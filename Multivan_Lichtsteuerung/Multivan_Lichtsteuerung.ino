// Initialisierung der NeoPixel RGB-Leuchtdioden (WS2812B LED)
#include <Adafruit_NeoPixel.h>
// #ifdef __AVR__
//   #include <avr/power.h>
// #endif
#define PIN            6    // Neopixel Steuerung
#define NUMPIXELS      112
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int button = 3;         // Taster = Pin 3
int drehgeberA = 2;     // Drehimpulsgeber = Pin 2
int drehgeberB = 4;     // Drehimpulsgeber = Pin 4
int Licht = 0;          // Sollwert für Beleuchtungszustand 
int LichtStatus = 0;    // aktueller Zustand der Beleuchtung
int Helligkeit = 255;   // Helligkeit der LEDs

volatile unsigned long alteZeit=0, entprellZeit=20;

void setup() {

  pinMode(button, INPUT);                   // definiere Pin 3 als Eingang
  digitalWrite(button, HIGH);               // aktiviert den Pull- Up- Widerstand
  pinMode(drehgeberA, INPUT);               // definiere Pin 2 als Eingang
  digitalWrite(drehgeberA, HIGH);           // aktiviert den Pull- Up- Widerstand
  pinMode(drehgeberB, INPUT);               // definiere Pin 4 als Eingang
  digitalWrite(drehgeberB, HIGH);           // aktiviert den Pull- Up- Widerstand

  attachInterrupt(1, ISRtaster, LOW);       //Aufruf der ISRtaster beim Drückjen des Tasters

  pixels.begin();
  LichtAus();

  // Serial.begin(9600);
}

void ISRtaster() {
  if((millis() - alteZeit) > entprellZeit) { 
    // innerhalb der entprellZeit nichts machen
    if(Licht == 0) { 
      Licht = 1;
      }
    else if(Licht == 1)  { 
      Licht = 2;
      }
    else { 
      Licht = 0;
      }
    }
    alteZeit = millis(); // letzte Schaltzeit merken      
  }


void loop() {
  if(LichtStatus != 1 && Licht == 1){
      LichtAnRot();
    }   
  if(LichtStatus != 2 && Licht == 2){
      LichtAnWeiss();
    }  
  if(LichtStatus !=0 && Licht == 0){
      LichtAus();
    }   
  // Serial.println(Licht);
}

void LichtAnRot(){

  for(int n=0;n<21;n=n+2){
      pixels.setPixelColor(n, pixels.Color(Helligkeit,0,0));
    }   
  for(int n=21;n<90;n++){
    pixels.setPixelColor(n, pixels.Color(Helligkeit,0,0));
  } 
  for(int n=90;n<112;n=n+2){
    pixels.setPixelColor(n, pixels.Color(Helligkeit,0,0));
  } 
  pixels.show();
  LichtStatus = 1;
}

void LichtAnWeiss(){

  for(int n=0;n<21;n=n+2){
      pixels.setPixelColor(n, pixels.Color(Helligkeit,Helligkeit,Helligkeit));
    }   
  for(int n=21;n<90;n++){
    pixels.setPixelColor(n, pixels.Color(Helligkeit,Helligkeit,Helligkeit));
  } 
  for(int n=90;n<112;n=n+2){
    pixels.setPixelColor(n, pixels.Color(Helligkeit,Helligkeit,Helligkeit));
  } 
  pixels.show();
  LichtStatus = 2;
}

void LichtAus(){

  for(int n=0;n<112;n++){
     pixels.setPixelColor(n, pixels.Color(0,0,0));
  }
  pixels.show();
  LichtStatus = 0;   
}
