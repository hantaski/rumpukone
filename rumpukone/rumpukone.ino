
#define TIMER_INTERRUPT_DEBUG         1
#define _TIMERINTERRUPT_LOGLEVEL_     4

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "RPi_Pico_TimerInterrupt.h"
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

#include <stdio.h>
#include "pico/stdlib.h"

#include "samples/00.h"
#include "samples/01.h"
#include "samples/02.h"
#include "samples/03.h"
#include "samples/04.h"
#include "samples/05.h"
#include "samples/06.h"
#include "samples/07.h"
unsigned int outputPin1 = LED_BUILTIN;

// Init RPI_PICO_Timer
RPI_PICO_Timer ITimer1(1);

// USB MIDI object
Adafruit_USBD_MIDI usb_midi;

// Create a new instance of the Arduino MIDI Library,
// and attach usb_midi as the transport.
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);

#define TIMER1_INTERVAL_MS    1000
int i_0=0;
int i_1=0;
int i_2=0;
int i_3=0;
int i_4=0;
int i_5=0;
int i_6=0;
int i_7=0;
unsigned int tot=0;

bool TimerHandler1(struct repeating_timer *t)
{
  (void) t;
  tot=(s_00[i_0]+s_01[i_1]+s_02[i_2]+s_03[i_3]+s_04[i_4]+s_05[i_5]+s_06[i_6]+s_07[i_7]) >> 3;
  if (i_0<s_00_len) i_0++;
  if (i_1<s_01_len) i_1++;
  if (i_2<s_02_len) i_2++;
  if (i_3<s_03_len) i_3++;
  if (i_4<s_04_len) i_4++;
  if (i_5<s_05_len) i_5++;
  if (i_6<s_06_len) i_6++;
  if (i_7<s_07_len) i_7++;

  analogWrite(2,tot);

  return true;
}

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
    // Log when a note is pressed.
  Serial.print("Note on: channel = ");
  Serial.print(channel);

  Serial.print(" pitch = ");
  Serial.print(pitch);

  Serial.print(" velocity = ");
  Serial.println(velocity);

  digitalWrite(LED_BUILTIN,HIGH);

  switch(pitch) {
    case 36:
      i_0=0;
    case 37:
      i_1=0;
    case 38:
      i_2=0;
    case 39:
      i_3=0;
    case 40:
      i_4=0;
    case 41:
      i_5=0;
    case 42:
      i_6=0;
    case 43:
      i_7=0;
  }
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
    // Log when a note is released.
  Serial.print("Note off: channel = ");
  Serial.print(channel);

  Serial.print(" pitch = ");
  Serial.print(pitch);

  Serial.print(" velocity = ");
  Serial.println(velocity);
  digitalWrite(LED_BUILTIN,LOW);
}


void setup()
{
  pinMode(outputPin1, OUTPUT);

#if defined(ARDUINO_ARCH_MBED) && defined(ARDUINO_ARCH_RP2040)
  // Manual begin() is required on core without built-in support for TinyUSB such as mbed rp2040
  TinyUSB_Device_Init(0);
#endif

  pinMode(LED_BUILTIN, OUTPUT);
  usb_midi.setStringDescriptor("TinyUSB MIDI");

  analogWriteFreq(100000);
  analogWriteResolution(16);
  analogWrite(2,32768);

  ITimer1.attachInterruptInterval(23, TimerHandler1);

  // Initialize MIDI, and listen to all MIDI channels
  // This will also call usb_midi's begin()
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // Attach the handleNoteOn function to the MIDI Library. It will
  // be called whenever the Bluefruit receives MIDI Note On messages.
  MIDI.setHandleNoteOn(handleNoteOn);

  // Do the same for MIDI Note Off messages.
  MIDI.setHandleNoteOff(handleNoteOff);
  Serial.begin(115200);
  Serial.println("starting");

  // wait until device mounted
  while( !TinyUSBDevice.mounted() ) delay(1);

  Serial.println("started");

}

void loop()
{
  // read any new MIDI messages
  MIDI.read();  

}


