#include <Wire.h>
#include <SparkFun_MMA8452Q.h>
#include "SparkFunTMP102.h" // Used to send and recieve specific information from our sensor
#include <LiquidCrystal.h>
#include <math.h>
#define PROCESSING_VISUALIZER 1
#define SERIAL_PLOTTER  2
//  Variables
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
float temperature;

TMP102 sensor0(0x48);
MMA8452Q accel;

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.
// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

static int outputType = SERIAL_PLOTTER;


void setup(){
  lcd.begin(16, 2);
   lcd.noAutoscroll();
  Serial.begin(115200);             // we agree to talk fast!
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS
    accel.init();
  sensor0.begin();  // Join I2C bus
  sensor0.setConversionRate(2);
  sensor0.setExtendedMode(0);


   // IF YOU ARE POWERING The Pulse Sensor AT VOLTAGE LESS THAN THE BOARD VOLTAGE,
   // UN-COMMENT THE NEXT LINE AND APPLY THAT VOLTAGE TO THE A-REF PIN
//   analogReference(EXTERNAL);
}


//  Where the Magic Happens
void loop(){
  lcd.clear();
    Serial.print("$");
    Serial.print(accelloSensor());
    lcd.print( "XYZ:" + accelloSensor());
    lcd.setCursor(0, 1); // bottom left
    Serial.print("_");
    
    serialOutput();

  if (QS == true){     // A Heartbeat Was Found
                       // BPM and IBI have been Determined
                       // Quantified Self "QS" true when arduino finds a heartbeat
                                // Set 'fadeRate' Variable to 255 to fade LED with pulse
        serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.
        QS = false;                      // reset the Quantified Self flag for next time
  }
    
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


