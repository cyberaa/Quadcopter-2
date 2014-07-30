#include "quadcopter.h"
#include "simpletools.h"
#include "simplei2c.h"
#include <propeller.h>
#include <stdio.h>

void motorRun()
{
  while(1)
  {
    int signal = xbeeGetByte();
    if (signal == 0x01)
      motorWakeup();
    else if (signal == 0x02)
      motorRun();
    else if (signal == 0x03)
      motorStop();
  }
}

void motorGo()
{
  pwm_set(4, 0, 2000);
}

void motorStop()
{
  pwm_set(4, 0, 1000);
}

void motorWakeup()
{
  pwm_start(20000);
  pwm_set(4, 0, 1000);
}

void run(int pulse)
{
  //printf("%d\n", pulse);
  int temp;
  for(int i=0;i<150+300;i++)
  {
    temp = CNT;
    low(4);
    waitcnt(temp + CLKFREQ/pulse);
    high(4);
    waitcnt(temp + CLKFREQ/480); // 50hz
  }
}