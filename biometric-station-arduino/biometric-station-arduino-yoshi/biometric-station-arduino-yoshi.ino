#include <Wire.h>
#include <SparkFun_MMA8452Q.h>
#include "SparkFunTMP102.h" // Used to send and recieve specific information from our sensor

int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int THRESHOLD = 550;            // Determine which Signal to "count as a beat", and which to ingore.
int MAXTHRESHOLD = 1500;
float temperature;
TMP102 sensor0(0x48);
MMA8452Q accel;

void setup(){
  Serial.begin(115200);
  accel.init();
  sensor0.begin();  // Join I2C bus
  sensor0.setConversionRate(2);
  sensor0.setExtendedMode(0);
}

void loop(){
    Serial.print("[");
    Serial.print(accelloSensor());
    Serial.print("|");
    Serial.print(heartBeat());
    Serial.print("|");
    Serial.print(temperatureSensor());
    Serial.print("]");    
    Serial.println();
    delay(10);
}
String temperatureSensor(){
  sensor0.wakeup();
  temperature = sensor0.readTempC();
  sensor0.sleep();

    String temperatureString="";
    temperatureString = String(temperature,4);
    return temperatureString;
}
String accelloSensor(){
    accel.available();
    accel.read();
    
    String xString="";
    String yString="";
    String zString="";
    xString = String(accel.cx,4);
    yString = String(accel.cy,4);
    zString = String(accel.cz,4);
        
    return xString + "," + yString + "," + zString;
}

String heartBeat(){
  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
                                              // Assign this value to the "Signal" variable.
    if(Signal > THRESHOLD){
      //Serial.println(Signal);    // Send the Signal value to Serial Plotter.
      String signalString = String(Signal);
      return signalString;
      }
      return "0";
}
