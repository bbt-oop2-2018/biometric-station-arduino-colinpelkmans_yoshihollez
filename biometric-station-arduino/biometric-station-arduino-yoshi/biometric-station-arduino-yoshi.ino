#include <SparkFun_MMA8452Q.h>
#include <LiquidCrystal.h>
#include <math.h>
#define PROCESSING_VISUALIZER 1
#define SERIAL_PLOTTER  2
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   
#include <Wire.h> // Used to establied serial communication on the I2C bus
#include "SparkFunTMP102.h" // Used to send and recieve specific information from our sensor

const int PulseWire = 0;        
float temperature;
int Threshold = 550;

TMP102 sensor0(0x48);
MMA8452Q accel;

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

static int outputType = SERIAL_PLOTTER;
PulseSensorPlayground pulseSensor;

void setup(){
  lcd.begin(16, 2);
  lcd.noAutoscroll();
  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);
  Serial.begin(115200);             
  accel.init();
  sensor0.begin();  // Join I2C bus
  sensor0.setConversionRate(2);
  sensor0.setExtendedMode(0);
  pulseSensor.begin();
}

void loop(){
  lcd.clear();
    Serial.print("$");
    Serial.print(accelloSensor());
    lcd.print( "XYZ:" + accelloSensor());
    lcd.setCursor(0, 1); // bottom left
    Serial.print("_");
    Serial.print(getBPM());
    lcd.print("BPM: ");
    lcd.print(getBPM());
    lcd.print(" ");
    Serial.print("_");
    lcd.print(temperatureSensor());
    lcd.write(223);
    lcd.print("C");
    Serial.print(temperatureSensor());
    Serial.print("£");    
    Serial.println();
    delay(1000);                          //  take a break
}

String temperatureSensor(){
  sensor0.wakeup();
  temperature = sensor0.readTempC();
  sensor0.sleep();
 
    String temperatureString="";
    temperatureString = String(temperature,1);
    return temperatureString;
}
String accelloSensor(){
    accel.available();
    accel.read();
    
    String xString="";
    String yString="";
    String zString="";
    xString = String(accel.cx,1);
    yString = String(accel.cy,1);
    zString = String(accel.cz,1);
        
    return xString + "_" + yString + "_" + zString;
}

int getBPM(){
   int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
  if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened".
    return myBPM;     
  }


}
  
