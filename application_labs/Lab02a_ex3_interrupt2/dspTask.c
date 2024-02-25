#include <xc.h>
#include "config.h"

unsigned int extint_GetCount(void);
void sevseg_DspAll(unsigned int cnt);

void dspTask_OnSevSeg(void) {
    unsigned int count;
    count = extint_GetCount();
    sevseg_DspAll(count);
}
