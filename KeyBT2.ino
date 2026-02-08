#define USE_NIMBLE
#include <NimBLEDevice.h> 
#include <BleKeyboard.h>
#include "soc/soc.h"             // Necessario per il brownout
#include "soc/rtc_cntl_reg.h"    // Necessario per il brownout

BleKeyboard bleKeyboard("Thomas-Key", "Thomas", 100);

const int buttonPin = 13; 
bool lastButtonState = HIGH;

void setup() {
  // ABILITA QUESTA RIGA: è fondamentale se la tua alimentazione è debole
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); 
  
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  
  Serial.println("Avvio con protezione Brownout...");
  bleKeyboard.begin();
  Serial.println("Tastiera pronta su G13!");
}

void loop() {
  if(bleKeyboard.isConnected()) {
    bool currentButtonState = digitalRead(buttonPin);
    
    if (currentButtonState == LOW && lastButtonState == HIGH) {
      Serial.println("Pulsante premuto!");
      bleKeyboard.print("a");
      delay(150); // Debounce leggermente più alto per sicurezza
    }
    lastButtonState = currentButtonState;
  }
}