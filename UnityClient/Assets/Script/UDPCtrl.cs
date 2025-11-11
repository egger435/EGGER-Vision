using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using System.Net.Sockets;
using UnityEngine.UI;
using System.Threading;
using System.Diagnostics;
using System.IO;

public class UDPCtrl : MonoBehaviour
{
    public static UDPCtrl Instance;

    [Header("配置文本输入框组件")]
    public InputField serverIPInput;
    public InputField msgSendPortInput;
    public InputField msgReceivePortInput;
    public InputField frpSetupNameInput;

    [Header("配置文本组件")]
    public Text serverIPText;
    public Text msgSendPortText;
    public Text msgReceivePortText;
    public Text frpSetupNameText;

    private string serverIP = "0.0.0.0";

    private int MSG_SEND_PORT = 00000;  // unity向frp服务器发送消息端口
    private UdpClient udpSendClient;

    private string frpSetupName = "frpc_setup.bat";

    [Header("UI控件")]
    public Text sendText;
    public Text logText;

    private string appPath;
    private string rootDir;

    void Start()
    {
        if (Instance == null)
            Instance = this;
    }

    // 自动配置
    public void AutoSetup()
    {
        serverIPText.text = "47.118.30.136";
        msgSendPortText.text = "12300";
        msgReceivePortText.text = "13300";
        frpSetupNameText.text = "_frpc_setup.bat";

        serverIPInput.text = "47.118.30.136";
        msgSendPortInput.text = "12300";
        msgReceivePortInput.text = "13300";
        frpSetupNameInput.text = "_frpc_setup.bat";
    }

    // 配置确认
    public void SendSetupConfirm()
    {
        if (serverIPText == null || msgSendPortText == null)
            return;
        serverIP = serverIPText.text;
        MSG_SEND_PORT = int.Parse(msgSendPortText.text);
        frpSetupName = frpSetupNameText.text;
    }

    // 启动frp客户端bat文件
    public void FRPClientBatStart()
    {
        logText.text += "\n" + "启动frp客户端，请查看控制台...启动后请勿关闭客户端";
        try
        {
            appPath = Application.dataPath;
            rootDir = Path.GetDirectoryName(appPath);

            string batPath = Path.Combine(rootDir, frpSetupName);

            if (!File.Exists(batPath))
            {
                UnityEngine.Debug.LogError($"批处理文件不存在：{batPath}");
                logText.text += "\n" + $"批处理文件不存在：{batPath}";
                return;
            }

            ProcessStartInfo startInfo = new ProcessStartInfo
            {
                FileName = batPath, 
                WorkingDirectory = rootDir, 
                UseShellExecute = true, 
                CreateNoWindow = false 
                // 若需隐藏窗口，可设置为：
                // CreateNoWindow = true,
                // UseShellExecute = false
            };

            Process process = Process.Start(startInfo);
            if (process != null)
            {
                UnityEngine.Debug.Log($"成功启动批处理：{batPath}");
                UnityEngine.Debug.Log("FRP客户端已建立");
            }
            else
            {
                UnityEngine.Debug.LogError("启动批处理失败，进程为null");
            }
        }
        catch (System.Exception ex)
        {
            UnityEngine.Debug.LogError($"启动批处理出错：{ex.Message}");
        }
    }

    // udp发送客户端初始化
    public void SendClientInit()
    {
        logText.text += "\n" + "正在建立UDP通信...";
        try
        {
            IPAddress[] addresses = Dns.GetHostAddresses(serverIP);
            IPAddress ipv4Address = null;
            foreach (var addr in addresses)
            {
                UnityEngine.Debug.Log("解析地址: " + addr + " (" + addr.AddressFamily + ")");
                if (addr.AddressFamily == AddressFamily.InterNetwork)
                {
                    ipv4Address = addr;
                    break;
                }
            }
            if (ipv4Address != null)
            {
                IPEndPoint endPoint = new IPEndPoint(ipv4Address, MSG_SEND_PORT);
                udpSendClient = new UdpClient(AddressFamily.InterNetwork);
                UnityEngine.Debug.Log("UDP 连接到: " + endPoint.Address + ":" + endPoint.Port);
                logText.text = "UDP 连接到: " + endPoint.Address + ":" + endPoint.Port;
            }
            else
            {
                UnityEngine.Debug.LogError("未找到 IPv4 地址: " + serverIP);
                logText.text = "未找到 IPv4 地址: " + serverIP;
            }
        }
        catch (System.Exception e)
        {
            UnityEngine.Debug.LogError("UDP send start failed:" + e.Message);
            logText.text = "UDP send start failed:" + e.Message;
        }
    }

    // 发送命令
    public void SendCommand(string cmd)
    {
        try
        {
            IPEndPoint endPoint = new IPEndPoint(IPAddress.Parse(serverIP), MSG_SEND_PORT);
            byte[] data = null;
            string message = string.Empty;
            
            if (string.IsNullOrEmpty(cmd))  // 文本输入框发送
            {
                data = System.Text.Encoding.UTF8.GetBytes(sendText.text);
                message = sendText.text;
            }
            else
            {
                data = System.Text.Encoding.UTF8.GetBytes(cmd);
                message = cmd;
            }

            udpSendClient.Send(data, data.Length, endPoint);
            UnityEngine.Debug.Log("send:" + message);
            logText.text = logText.text + "\nsend:" + message;
        }
        catch (System.Exception e)
        {
            UnityEngine.Debug.LogError("UDP send failed:" + e.Message);
            logText.text = "UDP send failed:" + e.Message;
        }
    }
}
