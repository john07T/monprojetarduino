#include <Wire.h> // Active le fil magique I2C

#define LCD_ADDR 0x27  // Adresse du LCD
#define BACKLIGHT 0x08 // Allume la lumière derrière

// Fonction pour envoyer une lettre au LCD
void lcdData(uint8_t data) {
  Wire.beginTransmission(LCD_ADDR);
  Wire.write(data | BACKLIGHT | 0x04); // Appuie sur le bouton EN
  Wire.endTransmission();
  delayMicroseconds(1);
  Wire.beginTransmission(LCD_ADDR);
  Wire.write((data | BACKLIGHT) & ~0x04); // Relâche le bouton EN
  Wire.endTransmission();
  delayMicroseconds(50);
}
void lcdcommand(uint8_t cmd){
  lcdData(cmd & 0xF0);
  lcdData((cmd << 4) & 0xF0);
  
}

void lcdWritechar(uint8_t data){
  
  lcdData((data & 0xF0) | 0x00);
  
  lcdData(((data << 4) & 0xF0)|0x01);
  }



// Fonction pour initialiser l’écran
void lcdInit() {
  Wire.begin(); // Commence la communication I2C
  delay(50);
  // Préparer le LCD en mode 4 bits
  lcdData(0x30); delay(5);
  lcdData(0x38); delayMicroseconds(100);
  lcdData(0x20);

  lcdcommand(0x30); delay(5);
  lcdcommand(0x30); delayMicroseconds(100);
  lcdcommand(0x20);
  lcdcommand(0x28);
  lcdcommand(0x0C);
  lcdcommand(0x06);
  lcdcommand(0x01);
  delay(2);
  }

//setup` : ce qu’on fait au démarrage
void setup() {
  lcdInit();       // Prépare l’écran
  lcdWritechar('S');    // Affiche S
  lcdWritechar('a');    // Affiche a
  lcdWritechar('l');    // Affiche l
  lcdWritechar('u');    // Affiche u
  lcdWritechar('t');
  lcdWritechar('_');
  lcdWritechar('j');
  lcdWritechar('e');
  lcdWritechar('_');
  lcdWritechar('s');
  lcdWritechar('u');
  lcdWritechar('i');
  lcdWritechar('s');
  lcdWritechar('_');
  lcdWritechar('j');
  lcdWritechar('o');
  lcdWritechar('h');
  lcdWritechar('n');
}

// `loop` : ce qu’on fait en boucle
void loop() {}
