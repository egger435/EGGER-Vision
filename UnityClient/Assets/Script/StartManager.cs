using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StartManager : MonoBehaviour
{
    private float upStartY = 30f;
    private float upTargetY = 240f;

    private float downStartY = -80f;
    private float downTargetY = -300f;
    private float moveDuration = 0.5f;
    private float fadeDuration = 0.5f;

    public RectTransform upImage;
    public RectTransform downImage;
    public CanvasGroup canvasGroup;

    private enum State { Idle, Moving, Fading }
    private State _state;
    private float curMoveTime = 0;
    private float fadeTimer = 0;
    private float idleTimer = 0;

    // Start is called before the first frame update
    void Start()
    {
        _state = State.Idle;
        // SetStartPos();
    }

    // Update is called once per frame
    void Update()
    {
        if (_state == State.Idle)
        {
            idleTimer += Time.deltaTime;
            if (idleTimer > 0.5)
            {
                StartMove();
            }
        }
        else if (_state == State.Moving)
        {
            DoMove();
        }
        else if (_state == State.Fading)
        {
            DoFade();
        }
    }

    private void SetStartPos()
    {
        Vector2 upStartPos = upImage.anchoredPosition;
        upStartPos.y = upStartY;
        upImage.anchoredPosition = upStartPos;

        Vector2 downStartPos = downImage.anchoredPosition;
        downStartPos.y = downStartY;
        downImage.anchoredPosition = downStartPos;
    }

    private void StartMove()
    {
        curMoveTime = 0;
        enabled = true;
        _state = State.Moving;
    }

    private void DoMove()
    {
        if (curMoveTime < moveDuration)
        {
            curMoveTime += Time.deltaTime;
            float t = Mathf.SmoothStep(0, 1, curMoveTime / moveDuration);
            float currentUpY = Mathf.Lerp(upStartY, upTargetY, t);
            float currentDownY = Mathf.Lerp(downStartY, downTargetY, t);

            Vector2 upStartPos = upImage.anchoredPosition;
            upStartPos.y = currentUpY;
            upImage.anchoredPosition = upStartPos;

            Vector2 downStartPos = downImage.anchoredPosition;
            downStartPos.y = currentDownY;
            downImage.anchoredPosition = downStartPos;
        }
        else
        {
            _state = State.Fading;
            fadeTimer = 0;
        }
    }

    void DoFade()
    {
        if (fadeTimer < fadeDuration)
        {
            fadeTimer += Time.deltaTime;
            float t = fadeTimer / fadeDuration;
            canvasGroup.alpha = Mathf.Lerp(1f, 0f, t);
        }
        else
        {
            canvasGroup.alpha = 0f;
            canvasGroup.gameObject.SetActive(false);
            enabled = false;
        }
    }
}
