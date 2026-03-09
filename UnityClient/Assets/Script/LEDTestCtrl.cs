using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class LEDTestCtrl : MonoBehaviour
{
    public InputActionAsset inputActionAsset;
    private InputAction changeLEDState;

    private void Awake()
    {
        changeLEDState = inputActionAsset.FindActionMap("LED_Test").FindAction("Change_LED_State");
    }

    private void OnEnable()
    {
        changeLEDState.Enable();
        changeLEDState.performed += OnButtonPress;
        changeLEDState.canceled += OnButtonRelease;
    }

    private void OnDisable()
    {
        changeLEDState.performed -= OnButtonPress;
        changeLEDState.canceled -= OnButtonRelease;
        changeLEDState.Disable();
    }

    private void OnButtonPress(InputAction.CallbackContext context)
    {
        Debug.Log("按键按下");
        UDPCtrl.Instance.SendCommand(ControlCmd.ChangeLEDState);
    }

    private void OnButtonRelease(InputAction.CallbackContext context)
    {
        Debug.Log("按键松开");
    }
}
