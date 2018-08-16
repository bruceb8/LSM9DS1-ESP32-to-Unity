#include <WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h> 
#include <ArduinoJson.h>
#define DECLINATION 15.35
#define LSM9DS1_SCK 18
#define LSM9DS1_MISO 19
#define LSM9DS1_MOSI 23
#define LSM9DS1_XGCS 5
#define LSM9DS1_MCS 4
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS, LSM9DS1_MCS);

const char* ssid = "University of Washington";
//const char* ssid = "NETGEAR46";
const char* password =  "91coth61apar64woli93";
 
const uint16_t port = 8000;
const char* host = "10.16.6.202";
//const char * host = "192.168.1.14";


void setupSensor()
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_12GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_16GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_2000DPS);
}

 
void setup()
{
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
 Serial.begin(115200);

  while (!Serial) {
    delay(1); // will pause Zero, Leonardo, etc until serial console opens
  }
  
  Serial.println("LSM9DS1 data read demo");
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS1. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS1 9DOF");

  // helper to just set the default scaling we want, see above!
  setupSensor();
}
 
void loop()
{
    WiFiClient client;
 
    if (!client.connect(host, port)) {
 
        Serial.println("Connection to host failed");
 
        delay(1000);
        return;
    }
    lsm.read();  /* ask it to read in the data */ 

     /* Get a new sensor event */ 
    sensors_event_t a, m, g, temp;

    lsm.getEvent(&a, &m, &g, &temp);
    int gx = g.gyro.x;
    int gy = g.gyro.y;
    int gz = g.gyro.z;
    //String postData = "[{ \"time\":\"8:36 PM\"&\"gyrox\":\"93.2923\"&\"gyroy\":\"120\"&\"gyroz\":\"12\" }]";
    //String postData = "time=8%3A36+PM&gyrox=93.2923&gyroy=120&gyroz=12";
    String postData = "gyrox=&gyroy=&gyroz=";
    int total = postData.length() + Serial.print(g.gyro.x) + Serial.print(g.gyro.y) + Serial.print(g.gyro.z);
    
    client.println("POST /gyro HTTP/1.1");
    client.println("Host: 192.168.1.14:8000");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Connection: close");
    client.println("Cache-Control: no-cache");
    client.print("Content-Length: ");
    //client.println(postData.length());
    client.println(total);
    client.println("");
    
     client.print("gyrox="); client.print(g.gyro.x); client.print("&");
     client.print("gyroy="); client.print(g.gyro.y); client.print("&");
     client.print("gyroz="); client.print(g.gyro.z); client.println("");

      //now we post accel
      postData = "xcelx=&xcely=&xcelz=";
      total = postData.length() + Serial.print(a.acceleration.x) + Serial.print(a.acceleration.y) + Serial.print(a.acceleration.z);
    
    client.println("POST /xcel HTTP/1.1");
    client.println("Host: 192.168.1.14:8000");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Connection: close");
    client.println("Cache-Control: no-cache");
    client.print("Content-Length: ");
    //client.println(postData.length());
    client.println(total);
    client.println("");
    
     client.print("xcelx="); client.print(a.acceleration.x); client.print("&");
     client.print("xcely="); client.print(a.acceleration.y); client.print("&");
     client.print("xcelz="); client.print(a.acceleration.z); client.println("");



      //now we post the magnet
      postData = "magx=&magy=&magz=";
      total = postData.length() + Serial.print(m.magnetic.x) + Serial.print(m.magnetic.y) + Serial.print(m.magnetic.z);
    
    client.println("POST /mag HTTP/1.1");
    client.println("Host: 192.168.1.14:8000");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Connection: close");
    client.println("Cache-Control: no-cache");
    client.print("Content-Length: ");
    //client.println(postData.length());
    client.println(total);
    client.println("");
    
     client.print("magx="); client.print(m.magnetic.x); client.print("&");
     client.print("magy="); client.print(m.magnetic.y); client.print("&");
     client.print("magz="); client.print(m.magnetic.z); client.println("");


    //client.println(postData);
    client.stop();
    Serial.println();
    delay(200);
}
