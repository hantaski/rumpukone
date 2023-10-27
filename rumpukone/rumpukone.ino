
#define TIMER_INTERRUPT_DEBUG         1
#define _TIMERINTERRUPT_LOGLEVEL_     4

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "RPi_Pico_TimerInterrupt.h"
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

#define TIMER1_INTERVAL_MS    1000
int i_0=0;
int i_1=0;
int i_2=0;
int i_3=0;
int i_4=0;
int i_5=0;
int i_6=0;
int i_7=0;
int tot=0;

bool TimerHandler1(struct repeating_timer *t)
{
  (void) t;
  tot=(s_00[i_0++]+s_01[i_1++]+s_02[i_2++]+s_03[i_3++]+s_04[i_4++]+s_05[i_5++]+s_06[i_6++]+s_07[i_7++]) >> 3;

  if (i_0==s_00_len) i_0=0;
  if (i_1==s_01_len) i_1=0;
  if (i_2==s_02_len) i_2=0;
  if (i_3==s_03_len) i_3=0;
  if (i_4==s_04_len) i_4=0;
  if (i_5==s_05_len) i_5=0;
  if (i_6==s_06_len) i_6=0;
  if (i_7==s_07_len) i_7=0;

  analogWrite(2,tot);

  return true;
}


void setup()
{
  pinMode(outputPin1, OUTPUT);
  
  Serial.begin(115200);
  while (!Serial);


  analogWriteFreq(100000);
  analogWriteResolution(16);
  analogWrite(2,32768);

  Serial.print(F("\nStarting Argument_Simple on ")); Serial.println(BOARD_NAME);
  Serial.println(RPI_PICO_TIMER_INTERRUPT_VERSION);
  Serial.print(F("CPU Frequency = ")); Serial.print(F_CPU / 1000000); Serial.println(F(" MHz"));

  if (ITimer1.attachInterruptInterval(23, TimerHandler1))
  {
    Serial.print(F("Starting ITimer1 OK, millis() = ")); Serial.println(millis());

#if (TIMER_INTERRUPT_DEBUG > 1)    
    Serial.print(F("OutputPin1 = ")); Serial.print(outputPin1);
#endif    
  }
  else
    Serial.println(F("Can't set ITimer1. Select another freq. or timer"));


}

void loop()
{
}