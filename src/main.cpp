/**
 * @file main.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-05-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <Arduino.h>
#include "test/test.h"

/* time_t convertToUnixTime(int year, int month, int day, int hour, int minute, int second) {
    struct tm t;
    t.tm_year = year - 1900; // Year since 1900
    t.tm_mon = month - 1;    // Month, where 0 = jan
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = second;
    t.tm_isdst = -1;         // Not considering daylight saving time

    return mktime(&t);
} */

TEST::TEST test;

void setup()
{
    test.setup();
}

void loop()
{
    test.loop();
}
