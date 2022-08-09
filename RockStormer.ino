/******************************
   ** Upload Settings **
   Board: "Teensy LC"
   USB Type: "MIDI"
   CPU Speed: "48 Mhz"
 ******************************/

#include <Bounce.h>

//MIDI Channel
#define MIDI_CHANNEL 1
#define POT_CHANNEL 2

//Switch CC Numbers
#define BUT1 38
#define BUT2 39
#define BUT3 40
#define BUT4 41
#define BUT5 42
#define BUT6 43
#define BUT7 44
#define BUT8 45


//Pin Numbers on Teensy
#define L1_PIN 0
#define L2_PIN 1
#define L3_PIN 2
#define L4_PIN 3
#define L5_PIN 4
#define L6_PIN 5
#define L7_PIN 6
#define L8_PIN 7

//Other
#define SWITCHES 8 // How many switches?
#define VELOCITY 127 // ON Velocity
#define BOUNCE_TIME 15 // Debounce Time (in milliseconds)

//Global variables
const int DIGITAL_SWITCHES[SWITCHES] = {L1_PIN,L2_PIN,L3_PIN,L4_PIN,L5_PIN,L6_PIN,L7_PIN,L8_PIN};
const int CC_NUMBER[SWITCHES] = {BUT1,BUT2,BUT3,BUT4,BUT5,BUT6,BUT7,BUT8};

//Set up 'Bounce' Objects
Bounce digital[] =   {
  Bounce(DIGITAL_SWITCHES[0], BOUNCE_TIME),
  Bounce(DIGITAL_SWITCHES[1], BOUNCE_TIME),
  Bounce(DIGITAL_SWITCHES[2], BOUNCE_TIME),
  Bounce(DIGITAL_SWITCHES[3], BOUNCE_TIME),
  Bounce(DIGITAL_SWITCHES[4], BOUNCE_TIME),
  Bounce(DIGITAL_SWITCHES[5], BOUNCE_TIME),
  Bounce(DIGITAL_SWITCHES[6], BOUNCE_TIME),
  Bounce(DIGITAL_SWITCHES[7], BOUNCE_TIME),
};

int pre_value = 0;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < SWITCHES; i++) {
    pinMode(DIGITAL_SWITCHES[i], INPUT_PULLUP);
  }
}

void loop() {
  readSwitches();
  readPot();
  while (usbMIDI.read()) {
  }
}

void readSwitches() {
  static byte input = 0;

  digital[input].update();

  if (digital[input].fallingEdge()) {
    usbMIDI.sendControlChange(CC_NUMBER[input], VELOCITY, MIDI_CHANNEL);
  }
  else if (digital[input].risingEdge()) {
    usbMIDI.sendControlChange(CC_NUMBER[input], 0, MIDI_CHANNEL);
  }

  input++;
  if (input >= SWITCHES) input = 0;
}

void readPot() {
  int value = analogRead(A0)/8;
  if (value > 1 && value <= 116 && value != pre_value){
    usbMIDI.sendControlChange(12, value, POT_CHANNEL);
    pre_value = value;
  }
  else if (value > 116){
    usbMIDI.sendControlChange(12, 127, POT_CHANNEL);
    pre_value = value;
  }
}
