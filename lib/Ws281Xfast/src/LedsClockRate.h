#ifndef LEDS_CLOCK_RATE_H
#define LEDS_CLOCK_RATE_H
#include <stdint.h>
enum LED_TYPE{
    WS2812,
    WS2812B,
    WS2813,
    WS2813B,
};

template<LED_TYPE type>
struct LedsClockRate{
    typedef void false_type;
};

#define NSEC(x) (x)
#define USEC(x) (NSEC(1000 * x))
#define MSEC(x) (USEC(1000 * x))
#define SEC(x) (MSEC(1000 * x))
#define STOCLOCK(x) (1.0 * x / 13.8 + 0.5 - 3)

template<>
struct LedsClockRate<WS2812>{
    typedef void true_type;
    static constexpr uint32_t T0H = STOCLOCK(NSEC(350));
    static constexpr uint32_t T0L = STOCLOCK(NSEC(800));
    static constexpr uint32_t T1H = STOCLOCK(NSEC(700));
    static constexpr uint32_t T1L = STOCLOCK(NSEC(600));
    static constexpr uint32_t TRST = STOCLOCK(USEC(50));
};

template<>
struct LedsClockRate<WS2812B>{
    typedef void true_type;
    static constexpr uint32_t T0H = STOCLOCK(NSEC(400));
    static constexpr uint32_t T0L = STOCLOCK(NSEC(850));
    static constexpr uint32_t T1H = STOCLOCK(NSEC(800));
    static constexpr uint32_t T1L = STOCLOCK(NSEC(450));
    static constexpr uint32_t TRST = STOCLOCK(USEC(50));
};

template<>
struct LedsClockRate<WS2813>{
    typedef void true_type;
    static constexpr uint32_t T0H = STOCLOCK(NSEC(300));
    static constexpr uint32_t T0L = STOCLOCK(NSEC(400));
    static constexpr uint32_t T1H = STOCLOCK(NSEC(750));
    static constexpr uint32_t T1L = STOCLOCK(NSEC(400));
    static constexpr uint32_t TRST = STOCLOCK(USEC(250));
};

template<>
struct LedsClockRate<WS2813B>{
    typedef void true_type;
    static constexpr uint32_t T0H = STOCLOCK(NSEC(300));
    static constexpr uint32_t T0L = STOCLOCK(NSEC(400));
    static constexpr uint32_t T1H = STOCLOCK(NSEC(750));
    static constexpr uint32_t T1L = STOCLOCK(NSEC(400));
    static constexpr uint32_t TRST = STOCLOCK(USEC(250));
};

#undef NSEC
#undef USEC
#undef MSEC
#undef SEC
#undef STOCLOCK

#endif /* end of include guard:LEDS_CLOCK_RATE_H */
