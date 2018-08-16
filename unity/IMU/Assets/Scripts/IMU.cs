using System.Collections;
using System.Collections.Generic;
using System.IO.Ports;
using UnityEngine;

public class IMU : MonoBehaviour
{
    //this port thing needs to be changed to recieve from a websocket/webserver
    SerialPort serial = new SerialPort("COM4", 115200);

    // Use this for initialization
    void Start()
    {
        serial.Open();
    }

    // Update is called once per frame
    void Update()
    {
        if (!serial.IsOpen)
        {
            serial.Open();
        }
        //maybe change the order of these
        string[] acc = serial.ReadLine().Split(',');
        string[] gyr = serial.ReadLine().Split(',');
        string[] mag = serial.ReadLine().Split(',');

        //there is another line to can add here to keep the objects on screen

        Quaternion rot = Quaternion.Euler(new Vector3(float.Parse(gyr[0]), float.Parse(gyr[1]), float.Parse(gyr[2])));
        transform.rotation = Quaternion.Slerp(transform.rotation, rot, Time.deltaTime * 2.0f);
    }
}