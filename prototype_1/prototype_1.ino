/* prototype_1.ino
*
* Copyright (C) 2015 Alejandro Simon
* License: MIT License http://opensource.org/licenses/MIT
*
* 4 buttons to trigger 4 notes
* 1 Potenciometer to change velocity */

#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

#define CHANNEL 1

const int potPin = A0;
const int button1Pin = 2;
const int button2Pin = 3;
const int button3Pin = 4;
const int button4Pin = 5;
const int buttons [] = {button1Pin, button2Pin,
                        button3Pin, button4Pin};
const byte notes [] = {21, 59, 83, 105};
const int maxButtons = 4;
int val = 0;

void setup() {
  Serial.begin(9600);
  // initialize the pushbutton pin as an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);
}

void sendNote(byte note, byte velo, byte channel) {
  MIDI.sendNoteOn(note, velo, channel);  // Send a Note
  delay(1000);		                 // Wait
  MIDI.sendNoteOff(note, 0, channel);    // Stop the note
}

void loop() {
  // Potenciometer
  val = analogRead(potPin);
  // scale value to [0, 127]
  val = (127 * val)/1023;
  // Buttons
  for (int i=0; i<maxButtons; i++) {
    // Check if button pressed
    if (digitalRead(buttons[i]) == HIGH) {
      sendNote(notes[i], val, CHANNEL);
    }
  }
}
