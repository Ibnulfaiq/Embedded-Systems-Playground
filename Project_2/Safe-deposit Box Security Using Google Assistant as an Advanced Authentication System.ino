//library 
#include <MFRC522.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//RFID pins Declaration
#define SS_PIN D2
#define RST_PIN D1
MFRC522 rfid(SS_PIN, RST_PIN);
// Blynk Template Declaration
#define BLYNK_TEMPLATE_ID "TMPL6DctVJlW4"
#define BLYNK_TEMPLATE_NAME "Skripsi"
#define BLYNK_AUTH_TOKEN "29gzO84ywah4Z077ALjI_1JYYmyfOiGz"


// Blynk auth token deklaration and wifi integration
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Ibnu";
char pass[] = "Ibnu1201";
//variable declaration
bool isAuthenticated = false;
String allowedCardSerial1 = "2125fa23";
String allowedCardSerial2 = "76ac8f29";
int authenticationAttempts = 0;
const int MAX_AUTHENTICATION_ATTEMPTS = 3;
// subprogram Datastream integer V0 for blynk parameter
BLYNK_WRITE(V0)
{
  int value = param.asInt();
  
  if (value == HIGH) {
    digitalWrite(D4, HIGH);
  }
  else {
    digitalWrite(D4, LOW);
  }
  
  Blynk.virtualWrite(V0, value);
}
// pinmode, serial, spi, and blynk initial setup
void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(D4, OUTPUT);
  pinMode(D0, OUTPUT);
  pinMode(D3,INPUT);
  Blynk.begin(auth, ssid, pass);
  Blynk.virtualWrite(V0, LOW);
  
}
// calling the blynk activation and RFID authentication subprogram 
void loop() {
  
  Blynk.run();
  rfidLoop();
}
//subprogram for RFID authentication
void rfidLoop() {
  
  digitalWrite(D0, HIGH);
  int pinvalue = digitalRead(D3);

// RFID reading
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String cardSerial = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      cardSerial += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
      cardSerial += String(rfid.uid.uidByte[i], HEX);
    }

//RFID succeed Authentication sequence
    if (cardSerial == allowedCardSerial1 && authenticationAttempts < MAX_AUTHENTICATION_ATTEMPTS ) {
      isAuthenticated = true;
      Serial.println("Card Serial: " + cardSerial);
      Serial.println("Authentication successful!");
      authenticationAttempts = 0; // mereset perhitungan percobaan akses
      //blynk push notification activation
      Blynk.logEvent("rfid", "RFID authentication has been detected, you may unlock the safe using voice command");
      
      
    }
    else if (cardSerial == allowedCardSerial2 && authenticationAttempts < MAX_AUTHENTICATION_ATTEMPTS ) {
      isAuthenticated = true;
      Serial.println("Card Serial: " + cardSerial);
      Serial.println("Authentication successful!");
      authenticationAttempts = 0; // mereset perhitungan percobaan akses
      //blynk push notification activation
      Blynk.logEvent("rfid", "RFID authentication has been detected, you may unlock the safe using voice command");
      
    }
// Sequence when RFID authentication is failed
    else {
      isAuthenticated = false;
      Serial.println("Authentication failed!");
      Serial.println("Card Serial: " + cardSerial);
      authenticationAttempts++;
      Blynk.logEvent("rfid", "Access Attempt has been detected!");
     //Sequence When RFID authentication has reached the maximum authentication attempts
      if (authenticationAttempts >= MAX_AUTHENTICATION_ATTEMPTS) {
        Serial.println("Maximum authentication attempts reached!");
        //blynk warning push notification activation that would activate alarm
         Blynk.logEvent("maximum_access_attempt", "maximum attempt reached, RFID Authentication has been locked!");
        
      }
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  } 
//the sequence when the RFID read is successful and below the maximum access attempts
  if (isAuthenticated == true && pinvalue == HIGH && authenticationAttempts < MAX_AUTHENTICATION_ATTEMPTS)
  {
  digitalWrite(D0, LOW);
  //push notification activation on blynk
    Blynk.logEvent("google_assistant", "Safe Deposit Box Has been unlocked");
    delay(6000);
    //sequence to reset the push notification
    digitalWrite(D0, HIGH);
    isAuthenticated = false;
    digitalWrite(D4, LOW);
    Blynk.virtualWrite(V0, LOW);
  }
//the sequence when the RFID authentication access attempt is blocked and authentication
  else if (isAuthenticated == false && pinvalue == HIGH && authenticationAttempts >= MAX_AUTHENTICATION_ATTEMPTS )
  {
    authenticationAttempts = 0;
    //sequence to reset the push notification
    Blynk.logEvent("google_assistant", "RFID authentication has been unlocked");
  }
}
