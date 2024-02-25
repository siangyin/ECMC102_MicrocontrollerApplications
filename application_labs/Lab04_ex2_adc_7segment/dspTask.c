#include <xc.h>
#include "config.h"

unsigned int adc_GetConversion(void);
void sevseg_DspAll(unsigned int cnt);

void dspTask_OnSevSeg(void) {
    unsigned int result;
    result = adc_GetConversion();
    sevseg_DspAll(result);
}