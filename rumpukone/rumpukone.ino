
#define TIMER_INTERRUPT_DEBUG         1
#define _TIMERINTERRUPT_LOGLEVEL_     4

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "RPi_Pico_TimerInterrupt.h"
#include "kick.h"
unsigned int outputPin1 = LED_BUILTIN;

// Init RPI_PICO_Timer
RPI_PICO_Timer ITimer1(1);

#define TIMER1_INTERVAL_MS    1000
int i=0;

bool TimerHandler1(struct repeating_timer *t)
{
  (void) t;
  Serial.println("foo "+i);
  analogWrite(2,kick[i++]);
  if (i==kick_len) i=0;
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

  if (ITimer1.attachInterruptInterval(22, TimerHandler1))
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