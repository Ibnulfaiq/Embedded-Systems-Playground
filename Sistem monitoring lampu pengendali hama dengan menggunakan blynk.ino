#define BLYNK_TEMPLATE_ID "TMPL8Rdty1-H"
#define BLYNK_DEVICE_NAME "Test"
#define BLYNK_AUTH_TOKEN "MCAhEFzQx-hDqtsUY9CMUobnuK8X_B-u"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#include <PZEM004Tv30.h>
PZEM004Tv30 pzem( 12, 15);
#include <Wire.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Ibnu";
char pass[] = "Ibnu1201";

BlynkTimer timer;




//LDR Sensor
byte ldr = A0;
int nilai;


const int ledBuiltIn = LED_BUILTIN;


//LCD
WidgetLCD led1(1);
WidgetLCD LCD2 (2);
// This function is called every time the Virtual Pin 0 state changes
const int buttonPin = D5;
int buttonState = 0;
void Widget()
{
  if (buttonState == HIGH) {
  led1.clear();
  led1.print(0, 0, "Mode Kontrol ");
  led1.print(0, 1, "Lampu: Otomatis");
  delay(8000);
  
    
  }
  
  else
  {
    led1.clear();
    led1.print(0, 0,"Mode Kontrol ");
    led1.print(0, 1, "Lampu: Manual");
    delay(8000);
  }
}

// This function is called every time the device is connected to the Blynk.Cloud

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, millis() / 1000);
}

//Switch Button
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
 int value = param.asInt();
  if (param.asInt() == HIGH) {
    digitalWrite(D5, LOW);
  }
  else {
    digitalWrite(D5, HIGH);
  }
  //Update state
 Blynk.virtualWrite(V0, value);
}



void setup()
{
  
  Serial.begin(9600);
  pinMode(ldr, INPUT);

  // Debug console
 // Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  
 
  pinMode(D0,OUTPUT);
  pinMode(D5, OUTPUT);

  //pinMode(ledBuiltIn, OUTPUT);  
  timer.setInterval(1000L, Widget);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
  //BlynkEdgent.begin():
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  Blynk.run();
  timer.run();
 


  //Ldr Sensor Trigger
  
  nilai = analogRead(ldr);
Blynk.virtualWrite(V8, nilai);
 /* if(D0==HIGH){
    
  */
  if (nilai <=500)
  {
    digitalWrite(D0, LOW);
    
  }
  else if (nilai >500)
  {
    digitalWrite(D0, HIGH);
    
  }/*
  }*/
  Serial.print("Nilai LDR: ");
  Serial.println(nilai);
  

{
float voltage = pzem.voltage();
float tegangan=voltage;
  Serial.print(voltage);Serial.print("V; ");
 Blynk.virtualWrite( V2, voltage);
  float current = pzem.current();
  Serial.print(current);Serial.print("A; "); 
  Blynk.virtualWrite( V3, current);
  /*
  float p = pzem.power(V4);
  if(p >= 0.0){ Serial.print(p);Serial.print("W; "); }
  
  float e = pzem.energy(V6);
  if(e >= 0.0){ Serial.print(e);Serial.print("Wh; "); }
 
  Serial.println();

float arus = pzem.current();
Serial.print("Current: "); Serial.print(arus); Serial.println("A");
*/
double power = pzem.power();
Serial.print("Power: "); Serial.print(power); Serial.println("W");
Blynk.virtualWrite( V4, power);

double dayawh = power*12;
double daya=dayawh/1000;
Blynk.virtualWrite( V6, daya);
Serial.print(daya);

float tariflistrik = daya*1352;
Blynk.virtualWrite(V7,"Tarif Listrik: Rp ", tariflistrik ,",00");
/*float pf = pzem.pf();
Serial.print("PF: "); 
Serial.println(pf);*/
delay(2000);
}
  
//  BlynkEdgent.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
