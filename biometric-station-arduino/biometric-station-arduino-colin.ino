void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);

   }

void loop() {
  // put your main code here, to run repeatedly:
int pubg = 1234;
double level = 12.33;
String pubgString = String(pubg);
String levelString = String(level);
Serial.println("[" + pubgString + "|" + levelString  + "]");
delay(500);
}
