#include "allhead.h"

uint16_t ui_state;

RTC_TimeTypeDef sTime = {0};
RTC_DateTypeDef DateToUpdate = {0};

void oled_show(void)
{
    if (ui_state == 0)
    {
        OLED_Printf(0, 0, OLED_8X16, "20%02d-%02d-%02d", DateToUpdate.Year, DateToUpdate.Month, DateToUpdate.Date);
        OLED_Printf(0, 20, OLED_8X16, "%02d:%02d:%02d", sTime.Hours, sTime.Minutes, sTime.Seconds);
    }
    OLED_Update();
}

void time_update(void)
{
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);
}
