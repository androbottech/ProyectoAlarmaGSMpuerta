#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

#define sensor A3
#define buzzer 6

void setup()
{
  pinMode(sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, i t will back to OK
  updateSerial();

  while(digitalRead(sensor)== 1)
  {
    
  }
  tone(buzzer, 500);
  llamar();
  noTone(buzzer);
}

void loop()
{
  
}

void llamar()
{
  mySerial.println("ATD+ +zzzzzzzzz;");
  updateSerial();
  delay(15000); // wait for 15 seconds...
  mySerial.println("ATH"); //hang up
  delay(1000);
  updateSerial();
}

void sms()
{
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  delay(100);
  mySerial.println("AT+CMGS=\"+zzzzzzz\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  delay(100);
  mySerial.print("ON"); //text content
  delay(100);
  mySerial.write(26);
  delay(100);
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
