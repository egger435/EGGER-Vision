using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

public class ConfigReader : MonoBehaviour
{
    public static ConfigReader Instance;

    private string configPath = "client_config.txt";
    private Dictionary<string, string> configDict = new Dictionary<string, string>();

    public string SeverIP => GetConfigValue("SeverIP");
    public int MsgSendPort => int.Parse(GetConfigValue("MsgSendPort"));
    public int MsgReceivePort => int.Parse(GetConfigValue("MsgReceivePort"));
    public string FrpSetupBat => GetConfigValue("FrpSetupBat");

    private void Awake()
    {
        if (Instance == null)
        {
            Instance = this;
            LoadConfig();
        }
        else
        {
            Destroy(gameObject);
        }
    }

    private void LoadConfig()
    {
        configDict.Clear();
        
        if (!File.Exists(configPath))
        {
            return;
        }

        string[] lines = File.ReadAllLines(configPath);
        foreach (var line in lines)
        {
            if (string.IsNullOrWhiteSpace(line) || line.TrimStart().StartsWith("//"))
                continue;

            string[] keyValue = line.Split('=', 2);
            if (keyValue.Length != 2)
            {
                continue;
            }

            string key = keyValue[0].Trim();
            string value = keyValue[1].Trim();
            configDict.Add(key, value);
        }
    }

    private string GetConfigValue(string key)
    {
        if (configDict.TryGetValue(key, out string value))
        {
            return value;
        }
        else
        {
            return string.Empty;
        }
    }
}
