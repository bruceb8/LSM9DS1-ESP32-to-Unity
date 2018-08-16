using System.Collections;
using System.Collections.Generic;
using SimpleJSON;
using System.IO.Ports;
using UnityEngine;

public class ArduinoPlane : MonoBehaviour
{
    //SerialPort serial = new SerialPort("COM4", 115200);
    
    // Use this for initialization
    void Start()
    {
        //serial.Open();
    }
    // Update is called once per frame
    Quaternion lastRot;
    void Update()
    {
        //first we need to read the website
        //string test = "http://192.168.1.14:8000/gyro";
        string test = "http://10.16.6.202:8000/gyro";
        WWW www = new WWW(test);
        ///yield return www;
        while (!www.isDone) { }
        string parseThis = www.text;
        //Debug.Log(www.error);
        //then we take the string and parse it using json
        var N = JSON.Parse(parseThis);
        //string[] acc = new string[3];
        string[] gyr = new string[3];
        //string[] mag = new string[3];
        gyr[0] = N["gyrox"];
        gyr[1] = N["gyroy"];
        gyr[2] = N["gyroz"];

        //Debug.Log(gyr[0]);
        //Debug.Log(gyr[1]);
        //Debug.Log(gyr[2]);
        //then we assign it to the strings below

        /*  
        string[] acc = serial.ReadLine().Split(',');
        string[] gyr = serial.ReadLine().Split(',');
        string[] mag = serial.ReadLine().Split(',');
        */
        Vector3 gyro = new Vector3(float.Parse(gyr[0]), float.Parse(gyr[1]), float.Parse(gyr[2]));
        Quaternion rot = Quaternion.Euler(new Vector3(float.Parse(gyr[0]), float.Parse(gyr[1]), float.Parse(gyr[2])));
        //Quaternion rot = Quaternion.Euler(gyro);
        /*if(gyro.sqrMagnitude > 50) {
            lastRot = rot;
        }*/
        transform.rotation = Quaternion.Slerp(transform.rotation, rot, Time.deltaTime * 2);
        //transform.position = new Vector3(-0.12f, 0.17f, 0f);
        //new WaitForSecondsRealtime(0.5f);
    }
}