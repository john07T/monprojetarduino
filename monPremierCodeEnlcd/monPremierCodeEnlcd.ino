#include <Wire.h>

#define LCD_ADDR 0x27
#define BACKLIGHT 0x08  // Lumière de fond ON

// Fonction pour envoyer un signal au LCD
void lcdPulseEnable(uint8_t data) {
  Wire.beginTransmission(LCD_ADDR);
  Wire.write(data | 0x04 | BACKLIGHT); // EN = 1
  Wire.endTransmission();
  delayMicroseconds(1);
  Wire.beginTransmission(LCD_ADDR);
  Wire.write((data & ~0x04) | BACKLIGHT); // EN = 0
  Wire.endTransmission();
  delayMicroseconds(50);
}

// Envoi 4 bits
void lcdWrite4bits(uint8_t value) {
  Wire.beginTransmission(LCD_ADDR);
  Wire.write(value | BACKLIGHT);
  Wire.endTransmission();
  lcdPulseEnable(value);
}

// Envoi d’une commande au LCD
void lcdCommand(uint8_t cmd) {
  lcdWrite4bits(cmd & 0xF0);          // 4 bits hauts
  lcdWrite4bits((cmd << 4) & 0xF0);   // 4 bits bas
}

// Envoi d’une lettre à afficher
void lcdWriteChar(uint8_t data) {
  lcdWrite4bits((data & 0xF0) | 0x01);          // RS = 1
  lcdWrite4bits(((data << 4) & 0xF0) | 0x01);   // RS = 1
}

// Initialisation du LCD
void lcdInit() {
  Wire.begin();
  delay(50);

  lcdWrite4bits(0x30); delay(5);
  lcdWrite4bits(0x30); delayMicroseconds(100);
  lcdWrite4bits(0x20); // Mode 4 bits

  lcdCommand(0x28); // 4 bits, 2 lignes
  lcdCommand(0x0C); // Écran ON
  lcdCommand(0x06); // Curseur avance à droite
  lcdCommand(0x01); // Effacer l’écran
  delay(2);
}

void setup() {
  lcdInit();
  lcdWriteChar('S');
  lcdWriteChar('A');
  lcdWriteChar('L');
  lcdWriteChar('U');
  lcdWriteChar('T');
}

void loop() {}
