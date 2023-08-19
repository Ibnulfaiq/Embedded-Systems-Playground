//pemanggilan library
#include <MFRC522.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//deklarasi pin simple select dan rst
#define SS_PIN D2
#define RST_PIN D1
MFRC522 rfid(SS_PIN, RST_PIN);
// deklarasi template dan token autentikasi
#define BLYNK_TEMPLATE_ID "TMPL6DctVJlW4"
#define BLYNK_TEMPLATE_NAME "Skripsi"
#define BLYNK_AUTH_TOKEN "29gzO84ywah4Z077ALjI_1JYYmyfOiGz"


// penetapan token autentikasi dan deklarasi ssid dan password wifi
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Ibnu";
char pass[] = "Ibnu1201";
//Deklarasi variabel
bool isAuthenticated = false;
String allowedCardSerial1 = "2125fa23";
String allowedCardSerial2 = "76ac8f29";
int authenticationAttempts = 0;
const int MAX_AUTHENTICATION_ATTEMPTS = 3;
// subprogram Datastream integer V0
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
// penetapan mode pin dan integrasi blynk
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
// pemanggilan subprogram RFID dan aktivasi blynk
void loop() {
  
  Blynk.run();
  rfidLoop();
}
//subprogram untuk autentikasi RFID
void rfidLoop() {
  
  digitalWrite(D0, HIGH);
  int pinvalue = digitalRead(D3);

//Pembacaan RFID
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String cardSerial = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      cardSerial += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
      cardSerial += String(rfid.uid.uidByte[i], HEX);
    }

//sekuensi ketika pembacaan berhasil
    if (cardSerial == allowedCardSerial1 && authenticationAttempts < MAX_AUTHENTICATION_ATTEMPTS ) {
      isAuthenticated = true;
      Serial.println("Card Serial: " + cardSerial);
      Serial.println("Authentication successful!");
      authenticationAttempts = 0; // mereset perhitungan percobaan akses
      //aktivasi push notification pada blynk
      Blynk.logEvent("rfid", "RFID authentication has been detected, you may unlock the safe using voice command");
      
      
    }
    else if (cardSerial == allowedCardSerial2 && authenticationAttempts < MAX_AUTHENTICATION_ATTEMPTS ) {
      isAuthenticated = true;
      Serial.println("Card Serial: " + cardSerial);
      Serial.println("Authentication successful!");
      authenticationAttempts = 0; // mereset perhitungan percobaan akses
      //aktivasi push notification pada blynk
      Blynk.logEvent("rfid", "RFID authentication has been detected, you may unlock the safe using voice command");
      
    }
//sekuensi ketika pembacaan tidak berhasil
    else {
      isAuthenticated = false;
      Serial.println("Authentication failed!");
      Serial.println("Card Serial: " + cardSerial);
      authenticationAttempts++;
      Blynk.logEvent("rfid", "Access Attempt has been detected!");
     //sekuensi ketika percobaan mencapai batas maksimum
      if (authenticationAttempts >= MAX_AUTHENTICATION_ATTEMPTS) {
        Serial.println("Maximum authentication attempts reached!");
        //aktivasi push notification pada blynk
         Blynk.logEvent("maximum_access_attempt", "maximum attempt reached, RFID Authentication has been locked!");
        
      }
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  } 
//sekuensi ketika pembacaan RFID berhasil dan dibawah maksimum percobaan akses
  if (isAuthenticated == true && pinvalue == HIGH && authenticationAttempts < MAX_AUTHENTICATION_ATTEMPTS)
  {
  digitalWrite(D0, LOW);
  //aktivasi push notification pada blynk
    Blynk.logEvent("google_assistant", "Safe Deposit Box Has been unlocked");
    delay(6000);
    //sekuensi untuk mereset push notification
    digitalWrite(D0, HIGH);
    isAuthenticated = false;
    digitalWrite(D4, LOW);
    Blynk.virtualWrite(V0, LOW);
  }
//sekuensi ketika percobaan akses autentikasi RFID diblokir dan autentikasi
  else if (isAuthenticated == false && pinvalue == HIGH && authenticationAttempts >= MAX_AUTHENTICATION_ATTEMPTS )
  {
    authenticationAttempts = 0;
    //aktivasi push notification pada blynk
    Blynk.logEvent("google_assistant", "RFID authentication has been unlocked");
  }
}
