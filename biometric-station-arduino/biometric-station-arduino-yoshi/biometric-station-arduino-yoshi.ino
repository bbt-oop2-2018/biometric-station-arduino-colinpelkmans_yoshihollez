#include <Wire.h>
#include <SparkFun_MMA8452Q.h>
#include "SparkFunTMP102.h" // Used to send and recieve specific information from our sensor
#define PROCESSING_VISUALIZER 1
#define SERIAL_PLOTTER  2

int pulsePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.
float temperature;

TMP102 sensor0(0x48);
MMA8452Q accel;

void setup(){
  Serial.begin(115200);
  interruptSetup();
  accel.init();
  sensor0.begin();  // Join I2C bus
  sensor0.setConversionRate(2);
  sensor0.setExtendedMode(0);
}

void loop(){
    //Serial.print("$");
    //Serial.print(accelloSensor());
    //Serial.print("|");
    Serial.print(heartBeat());
    //Serial.print("|");
    //Serial.print(temperatureSensor());
    //Serial.print("£");    
    Serial.println();
    delay(100);
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
    //serialOutput() ;

  if (QS == true){     // A Heartbeat Was Found
                       // BPM and IBI have been Determined
                       // Quantified Self "QS" true when arduino finds a heartbeat

        //serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.
        QS = false;                      // reset the Quantified Self flag for next time
  }
     

      
}
