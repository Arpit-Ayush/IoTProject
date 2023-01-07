//For RFID

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
Servo SM;

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup(){
  SM.attach(3);         //Servo Pin Number  
  SM.write(0);  
  delay(5000); 
  SM.write(180);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();          // Initiate  SPI bus  
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader..."); 
  Serial.println();
}

Void loop(){
  // Look for new cards 
    if ( ! mfrc522.PICC_IsNewCardPresent())   {  
      return;
    } 
  // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()){    
      return;
    }
  //Show UID on serial monitor
    Serial.print("UID tag :"); 
    String content= ""; 
    byte letter; 
    for (byte i = 0; i < mfrc522.uid.size; i++)   {  
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");     
      Serial.print(mfrc522.uid.uidByte[i], HEX);     
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));     
      content.concat(String(mfrc522.uid.uidByte[i], HEX)); 
    }
    Serial.println();
    Serial.print("Message : ");  content.toUpperCase();  
    if ((content.substring(1) == "90 CB 00 A9") || (content.substring(1) == "A9 34 25 D9")){   
      SM.write(0);   
      Serial.println("Authorized access");    delay(3000);    
      SM.write(180);    
      Serial.println();   
      delay(3000); 
    } 
    else {   
      Serial.println(" Access denied");    delay(1000); 
    }
}
