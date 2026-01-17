using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class CarMoveCtrl : MonoBehaviour
{
    public InputActionAsset inputActionAsset;
    private InputAction moveAction;

    private float moveInput;

    private void Awake()
    {
        moveAction = inputActionAsset.FindActionMap("Car_Move").FindAction("Move");
    }

    private void OnEnable()
    {
        moveAction.Enable();
    }

    private void OnDisable()
    {
        moveAction.Disable();
    }

    private void Update()
    {
        moveInput = moveAction.ReadValue<float>();

        if (moveInput > 0)
        {
            Debug.Log($"右扳机按下深度：{moveInput}");
        }
    }
}
