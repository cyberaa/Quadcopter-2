#include "quadcopter.h"
#include "simpletools.h"
#include "simplei2c.h"
#include <propeller.h>
#include <stdio.h>

int main()
{
  waitcnt(CNT + CLKFREQ); // Wait one second. 157 0x35  141 0x15

  high(PIN_XBEE_OUT);

  imuInit();
  cog_run(&imuRun, 1);
  //cog_run(&xbeeRun, 2);
  //xbeeRun();
  
  for (int i=0;i<150;i++)
  {
    printf("%d\n", i);
    xbeeSendByte(i);
    waitcnt(CNT + CLKFREQ/2);
  }

  while(1)
    printf("%d\n", xbeeGetByte());
  
  signed short gx,gy,gz,ax,ay,az;
  
  while(1)
  {
    waitcnt(CNT + CLKFREQ/10);
    getImuData(&gx, &gy, &gz, &ax, &ay, &az);
    gx = computePID(gx, 0);
    printf("G: %5d %5d %5d\t", gx, gy, gz);
    printf("A: %5d %5d %5d\n", ax, ay, az);
  }
}