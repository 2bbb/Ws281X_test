#ifndef TEENSY32_FAST_REG_H
#define TEENSY32_FAST_REG_H
#include <array>

struct t32fr_PinRegPack{
    t32fr_PinRegPack(volatile uint32_t* cppSet, volatile uint32_t* cppClear, uint32_t bMask)
    : cppSet(cppSet)
    , cppClear(cppClear)
    , bMask(bMask)
    {}
    volatile uint32_t* cppSet;
    volatile uint32_t* cppClear;
    uint32_t bMask;
};

struct t32fr_PortModeRegs{
    t32fr_PortModeRegs()
    : pmr{
        (volatile uint32_t*)0x43fe0ac0,
        (volatile uint32_t*)0x43fe0ac4,
        (volatile uint32_t*)0x43fe1a80,
        (volatile uint32_t*)0x43fe02b0,
        (volatile uint32_t*)0x43fe02b4,
        (volatile uint32_t*)0x43fe1a9c,
        (volatile uint32_t*)0x43fe1a90,
        (volatile uint32_t*)0x43fe1a88,
        (volatile uint32_t*)0x43fe1a8c,
        (volatile uint32_t*)0x43fe128c,
        (volatile uint32_t*)0x43fe1290,
        (volatile uint32_t*)0x43fe1298,
        (volatile uint32_t*)0x43fe129c,
        (volatile uint32_t*)0x43fe1294,
        (volatile uint32_t*)0x43fe1a84,
        (volatile uint32_t*)0x43fe1280,
        (volatile uint32_t*)0x43fe0a80,
        (volatile uint32_t*)0x43fe0a84,
        (volatile uint32_t*)0x43fe0a8c,
        (volatile uint32_t*)0x43fe0a88,
        (volatile uint32_t*)0x43fe1a94,
        (volatile uint32_t*)0x43fe1a98,
        (volatile uint32_t*)0x43fe1284,
        (volatile uint32_t*)0x43fe1288,
        (volatile uint32_t*)0x43fe0294,
        (volatile uint32_t*)0x43fe0acc,
        (volatile uint32_t*)0x43fe2284,
        (volatile uint32_t*)0x43fe12a4,
        (volatile uint32_t*)0x43fe12a0,
        (volatile uint32_t*)0x43fe12a8,
        (volatile uint32_t*)0x43fe12ac,
        (volatile uint32_t*)0x43fe2280,
        (volatile uint32_t*)0x43fe0ac8,
        (volatile uint32_t*)0x43fe0290,
    }
    , pcr{
        (volatile uint32_t*)0x4004a040,
        (volatile uint32_t*)0x4004a044,
        (volatile uint32_t*)0x4004c000,
        (volatile uint32_t*)0x40049030,
        (volatile uint32_t*)0x40049034,
        (volatile uint32_t*)0x4004c01c,
        (volatile uint32_t*)0x4004c010,
        (volatile uint32_t*)0x4004c008,
        (volatile uint32_t*)0x4004c00c,
        (volatile uint32_t*)0x4004b00c,
        (volatile uint32_t*)0x4004b010,
        (volatile uint32_t*)0x4004b018,
        (volatile uint32_t*)0x4004b01c,
        (volatile uint32_t*)0x4004b014,
        (volatile uint32_t*)0x4004c004,
        (volatile uint32_t*)0x4004b000,
        (volatile uint32_t*)0x4004a000,
        (volatile uint32_t*)0x4004a004,
        (volatile uint32_t*)0x4004a00c,
        (volatile uint32_t*)0x4004a008,
        (volatile uint32_t*)0x4004c014,
        (volatile uint32_t*)0x4004c018,
        (volatile uint32_t*)0x4004b004,
        (volatile uint32_t*)0x4004b008,
        (volatile uint32_t*)0x40049014,
        (volatile uint32_t*)0x4004a04c,
        (volatile uint32_t*)0x4004d004,
        (volatile uint32_t*)0x4004b024,
        (volatile uint32_t*)0x4004b020,
        (volatile uint32_t*)0x4004b028,
        (volatile uint32_t*)0x4004b02c,
        (volatile uint32_t*)0x4004d000,
        (volatile uint32_t*)0x4004a048,
        (volatile uint32_t*)0x40049010,
    }
    , pp_pcr(0x144)
    , ode(0x20)
    {}

    std::array<volatile uint32_t*, 34> pmr;
    std::array<volatile uint32_t*, 34> pcr;
    uint32_t pp_pcr;
    uint32_t ode;
};

struct t32fr_util{
    static volatile uint32_t changeModeDigitalWrite(const uint8_t pinNum, const bool isOD = false){
        t32fr_PortModeRegs fpmr;
        volatile uint32_t* pinPmr;
        pinPmr = fpmr.pmr[pinNum];
        *pinPmr = 1;
        volatile uint32_t* pinPcr;
        pinPcr = fpmr.pcr[pinNum];
        *pinPcr = fpmr.pp_pcr;
        if (isOD) {
		    *pinPcr |= fpmr.ode;
		} else {
		    *pinPcr &= ~fpmr.ode;
        }
        return *pinPcr;
    }
};

struct t32fr_FastRegs{
    t32fr_FastRegs()
    : cppSet{
        (volatile uint32_t*)0x400ff044,
        (volatile uint32_t*)0x400ff044,
        (volatile uint32_t*)0x400ff0c4,
        (volatile uint32_t*)0x400ff004,
        (volatile uint32_t*)0x400ff004,
        (volatile uint32_t*)0x400ff0c4,
        (volatile uint32_t*)0x400ff0c4,
        (volatile uint32_t*)0x400ff0c4,
        (volatile uint32_t*)0x400ff0c4,
        (volatile uint32_t*)0x400ff084,
        (volatile uint32_t*)0x400ff084,
        (volatile uint32_t*)0x400ff084,
        (volatile uint32_t*)0x400ff084,
        (volatile uint32_t*)0x400ff084,
        (volatile uint32_t*)0x400ff0c4,
        (volatile uint32_t*)0x400ff084,
        (volatile uint32_t*)0x400ff044,
        (volatile uint32_t*)0x400ff044,
        (volatile uint32_t*)0x400ff044,
        (volatile uint32_t*)0x400ff044,
        (volatile uint32_t*)0x400ff0c4,
        (volatile uint32_t*)0x400ff0c4,
        (volatile uint32_t*)0x400ff084,
        (volatile uint32_t*)0x400ff084,
        (volatile uint32_t*)0x400ff004,
        (volatile uint32_t*)0x400ff044,
        (volatile uint32_t*)0x400ff104,
        (volatile uint32_t*)0x400ff084,
        (volatile uint32_t*)0x400ff084,
        (volatile uint32_t*)0x400ff084,
        (volatile uint32_t*)0x400ff084,
        (volatile uint32_t*)0x400ff104,
        (volatile uint32_t*)0x400ff044,
        (volatile uint32_t*)0x400ff004,
      }
    , cppClear{
        (volatile uint32_t*)0x400ff048,
        (volatile uint32_t*)0x400ff048,
        (volatile uint32_t*)0x400ff0c8,
        (volatile uint32_t*)0x400ff008,
        (volatile uint32_t*)0x400ff008,
        (volatile uint32_t*)0x400ff0c8,
        (volatile uint32_t*)0x400ff0c8,
        (volatile uint32_t*)0x400ff0c8,
        (volatile uint32_t*)0x400ff0c8,
        (volatile uint32_t*)0x400ff088,
        (volatile uint32_t*)0x400ff088,
        (volatile uint32_t*)0x400ff088,
        (volatile uint32_t*)0x400ff088,
        (volatile uint32_t*)0x400ff088,
        (volatile uint32_t*)0x400ff0c8,
        (volatile uint32_t*)0x400ff088,
        (volatile uint32_t*)0x400ff048,
        (volatile uint32_t*)0x400ff048,
        (volatile uint32_t*)0x400ff048,
        (volatile uint32_t*)0x400ff048,
        (volatile uint32_t*)0x400ff0c8,
        (volatile uint32_t*)0x400ff0c8,
        (volatile uint32_t*)0x400ff088,
        (volatile uint32_t*)0x400ff088,
        (volatile uint32_t*)0x400ff008,
        (volatile uint32_t*)0x400ff048,
        (volatile uint32_t*)0x400ff108,
        (volatile uint32_t*)0x400ff088,
        (volatile uint32_t*)0x400ff088,
        (volatile uint32_t*)0x400ff088,
        (volatile uint32_t*)0x400ff088,
        (volatile uint32_t*)0x400ff108,
        (volatile uint32_t*)0x400ff048,
        (volatile uint32_t*)0x400ff008,
      }
    , cppBm{
        (uint32_t)0x10000,
        (uint32_t)0x20000,
        (uint32_t)0x1,
        (uint32_t)0x1000,
        (uint32_t)0x2000,
        (uint32_t)0x80,
        (uint32_t)0x10,
        (uint32_t)0x4,
        (uint32_t)0x8,
        (uint32_t)0x8,
        (uint32_t)0x10,
        (uint32_t)0x40,
        (uint32_t)0x80,
        (uint32_t)0x20,
        (uint32_t)0x2,
        (uint32_t)0x1,
        (uint32_t)0x1,
        (uint32_t)0x2,
        (uint32_t)0x8,
        (uint32_t)0x4,
        (uint32_t)0x20,
        (uint32_t)0x40,
        (uint32_t)0x2,
        (uint32_t)0x4,
        (uint32_t)0x20,
        (uint32_t)0x80000,
        (uint32_t)0x2,
        (uint32_t)0x200,
        (uint32_t)0x100,
        (uint32_t)0x400,
        (uint32_t)0x800,
        (uint32_t)0x1,
        (uint32_t)0x40000,
        (uint32_t)0x10,
      }
    {}
    std::array<volatile uint32_t*, 34> cppSet;
    std::array<volatile uint32_t*, 34> cppClear;
    std::array<uint32_t, 34> cppBm;

    t32fr_PinRegPack getRagPack(const uint8_t pinNum){
        t32fr_PinRegPack prp(cppSet[pinNum], cppClear[pinNum], cppBm[pinNum]);
        return prp;
    }
};

struct FastDigitalWrite{
    FastDigitalWrite(const uint8_t pinNum){
        t32fr_FastRegs fr;
        reg[0] = fr.getRagPack(pinNum).cppClear;
        reg[1] = fr.getRagPack(pinNum).cppSet;
        mask = fr.getRagPack(pinNum).bMask;
    }

    const uint8_t operator =(const uint8_t state){
        *(reg[state]) = mask;
        return state;
    }

private:
    volatile uint32_t* reg[2];
    uint32_t mask;
};

#endif /* end of include guard: TEENSY32_FAST_REG_H */
