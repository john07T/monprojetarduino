#include <Wire.h>

#define LCD_ADDR 0x27   // Remplace par l'adresse trouvée avec le scan I2C
#define BACKLIGHT 0x08  // Active le rétroéclairage

// Envoi d’un nibble au LCD avec EN
void lcdPulseEnable(uint8_t data) {
  Wire.beginTransmission(LCD_ADDR);
  Wire.write(data | BACKLIGHT | 0x04); // EN = 1
  Wire.endTransmission();
  delayMicroseconds(1);

  Wire.beginTransmission(LCD_ADDR);
  Wire.write((data | BACKLIGHT) & ~0x04); // EN = 0
  Wire.endTransmission();
  delayMicroseconds(50);
}

// Envoi d’un octet complet au LCD
void lcdSend(uint8_t value, uint8_t mode) {
  lcdPulseEnable((value & 0xF0) | mode);
  lcdPulseEnable(((value << 4) & 0xF0) | mode);
}

// Commande
void lcdCommand(uint8_t cmd) {
  lcdSend(cmd, 0x00);
}

// Donnée (caractère)
void lcdData(uint8_t data) {
  lcdSend(data, 0x01);
}

// Initialisation du LCD
void lcdInit() {
  Wire.begin();
  delay(50);

  // Initialisation en mode 4 bits
  lcdPulseEnable(0x30); delay(5);
  lcdPulseEnable(0x30); delayMicroseconds(100);
  lcdPulseEnable(0x20);

  lcdCommand(0x28); // 4 bits, 2 lignes, 5x8
  lcdCommand(0x0C); // Affichage ON, curseur OFF
  lcdCommand(0x06); // Déplacement du curseur vers la droite
  lcdCommand(0x01); // Efface l’écran
  delay(2);
}

// Afficher une chaîne de caractères
void lcdPrint(const char* str) {
  while (*str) {
    lcdData(*str++);
  }
}

void setup() {
  lcdInit();
  lcdPrint("Salut Ives et Akido");
  lcdCommand(0xC0); // Déplacement à la deuxième ligne
  lcdPrint("John est de retour");
}

void loop() {
  // Rien à faire ici
}
