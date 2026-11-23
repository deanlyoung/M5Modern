#pragma once
#include <stdint.h>
namespace paperos {
// Unsigned subtraction handles the millis() wrap for timers shorter than 49 days.
inline uint32_t remainingTimerSeconds(uint32_t durationSeconds, uint32_t startedMs, uint32_t nowMs) {
    const uint32_t elapsedMs = nowMs - startedMs;
    const uint32_t durationMs = durationSeconds * 1000U;
    return elapsedMs >= durationMs ? 0U : (durationMs - elapsedMs + 999U) / 1000U;
}
}
