#include "Ws281Xfast.h"
#include <Arduino.h>
constexpr uint16_t numP = 144;

uint8_t mode = 0;

uint32_t timeBuf = 0;
uint32_t counter = 0;

void changeColor(){



    Serial.print("frameRate ");
    Serial.println(counter);
    timeBuf = millis();
    counter = 0;
}

int main(){
    Ws281Xfast<WS2812B,numP,6> test;
    Ws281Xfast<WS2813B,numP,7> test2;

    test.init();
    test2.init();
    Serial.begin(115200);


    IntervalTimer timer;
    timer.begin(changeColor, 1000000);
    for(;;){

        for(int i = 0 ; i < numP ; ++i){
                test2[i * 3 + 0] = test[i * 3 + 0] = numP - abs(i - mode);
                test2[i * 3 + 1] = test[i * 3 + 1] = abs(i - mode);
                test2[i * 3 + 2] = test[i * 3 + 2] = sin(mode / 10.0) * 100;

        }
        test.show();
        test2.show();



        ++counter;
        if(++ mode > numP){
            mode = 0;
        }

    }
}
