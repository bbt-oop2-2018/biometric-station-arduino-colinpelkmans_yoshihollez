#include <Wire.h>
#include <SparkFun_MMA8452Q.h>
#include "SparkFunTMP102.h" // Used to send and recieve specific information from our sensor

int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int THRESHOLD = 550;            // Determine which Signal to "count as a beat", and which to ingore.
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
    accelloSensor();
    Serial.print("|");
    heartBeat();
    Serial.print("|");
    temperatureSensor();
    Serial.print("]");    
    delay(10);
}
void temperatureSensor(){
  sensor0.wakeup();
  temperature = sensor0.readTempC();
  sensor0.sleep();
  Serial.print("Temperature: ");
  Serial.println(temperature);
}
void accelloSensor(){
    if (accel.available()){
    accel.read();
    printCalculatedAccels();
    }
}
int heartBeat(){
  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
                                              // Assign this value to the "Signal" variable.
    if(Signal > THRESHOLD){
       Serial.println(Signal);    // Send the Signal value to Serial Plotter.
       return Signal;
    }
    return 0;
}
void printCalculatedAccels()
{ 
  Serial.print("x: ");
  Serial.print(accel.cx, 3);
  Serial.print("\t");
  Serial.print("y: ");
  Serial.print(accel.cy, 3);
  Serial.print("\t");
  Serial.print("z: ");
  Serial.print(accel.cz, 3);
  Serial.print("\t");
}
