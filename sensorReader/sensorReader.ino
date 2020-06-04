#include <gprs.h>  // for Comunicating with SIM 900
#include <SoftwareSerial.h> // for Comunicating with SIM 900

const int trigPin = 2; // signal out pins for Sensor
const int echoPin = 4; // signal in pin for Sensor
const int ledPin =13; 
const int  medium =60;  
const int  high=35;
const int low=80;
GPRS gprs;
 
void setup() {
  
  Serial.begin(9600);
  
}
 
void loop() {

  long duration, inches, cm;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  delay(100);
  cm = microsecondsToCentimeters(duration);
  delay(100);
  String testString = String(cm);
  if (isDigit(testString.charAt(0))){
     if((cm<300)  ){
       Serial.println(cm);
     if (cm<high){
       sendSMS("full");
     }else{
     if(cm<medium){
       sendSMS("half");
       Serial.println();
     }else{
       sendSMS("empty");
       Serial.println();
    }
  }
 delay(1000);
}else{
  Serial.println("Sensor Error!, Repeating");
  delay(100);
 }
}else{
  Serial.println("Garbled Read!, Repeating");
  delay(100);
 }
}

long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
}

void sendSMS(String d){
    String Message="loc:0.6711880,35.5070199 state:"+d;
    if (isAlpha(Message.charAt(0))){
    char msg[Message.length()+1];
    Serial.println(Message);
    Serial.begin(9600);
    while(!Serial);
    Serial.println("Sending SMS...");
    gprs.preInit();
    delay(1000);
    Message.toCharArray(msg, Message.length());
    gprs.sendSMS("0724226XXX",msg); // sending message
    }else{
     Serial.println("garbled SMS, Repeat Sensor Read");
     delay(100);
    }
    
}
