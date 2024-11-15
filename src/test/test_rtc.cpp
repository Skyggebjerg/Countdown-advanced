/**
 * @file test_rtc.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-05-26
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "test.h"
#include "cplus_RTC.h"
// #include "../../lib/rtc/cplus_RTC.h"

time_t TrumpStop = 1863622800; //Unixtime for 20.january 2029 at noon in Washington DC
time_t CountDown; // Seconds until TrumpStop

namespace TEST
{

    cplus_RTC _rtc;

// Function to convert date and time to Unix time
time_t convertToUnixTime(int year, int month, int day, int hour, int minute, int second) {
    struct tm t;
    t.tm_year = year - 1900; // Year since 1900
    t.tm_mon = month - 1;    // Month, where 0 = jan
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = second;
    t.tm_isdst = -1;         // Not considering daylight saving time

    return mktime(&t);
}

void convertSecondsToDHMS(time_t totalSeconds, int &Restdays, int &Resthours, int &Restminutes, int &Restseconds) {
    Restdays = totalSeconds / 86400; // 86400 seconds in a day
    totalSeconds %= 86400;
    Resthours = totalSeconds / 3600; // 3600 seconds in an hour
    totalSeconds %= 3600;
    Restminutes = totalSeconds / 60; // 60 seconds in a minute
    Restseconds = totalSeconds % 60; // remaining seconds
}

    void TEST::DisplayRTC()
    {

        display->setFont(&fonts::Font0);

        Disbuff->fillRect(0, 0, 240, 135, Disbuff->color565(0, 0, 0));
        // Displaybuff();
        _rtc.GetBm8563Time();
        RTC_TimeTypeDef time;
        _rtc.GetTime(&time);
        RTC_DateTypeDef date;
        _rtc.GetDate(&date);

        Disbuff->setTextSize(4);
        Disbuff->setCursor(6, 25);
        Disbuff->setTextColor(TFT_WHITE);

        while (1)
        {
            Disbuff->fillRect(0, 0, 240, 135, Disbuff->color565(0, 0, 0));
            _rtc.GetTime(&time);
            _rtc.GetDate(&date);
            time_t unixTime = convertToUnixTime(date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
            
            // Calculate countdown
            time_t countdown = TrumpStop - unixTime;
            int Restdays, Resthours, Restminutes, Restseconds;
            convertSecondsToDHMS(countdown, Restdays, Resthours, Restminutes, Restseconds);

            Disbuff->setTextSize(4);
            Disbuff->setTextColor(TFT_WHITE);
            Disbuff->setCursor(25, 100);
            Disbuff->printf("%02d:%02d:%02d", time.Hours, time.Minutes, time.Seconds);
            Disbuff->setCursor(25, 50);
            Disbuff->printf("%02d:%02d:%02d", Resthours, Restminutes, Restseconds);
            //Disbuff->printf("%d days %02d:%02d:%02d", Restdays, Resthours, Restminutes, Restseconds); // Countdown to TrumpStop
            //Disbuff->setCursor(0, 100);
            //Disbuff->printf("%02d:%02d:%04d", date.Date, date.Month, date.Year);

            Disbuff->fillRect(0, 0, 240, 25, Disbuff->color565(20, 20, 20));
            Disbuff->setTextSize(2);
            Disbuff->setCursor(10, 5);
            Disbuff->printf("%d days ", Restdays); // Countdown to TrumpStop
           // Disbuff->printf("%ld", TrumpStop-unixTime); // Countdown to TrumpStop
            //Disbuff->drawString("TRUMP Time", 5, 5, &fonts::Font0);

            
            if (is_test_mode)
            {
                display->setFont(&fonts::efontCN_24);
                display->setTextColor(TFT_YELLOW, TFT_BLACK);
                display->setTextSize(1);
                display->setCursor(0, 80);
                display->printf("确保数值正常且变化");
                display->setFont(&fonts::Font0);
            }

            Displaybuff(); //display->update();

            // M5.update();
            // checkAXPPress();
            delay(100);

            checkReboot();
            if (checkNext())
            {
                break;
            }
        }
    }

    void TEST::rtc_init()
    {
        // rtc.begin();
        _rtc.clearIRQ();
        _rtc.disableIRQ();
    }

    void TEST::rtc_test()
    {
        printf("rtc test\n");
        DisplayRTC();
        printf("quit rtc test\n");
    }

    void TEST::rtc_wakeup_test()
    {
        display->fillScreen(TFT_BLACK);
        display->setCursor(0, 10);
        display->setFont(&fonts::efontCN_24);
        display->setTextColor(TFT_YELLOW);
        display->setTextSize(1);
        display->printf(" [RTC 唤醒测试]\n - 请移除电源 -\n\n 按下按键[关机]\n 数秒后将自动启动");
        displayUpdate();

        while (1)
        {
            if (btnA.pressed())
            {
                _tone(5000, 50);
                break;
            }
            if (btnB.pressed())
            {
                _tone(5500, 50);
                break;
            }
            if (btnPWR.pressed())
            {
                _tone(3500, 50);
                break;
            }
        }

        // waitNext();
        _rtc.clearIRQ();
        _rtc.SetAlarmIRQ(4);
        display->fillScreen(TFT_BLACK);
        displayUpdate();
        delay(500);
        // power_off();

        digitalWrite(POWER_HOLD_PIN, 0);

        while (1)
        {
            printf("%d\n", btnPWR.read());
            delay(50);
        }
    }

}
