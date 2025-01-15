#include <Arduino.h>
#include <vector>
#include "pitches.h"
#include "pins.h"

//buffer for storing the order of buttons
std::vector<int> buffer;
std::vector<int> playerBuffer;


bool isPlayerInput = false;
//
const size_t MAX_SCOPE = 20;

const size_t BTNS[] = {BUTTON_RED_PIN,BUTTON_GREEN_PIN,BUTTON_BLUE_PIN,BUTTON_YELLOW_PIN};
const size_t LEDS[]={LED_RED_PIN,LED_GREEN_PIN,LED_BLUE_PIN,LED_YELLOW_PIN};
const int tunes[] = {NOTE_C4,NOTE_F4,NOTE_D4,NOTE_G4};
const size_t SIZE_BTNS =4;
#pragma region DefinesFunc
void clearBuffers();
void resetBuffer();
void addNewBtnToBuffer(const size_t newValue);
void playBuffer();
void playSoundAndLed(const size_t btn,size_t time = 500);
void playerInput();
void checkPlayerInput(int playerBtn);
void loseGame();
void winGame();
void checkBuffer();
#pragma endregion DefinesFunc

void setup()
{
  for (size_t i = 0; i < SIZE_BTNS; i++)
  {
    pinMode(BTNS[i],INPUT_PULLUP);
    pinMode(LEDS[i],OUTPUT);
  }
  randomSeed(analogRead(0));
  resetBuffer();
  playBuffer();
}

void loop()
{
  playerInput();
  if (!isPlayerInput){
    delay(500);
     playBuffer();}
}

#pragma region GameFunc
void clearBuffers()
{
  buffer.clear();
  playerBuffer.clear();
}

//Clear the game buffer and add a random number.
void resetBuffer()
{
  
  clearBuffers();
  addNewBtnToBuffer(random(SIZE_BTNS));
}

void addNewBtnToBuffer(const size_t newValue)
{
  buffer.push_back(newValue);
}
//go through the game buffer, and give the player a move
void playBuffer()
{
  for (size_t i = 0 ; i < buffer.size();i++)
  {
    playSoundAndLed(buffer[i]);
    delay(250);
  }
  isPlayerInput = true;
}

void playSoundAndLed(const size_t btn, size_t time = 500)
{
  digitalWrite(LEDS[btn], HIGH);
  tone(SPEAKER_PIN, tunes[btn]);
  delay(time);
  digitalWrite(LEDS[btn],LOW);
  noTone(SPEAKER_PIN);
}

void playerInput()
{
  if(!isPlayerInput) return;
  for (size_t activeBtn = 0; activeBtn < SIZE_BTNS; activeBtn++)
  {
    if(digitalRead(BTNS[activeBtn])==LOW)
    {
      playSoundAndLed(activeBtn);

      playerBuffer.push_back(activeBtn);
      
      checkPlayerInput(activeBtn);

    }
  }
}

void checkPlayerInput(int playerBtn)
{
  size_t playerStep = playerBuffer.size()-1;

  if (buffer[playerStep] == playerBtn)
  {
    
    checkBuffer();
    
  }else{
    loseGame();
  }

  if(buffer.size() > MAX_SCOPE) winGame();
}
void loseGame()
{
  #pragma region PlayLeds
  for (size_t i = 0; i < 3; i++)
  {
    for (size_t j = 0; j < SIZE_BTNS; j++)
    {
      digitalWrite(LEDS[j],HIGH);
    }
    tone(SPEAKER_PIN,NOTE_A1);
    delay(250);
    for (size_t j = 0; j < SIZE_BTNS; j++)
    {
      digitalWrite(LEDS[j],LOW);
    }
    noTone(SPEAKER_PIN);
    delay(250);
  }
  #pragma endregion PlayLeds
  resetBuffer();
  playBuffer();

  
}
void winGame()
{
  #pragma region PlayLeds
  const int waveTimes = 3;
  for (size_t i = 0; i < waveTimes; i++)
  {
    for (size_t l = 0;l < SIZE_BTNS; l++)
    {
      playSoundAndLed(l,250);
    }
  }
  #pragma endregion PlayLeds

  resetBuffer();
}

//check whether the player has gone through the entire buffer
void checkBuffer()
{
  
  if(buffer.size() == playerBuffer.size())
  {
    addNewBtnToBuffer(random(SIZE_BTNS));
    isPlayerInput = false;
    playerBuffer.clear();

  }
}

#pragma endregion GameFunc