#include "pitches.h"
#include "Servo.h"

const int buzzer = 11; //Define pin 10, can use other PWM pins  (5,6 or 9)
                       //Note pins 3 and 11 can't be used when using the tone function in Arduino Uno
const int songspeed = 1.5; //Change to 2 for a slower version of the song, the bigger the number the slower the song
Servo myservo;
// notes in the melody:
int notes[] = {       //Note of the song, 0 is a rest/pulse
      NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,

   NOTE_A4, NOTE_A4,  
   //Repeat of first part
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,

   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,
   //End of Repeat

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
};
//*****************************************
int duration[] = {         //duration of each note (in ms) Quarter Note is set to 250 ms
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,

  250, 125,
  //Rpeat of First Part
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,
  //End of Repeat
  
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500,

  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500
};

int buttonInput = 13;
int buttonState = 0;
int winCounter = 0;
int totalPins = 11;
void setup() {
  myservo.attach(10);
  myservo.write(0);
  Serial.begin(9600);
  //sets up the pins
  for(int i=1;i<9;i++){
    pinMode(i,OUTPUT);
  } 
  pinMode(13,INPUT);
}   

void loop() {//runs through the pins and turns the LED's on/off
  bool buttonLock = false;
  for(int i=1;i<totalPins;i++){
    myservo.write((winCounter)*36);
    digitalWrite(i,HIGH);
    //where the delay begins/checking for button every 1ms
    for(int t=0;t<15;t++){
      delay(1);
      
      buttonState = digitalRead(13);
      if(buttonState == LOW && i != 6){//sets the button lock if you press on the wrong LED
        buttonLock = true;
        buttonState = HIGH;
      }
      if(i == 6 && buttonLock == false){//checks for button lock and correct LED
        buttonState=digitalRead(13);
      }
      
      if(buttonState==LOW && i==6 && buttonLock == false){
        winCounter++;
    for(int t=0;t<5;t++){
      
      for (int i=0;i<totalPins;i++) {
        digitalWrite (i, HIGH);
      
      }
      delay (100);
      for (int i=0;i<totalPins;i++) {
       digitalWrite (i, LOW);
      }
      delay (100);
    }
    delay(400);
    
        if(winCounter==5){//checks to see if you have won the game;
         gameWin();
        }
      }
    }
    //where the delay code ends
    digitalWrite(i,LOW);
    
  } 
}   
void gameWin(){//this method is when the game wins. Flashes LED's and plays song
  myservo.write(180);
  
  while(true){
   int pinCounter = 1;
   for (int i=0;i<203;i++){              //203 is the total number of music notes in the song
      int wait = duration[i] * songspeed;
      digitalWrite(pinCounter,HIGH);
      tone(buzzer,notes[i],wait);          //tone(pin,frequency,duration)
      delay(wait);
      digitalWrite(pinCounter,LOW);
      pinCounter ++;
      if(pinCounter > 8){
        pinCounter = 1;
      }
   }  //delay is used so it doesn't go to the next loop before tone is finished playing
      //You can click reset on Arduino to replay the song

  }
}
 
 


