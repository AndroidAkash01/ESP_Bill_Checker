#include <Arduino.h>
#include <time.h>

void initTime() {
    const long gmtOffset_sec = 3600;
    const int daylightOffset_sec = 3600;

    configTime(gmtOffset_sec, daylightOffset_sec, "pool.ntp.org");

    struct tm timeinfo;
    while (!getLocalTime(&timeinfo)) {
        delay(500);
    }
}

int getCurrentHour() {
    struct tm timeinfo;

    if (!getLocalTime(&timeinfo)) {
        return 0;
    }

    return timeinfo.tm_hour;
}