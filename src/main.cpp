#include <Arduino.h>
#include <vector>
#include "pitches.h"
#include "pins.h"

//buffer for storing the order of buttons
std::vector<int> buffer;
std::vector<int> playerBuffer;


bool isPlayerInput = false;

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

}

void loop()
{

}