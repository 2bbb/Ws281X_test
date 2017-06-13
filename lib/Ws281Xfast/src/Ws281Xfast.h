#ifndef Ws281XFAST_H
#define Ws281XFAST_H
#include "resouce/teenst32_FastReg.h"
#include "LedsClockRate.h"

template<LED_TYPE leds_type, std::size_t NUMPIXEL, uint8_t DATAPIN>
class Ws281Xfast{
public:
    Ws281Xfast()
    : dataTrans{ &Ws281Xfast::dataZero
                ,&Ws281Xfast::dataOne
               }
    , dataTransLast{ &Ws281Xfast::dataZeroLast
                    ,&Ws281Xfast::dataOneLast
               }
    {}

    auto init(const bool isOpenDrainMode = false)
    -> typename LedsClockRate<leds_type>::true_type
    {
        t32fr_FastRegs fastReg;
        dataSetReg = fastReg.getRagPack(DATAPIN).cppSet;
        dataClerReg = fastReg.getRagPack(DATAPIN).cppClear;
        dataMask = fastReg.getRagPack(DATAPIN).bMask;
        t32fr_util::changeModeDigitalWrite(DATAPIN,isOpenDrainMode); // OPENDRAIN
        dataTrans[0] = &Ws281Xfast::dataZero;
        dataTrans[1] = &Ws281Xfast::dataOne;
    }

    volatile void show(){
        disableInterapt();
        for(pixelCounter = 0 ; pixelCounter < NUMPIXEL ; ++pixelCounter){
            indexCounter = pixelCounter * 3;
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 1].bit7])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 1].bit6])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 1].bit5])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 1].bit4])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 1].bit3])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 1].bit2])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 1].bit1])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 1].bit0])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 0].bit7])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 0].bit6])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 0].bit5])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 0].bit4])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 0].bit3])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 0].bit2])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 0].bit1])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 0].bit0])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 2].bit7])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 2].bit6])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 2].bit5])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 2].bit4])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 2].bit3])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 2].bit2])();
            (this->*dataTrans[colorBuffer.colorArray[indexCounter + 2].bit1])();
            (this->*dataTransLast[colorBuffer.colorArray[indexCounter + 2].bit0])();
        }
        dataReset();
        enableInterapt();
    }

    uint8_t& operator [](const std::size_t index){
        return this -> colorBuffer.colorArray[index].raw;
    }

private:
    volatile void dataZero(){
        dataHigh();
        waitClock((LedsClockRate<leds_type>::T0H >> 2) + 2);
        dataLow();
        waitClock((LedsClockRate<leds_type>::T0L >> 2) - 2);
    }

    volatile void dataOne(){
        dataHigh();
        waitClock((LedsClockRate<leds_type>::T1H >> 2) + 2);
        dataLow();
        waitClock((LedsClockRate<leds_type>::T1L >> 2) - 2);
    }

    volatile void dataZeroLast(){
        dataHigh();
        waitClock((LedsClockRate<leds_type>::T0H >> 2) + 2);
        dataLow();
    }

    volatile void dataOneLast(){
        dataHigh();
        waitClock((LedsClockRate<leds_type>::T1H >> 2) + 2);
        dataLow();
    }

    volatile void dataReset(){
        waitClock(LedsClockRate<leds_type>::TRST >> 1);
    }


    volatile inline void waitClock(uint32_t clockNum){
        asm volatile(
            "L_%=_waitClock:subs %0, #1"   "\n\t"
            "bne L_%=_waitClock"           "\n\t"
            : "+r" (clockNum) :
        );
    }

    struct ColorBuffer{
        ColorBuffer(){}
        union BitSet{
            struct{
                uint8_t bit0:1;
                uint8_t bit1:1;
                uint8_t bit2:1;
                uint8_t bit3:1;
                uint8_t bit4:1;
                uint8_t bit5:1;
                uint8_t bit6:1;
                uint8_t bit7:1;
            };
            uint8_t raw;
        };
        BitSet colorArray[NUMPIXEL * 3];
    };
public:
    ColorBuffer colorBuffer;

private:

    volatile inline void dataHigh(){
        *dataSetReg = dataMask;
    }
    volatile inline void dataLow(){
        *dataClerReg = dataMask;
    }

    inline void disableInterapt(){
        asm volatile("CPSID i":::"memory");
    }

    inline void enableInterapt(){
        asm volatile("CPSIE i":::"memory");
    }

    uint32_t pixelCounter;
    uint32_t indexCounter;
    volatile uint32_t* dataSetReg;
    volatile uint32_t* dataClerReg;
    uint32_t dataMask;
    volatile void (Ws281Xfast::*dataTrans[2])();
    volatile void (Ws281Xfast::*dataTransLast[2])();

};
#endif /* end of include guard: Ws281XFAST_H */
