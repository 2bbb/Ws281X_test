#ifndef Ws281XFAST_H
#define Ws281XFAST_H
#include "resouce/teenst32_FastReg.h"
#include "LedsClockRate.h"

template<LED_TYPE leds_type, std::size_t NUMPIXEL, uint8_t DATAPIN>
class Ws281Xfast{
	using ClockRate = LedsClockRate<leds_type>;
public:
	Ws281Xfast()
	: clock_h{
		(ClockRate::T0H >> 2) + 2,
		(ClockRate::T1H >> 2) + 2}
	, clock_l{
		(ClockRate::T0L >> 2) - 2,
		(ClockRate::T1L >> 2) - 2}
	{}

	auto init(const bool isOpenDrainMode = false)
	-> typename ClockRate::true_type
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
			dataTrans(colorBuffer[indexCounter + 1].bit7]);
			dataTrans(colorBuffer[indexCounter + 1].bit6]);
			dataTrans(colorBuffer[indexCounter + 1].bit5]);
			dataTrans(colorBuffer[indexCounter + 1].bit4]);
			dataTrans(colorBuffer[indexCounter + 1].bit3]);
			dataTrans(colorBuffer[indexCounter + 1].bit2]);
			dataTrans(colorBuffer[indexCounter + 1].bit1]);
			dataTrans(colorBuffer[indexCounter + 1].bit0]);
			
			dataTrans(colorBuffer[indexCounter + 0].bit7]);
			dataTrans(colorBuffer[indexCounter + 0].bit6]);
			dataTrans(colorBuffer[indexCounter + 0].bit5]);
			dataTrans(colorBuffer[indexCounter + 0].bit4]);
			dataTrans(colorBuffer[indexCounter + 0].bit3]);
			dataTrans(colorBuffer[indexCounter + 0].bit2]);
			dataTrans(colorBuffer[indexCounter + 0].bit1]);
			dataTrans(colorBuffer[indexCounter + 0].bit0]);
			
			dataTrans(colorBuffer[indexCounter + 2].bit7]);
			dataTrans(colorBuffer[indexCounter + 2].bit6]);
			dataTrans(colorBuffer[indexCounter + 2].bit5]);
			dataTrans(colorBuffer[indexCounter + 2].bit4]);
			dataTrans(colorBuffer[indexCounter + 2].bit3]);
			dataTrans(colorBuffer[indexCounter + 2].bit2]);
			dataTrans(colorBuffer[indexCounter + 2].bit1]);
			dataTransLast(colorBuffer[indexCounter + 2].bit0]);
		}
		dataReset();
		enableInterapt();
	}

	uint8_t& operator [](const std::size_t index){
		return colorBuffer[index].raw;
	}
	uint8_t operator [](const std::size_t index) const {
		return colorBuffer[index].raw;
	}

private:
	volatile inline void dataTrans(uint8_t b) {
		dataHigh();
		waitClock(clock_h[b]);
		dataLow();
		waitClock(clock_l[b]);
	}
	
	volatile inline void dataTransLast(uint8_t b) {
		dataHigh();
		waitClock(clock_h[b]);
		dataLow();
	}
	
	volatile inline void dataReset(){
		waitClock(ClockRate::TRST >> 1);
	}


	volatile inline void waitClock(uint32_t clockNum){
		asm volatile(
			"L_%=_waitClock:subs %0, #1"   "\n\t"
			"bne L_%=_waitClock"           "\n\t"
			: "+r" (clockNum) :
		);
	}

public:
	union ColorBuffer {
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
	
	ColorBuffer colorBuffer[NUMPIXEL * 3];

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
	const uint8_t clock_h[2];
	const uint8_t clock_l[2];
};
#endif /* end of include guard: Ws281XFAST_H */
