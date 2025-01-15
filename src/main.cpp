#include <Arduino.h>
#include "pitches.h"

#define LED_BLUE 7
#define LED_GREEN 4
#define LED_RED 6
#define LED_YELLOW  5
#define SPEAKER 8

const int led_btns[] = {LED_GREEN, LED_BLUE,LED_RED,LED_YELLOW};
const int btns[] = {
  10,
  11,
  12,
  13,
};
const int tunes[] = {
  NOTE_C4,
  NOTE_F4,
  NOTE_D4,
  NOTE_G4
};

const size_t SIZE_BTNS = sizeof(btns)/sizeof(int);

int * buffer = new int[20];
size_t lastBtn;
bool getInput = true;

void playSoundWithLed(const size_t, size_t timeLed = 1000);
void setNewBtnToBuffer(size_t);
void playBuffer();
void clearBuffer();
void winGame();
void loseGame();


void setup()
{


  for (size_t i = 0; i < SIZE_BTNS; i++)
  {
    pinMode(btns[i], INPUT_PULLUP);
    pinMode(led_btns[i],OUTPUT);
    
  }
  //playSoundWithLed(i);
  clearBuffer();
  setNewBtnToBuffer(random(SIZE_BTNS));
  playBuffer();
}

void loop()
{

  size_t buffer_size = sizeof(buffer)/sizeof(size_t);
  if (getInput)
    for (size_t activeBtn = 0; activeBtn < SIZE_BTNS; activeBtn++)
    {
      if (digitalRead(btns[activeBtn]) == LOW)
      {
        if (activeBtn == lastBtn)
        {
          setNewBtnToBuffer(random(SIZE_BTNS));
          getInput = false;
          playBuffer();
          break;
        }
        else{
          loseGame();
        }
      }
    }



}

void playBuffer()
{
  size_t buffer_size = sizeof(buffer)/sizeof(size_t);
  if (buffer_size == 0) return;
  for(size_t i = 0; i < 20; i++)
  {
    if(buffer[i] == -1) return;
    playSoundWithLed(buffer[i]);
  }
  noTone(SPEAKER);
  for(int i = 0; i <4; i++)
  {
    digitalWrite(led_btns[i], LOW);
  }
  getInput =true;
}

void setNewBtnToBuffer(size_t newBtn)
{
  for (size_t i = 0; i < 20; i++)
  {
    if (buffer[i] == -1)
    {
      buffer[i] = newBtn;
      lastBtn = newBtn;
      return;
    }
    
    /* code */
  }
  
}

void playSoundWithLed(const size_t numLed, size_t timeLed = 1000)
{
  digitalWrite(led_btns[numLed], HIGH);
  tone(SPEAKER, tunes[numLed]);
  delay(timeLed);
  digitalWrite(led_btns[numLed],LOW);
  noTone(SPEAKER);
}



void loseGame()
{
  for (int times = 0; times < 5; times ++){
    for (size_t i = 0; i < SIZE_BTNS; i++)
    {
      digitalWrite(led_btns[i],HIGH);
    }
    delay(500);
        for (size_t i = 0; i < SIZE_BTNS; i++)
    {
      digitalWrite(led_btns[i],LOW);
    }
  }
  clearBuffer();
  setNewBtnToBuffer(random(SIZE_BTNS));
  getInput = false;
  playBuffer();
}

void winGame()
{
  for (int times = 0; times < 5;times ++){
    for (size_t i = 0; i < SIZE_BTNS; i++)
    {
      playSoundWithLed(i,500);
    }
  }
}

void clearBuffer()
{

  for (int i = 0; i < 20; i++)
  {
    buffer[i] = -1;
  }
}