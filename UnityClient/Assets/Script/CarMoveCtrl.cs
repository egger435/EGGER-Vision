using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.UI;

public enum CarGear
{
    Reverse = 'R',
    Neutral = 'N',
    Drive = 'D',
    Speed = 'S'
}

public class CarMoveCtrl : MonoBehaviour
{
    [Header("UI")]
    public Image inputFill;
    public Image gearImage;
    public Image steerPosImage;
    public Sprite gearR;
    public Sprite gearN;
    public Sprite gearD;
    public Sprite gearS;
    public Text steeringValueText;
    public Text moveInputValueText;
    public Text curGearText;
    private float minFill = 0.2f;
    private float maxFill = 0.9f;
    private float currentSteeringAngle = 0f;

    public InputActionAsset inputActionAsset;
    private InputAction moveAction;
    private InputAction steeringAction;
    private InputAction gearActionUp;
    private InputAction gearActionDown;

    private float moveInput;
    private float steeringValue;

    private float sendInterval = 0.02f;  // 发送指令时间间隔 20ms

    private float lastSendTime;
    private int targetSteeringAngle;
    private int targetMoveInput;
    private CarGear curGear = CarGear.Neutral;

    private void Awake()
    {
        moveAction = inputActionAsset.FindActionMap("Car_Move").FindAction("Move");
        steeringAction = inputActionAsset.FindActionMap("Car_Move").FindAction("Steering");
        gearActionUp = inputActionAsset.FindActionMap("Car_Move").FindAction("GearUp");
        gearActionDown = inputActionAsset.FindActionMap("Car_Move").FindAction("GearDown");

        curGearText.text = $"Gear: {(char)curGear}";
        UpdateGearImage(curGear);
    }

    private void OnEnable()
    {
        moveAction.Enable();
        steeringAction.Enable();

        gearActionUp.Enable();
        gearActionUp.performed += OnBtnGearUp;

        gearActionDown.Enable();
        gearActionDown.performed += OnBtnGearDown;

        lastSendTime = Time.time;
    }

    private void OnDisable()
    {
        moveAction.Disable();
        steeringAction.Disable();
        gearActionUp.Disable();
        gearActionDown.Disable();
    }

    private void OnBtnGearUp(InputAction.CallbackContext context)
    {
        if (moveInput != 0 && curGear != CarGear.Drive) return;  // 只有在车停稳时才能升档
        Debug.Log("发送升档指令");
        curGear = curGear switch
        {
            CarGear.Reverse => CarGear.Neutral,
            CarGear.Neutral => CarGear.Drive,
            CarGear.Drive => CarGear.Speed,
            _ => curGear
        };
        if (UDPCtrl.Instance != null)
            UDPCtrl.Instance.SendCommand(ControlCmd.ShiftGear((char)curGear));
        curGearText.text = $"Gear: {(char)curGear}";
        UpdateGearImage(curGear);
    }

    private void OnBtnGearDown(InputAction.CallbackContext context)
    {
        if (moveInput != 0 && curGear != CarGear.Speed) return;  // 只有在车停稳时才能降档
        Debug.Log("发送降档指令");
        curGear = curGear switch
        {
            CarGear.Speed => CarGear.Drive,
            CarGear.Drive => CarGear.Neutral,
            CarGear.Neutral => CarGear.Reverse,
            _ => curGear
        };
        if (UDPCtrl.Instance != null)
            UDPCtrl.Instance.SendCommand(ControlCmd.ShiftGear((char)curGear));
        curGearText.text = $"Gear: {(char)curGear}";
        UpdateGearImage(curGear);
    }

    private void Update()
    {
        moveInput = moveAction.ReadValue<float>();
        steeringValue = steeringAction.ReadValue<float>();

        UpdateFill(moveInput);
        UpdateSteeringPos(steeringValue);

        if (steeringValueText != null)
        {
            steeringValueText.text = $"Steering value: {steeringValue:F2} | angle: {MapSteeringToAngle(steeringValue)}°";
        }
        if (moveInputValueText != null)
        {
            moveInputValueText.text = $"Move input: {(int)(moveInput * 100)}";
        }

        if (Time.time - lastSendTime >= sendInterval && UDPCtrl.Instance.udpReady)
        {
            SendSteeringAngleToPi();
            SendMoveSpeedToPi();
            lastSendTime = Time.time;
        }
    }

    // 更新输入填充
    private void UpdateFill(float moveInput)
    {
        float targetFillAmount = Mathf.Lerp(minFill, maxFill, moveInput);

        inputFill.fillAmount = Mathf.Lerp(inputFill.fillAmount, targetFillAmount, Time.deltaTime * 8);
    }

    private void UpdateGearImage(CarGear curGear)
    {
        switch (curGear)
        {
            case CarGear.Reverse:
                gearImage.sprite = gearR;
                break;
            case CarGear.Neutral:
                gearImage.sprite = gearN;
                break;
            case CarGear.Drive:
                gearImage.sprite = gearD;
                break;
            case CarGear.Speed:
                gearImage.sprite = gearS;
                break;
            default:
                gearImage.sprite = gearN;
                break;
        }
    }

    private void UpdateSteeringPos(float steeringValue)
    {
        float targetAngle = -steeringValue * 123;

        currentSteeringAngle = Mathf.Lerp(currentSteeringAngle, targetAngle, Time.deltaTime * 10);
        // 应用旋转
        steerPosImage.rectTransform.localRotation = Quaternion.Euler(0, 0, currentSteeringAngle);
    }

    // 将转向值映射为角度
    private int MapSteeringToAngle(float steeringVal)
    {
        float angleFloat = 30f * steeringVal + 90;
        angleFloat = Mathf.Clamp(angleFloat, 60f, 120f);
        return Mathf.RoundToInt(angleFloat);
    }

    private void SendSteeringAngleToPi()
    {
        targetSteeringAngle = MapSteeringToAngle(steeringValue);
        if (UDPCtrl.Instance != null)
        {
            string steeringCmd = ControlCmd.SteeringServoAngle(targetSteeringAngle);
            UDPCtrl.Instance.SendCommand(steeringCmd);
            Debug.Log("发送转向指令: " + steeringCmd + $" (转向值: {steeringValue:F2}, 角度: {targetSteeringAngle}°)");
        }
    }

    private void SendMoveSpeedToPi()
    {
        targetMoveInput = (int)(moveInput * 100);
        if (UDPCtrl.Instance != null)
        {
            string moveCmd = ControlCmd.MotorSpeed(targetMoveInput);
            UDPCtrl.Instance.SendCommand(moveCmd);
            Debug.Log("发送移动指令: " + moveCmd + $" (移动值: {moveInput:F2}, 速度值: {targetMoveInput})");
        }
    }
}
