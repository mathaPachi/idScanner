#include <LiquidCrystal.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
  Serial.begin(9600);  // Initialize serial communications.
  SPI.begin();  // Initialize SPI bus.
  mfrc522.PCD_Init();  // Initialize MFRC522 card reader.

  lcd.begin(16, 2);  // Initialize LCD screen.
  lcd.setCursor(0, 0);
  lcd.print("RFID Attendance");
}

void loop() {
  // Look for new cards.
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String cardID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      cardID += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
      cardID += String(mfrc522.uid.uidByte[i], HEX);
    }
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();

    // Check if the card is registered.
    if (cardID == "12345678") {  // Replace with your registered card ID.
      lcd.setCursor(0, 1);
      lcd.print("Welcome!");
      delay(1000);
    } else {
      lcd.setCursor(0, 1);
      lcd.print("Unregistered card");
      delay(1000);
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RFID Attendance");
  }
}