
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

int i_0=_00_len;
int i_1=_01_len;
int i_2=_02_len;
int i_3=_03_len;
int i_4=_04_len;
int i_5=_05_len;
int i_6=_06_len;
int i_7=_07_len;
int tot=0;
int tot2=0;
static const int h=32768;

bool TimerHandler1(struct repeating_timer *t)
{
  (void) t;
  tot=((int)_00[i_0]-h) + ((int)_01[i_1]-h) + ((int)_02[i_2]-h) + ((int)_03[i_3]-h) + ((int)_04[i_4]-h) + ((int)_05[i_5]-h) + ((int)_06[i_6]-h) + ((int)_07[i_7]-h);
//  tot=((int)_00[i_0]-h);
//  tot=_00[0];
  if (i_0<_00_len) i_0++;
  if (i_1<_01_len) i_1++;
  if (i_2<_02_len) i_2++;
  if (i_3<_03_len) i_3++;
  if (i_4<_04_len) i_4++;
  if (i_5<_05_len) i_5++;
  if (i_6<_06_len) i_6++;
  if (i_7<_07_len) i_7++;
  

//  Serial.print(tot);
//  Serial.print(" ");
  tot=(tot >> 1)+h;
//  Serial.println(tot);
  

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
      Serial.println("0");
      break;
    case 37:
      i_1=0;
      Serial.println("1");
      break;
    case 38:
      i_2=0;
      Serial.println("2");
      break;
    case 39:
      i_3=0;
      Serial.println("3");
      break;
    case 40:
      i_4=0;
      Serial.println("4");
      break;
    case 41:
      i_5=0;
      Serial.println("5");
      break;
    case 42:
      i_6=0;
      Serial.println("6");
      break;
    case 43:
      i_7=0;
      Serial.println("7");
      break;
    default:
      Serial.println("muuuu");
      break;
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

  ITimer1.attachInterruptInterval(25, TimerHandler1);

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


