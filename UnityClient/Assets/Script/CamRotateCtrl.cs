using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class CamRotateCtrl : MonoBehaviour
{
    public InputActionAsset inputActionAsset;

    private InputAction rotateCamLeft;
    private InputAction rotateCamRight;
    private InputAction rotateCamBehind;

    private void Awake()
    {
        rotateCamLeft   = inputActionAsset.FindActionMap("Cam_Action").FindAction("Rotate_Camera_Left");
        rotateCamRight  = inputActionAsset.FindActionMap("Cam_Action").FindAction("Rotate_Camera_Right");
        rotateCamBehind = inputActionAsset.FindActionMap("Cam_Action").FindAction("Rotate_Camera_Behind");
    }

    private void OnEnable()
    {
        rotateCamLeft.Enable();
        rotateCamLeft.performed += OnD_PadLeft;
        rotateCamLeft.canceled  += OnD_PadReset;

        rotateCamRight.Enable();
        rotateCamRight.performed += OnD_PadRight;
        rotateCamRight.canceled  += OnD_PadReset;

        rotateCamBehind.Enable();
        rotateCamBehind.performed += OnD_PadBehind;
        rotateCamBehind.canceled  += OnD_PadReset;
    }

    private void OnD_PadLeft(InputAction.CallbackContext context)
    {
        Debug.Log("发送摄像头左转指令");
        UDPCtrl.Instance.SendCommand(ControlCmd.RotateCameraLeft);
    }

    private void OnD_PadRight(InputAction.CallbackContext context)
    {
        Debug.Log("发送摄像头右转指令");
        UDPCtrl.Instance.SendCommand(ControlCmd.RotateCameraRight);
    }

    private void OnD_PadBehind(InputAction.CallbackContext context)
    {
        Debug.Log("发送摄像头向后转指令");
        UDPCtrl.Instance.SendCommand(ControlCmd.RotateCameraBehind);
    }

    private void OnD_PadReset(InputAction.CallbackContext context)
    {
        Debug.Log("发送摄像头复位指令");
        UDPCtrl.Instance.SendCommand(ControlCmd.RotateCamerainPlace);
    }
}
