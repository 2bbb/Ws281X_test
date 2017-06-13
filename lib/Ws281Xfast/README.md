# Ws2812fast
Ws2812BLED 光る teensy3.2
Improving now...

```cpp:example 
 
    #include "Ws2812fast.h"

    constexpr uint16_t numPixel = 174;

    int main(){
       Ws2812fast<numPixel,6> leds;
       leds.init();
       for(int i = 0 ; i < numPixel ; ++i){
        leds[i * 3 + 0] = 255; //R
        leds[i * 3 + 1] = 255; //G
        leds[i * 3 + 2] = 255; //B
      }
      leds.show(); //nterrupts are prohibited during show
    }
```
