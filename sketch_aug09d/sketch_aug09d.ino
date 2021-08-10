#include <Encoder.h>
const int NUM_SLIDERS = 1;

//broche vcc sur le 5V
#define PIN 7
#define G 49
#define R 51
#define B 53


Encoder knobMaster(A0,A1);
int analogSliderValues[NUM_SLIDERS];
int Master, Discord, Chrome, Gaming, Music;
int masterMute, discordMute, chromeMute, gamingMute, musicMute;
int masterDebounceTime;
const int masterButton=1;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 175;    // the debounce time; increase if the output flickers

int masterState=0;

void setup() {
  
    // put your setup code here, to run once:
    
  digitalWrite (G, 1);
  digitalWrite (R, 1);
  digitalWrite (B, 1);


    Serial.begin(9600);
  pinMode(masterButton, INPUT_PULLUP);
  pinMode (G, OUTPUT);
  pinMode (R, OUTPUT);
  pinMode (B, OUTPUT);
  
analogSliderValues[0]  = 512;
knobMaster.write(51);
masterMute=0;











  

}

void loop() {
  // put your main code here, to run repeatedly:

digitalWrite (G, 1);
  digitalWrite (R, 1);
  digitalWrite (B, 1);
  delay (100);
  digitalWrite (G, 0);
  digitalWrite (R, 0);
  digitalWrite (B, 0);
  delay (100);
  digitalWrite (G, 1);
  digitalWrite (R, 1);
  digitalWrite (B, 1);
  delay (100);
  digitalWrite (G, 0);
  digitalWrite (R, 0);
  digitalWrite (B, 0);
  delay (2000);


  Master = knobMaster.read();

Encoder checkButtons();
Encoder checkEncoders();
sendSliderValues();


}



void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}
void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}
void checkButtons(){
if (digitalRead(masterButton)==0 && masterState ==0){
masterMute = !masterMute ;
masterState =1;
delay(25);
}
 if (digitalRead(masterButton)==1){
  masterState=0;
 }
}
void checkEncoders(){
      if (Master > 0 && Master < 102 && masterMute==0){
        analogSliderValues[0]=Master*10;
     
    }
    else if (masterMute==0 && (Master > 102 || Master==102)){
        analogSliderValues[0]=102*10;
        knobMaster.write(102);
    }
    else if (masterMute==1){
      analogSliderValues[0]=0;
        
    }
    
    else {
        analogSliderValues[0]=0;
        knobMaster.write(0);
  digitalWrite (G, 0);
  digitalWrite (R, 0);
  digitalWrite (B, 0);
  delay (100);
  digitalWrite (G, 1);
  digitalWrite (R, 1);
  digitalWrite (B, 1);

        
    }
}

/* Arduino : 1.8.15 (Windows Store 1.8.49.0) (Windows 10), Carte : "Arduino Mega or Mega 2560, ATmega2560 (Mega 2560)"

Le croquis utilise 5654 octets (2%) de l'espace de stockage de programmes. Le maximum est de 253952 octets.

Les variables globales utilisent 240 octets (2%) de mémoire dynamique, ce qui laisse 7952 octets pour les variables locales. Le maximum est de 8192 octets.



Ce rapport pourrait être plus détaillé avec
l'option "Afficher les résultats détaillés de la compilation"
activée dans Fichier -> Préférences.*/
