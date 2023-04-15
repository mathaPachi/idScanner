#include <LiquidCrystal.h>  // Include the LiquidCrystal library
#include <MFRC522.h>  // Include the MFRC522 library

// Pins for RFID reader module
#define SS_PIN 10  // Slave Select (SS) pin of RFID reader
#define RST_PIN 9  // Reset (RST) pin of RFID reader

// Pins for LCD display
const int rs = 7;  // Register Select (RS) pin of LCD
const int en = 6;  // Enable (EN) pin of LCD
const int d4 = 5;  // Data 4 (D4) pin of LCD
const int d5 = 4;  // Data 5 (D5) pin of LCD
const int d6 = 3;  // Data 6 (D6) pin of LCD
const int d7 = 2;  // Data 7 (D7) pin of LCD

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Initialize MFRC522 object
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  // Initialize LCD object

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  SPI.begin();  // Initialize SPI bus
  mfrc522.PCD_Init();  // Initialize RFID reader module
  lcd.begin(16, 2);  // Initialize LCD display
  lcd.print("RFID Scanner");  // Display startup message
}

void loop() {
  lcd.setCursor(0, 1);  // Set cursor to second row
  lcd.print("Place RFID tag");  // Display prompt on LCD
  
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String rfidTag = "";  // Initialize empty string for storing RFID tag data
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      rfidTag += String(mfrc522.uid.uidByte[i], HEX);  // Read RFID tag data as hexadecimal
    }
    mfrc522.PICC_HaltA();  // Halt card to stop further reading
    lcd.clear();  // Clear LCD display
    lcd.setCursor(0, 0);  // Set cursor to first row
    lcd.print("RFID Tag:");  // Display "RFID Tag:" label
    lcd.setCursor(0, 1);  // Set cursor to second row
    lcd.print(rfidTag);  // Display RFID tag on LCD
    delay(1000);  // Delay to allow time for tag removal
  }
}
