#include "allhead.h"

uint16_t ui_state;
uint16_t battery_value = 100;

RTC_TimeTypeDef sTime = {0};
RTC_DateTypeDef DateToUpdate = {0};

void oled_show(void)
{
    if (ui_state == 0)
    {
        OLED_Printf(0, 0, OLED_6X8, "20%02d-%02d-%02d", DateToUpdate.Year, DateToUpdate.Month, DateToUpdate.Date);
        OLED_Printf(16, 20, OLED_12x24, "%02d:%02d:%02d", sTime.Hours, sTime.Minutes, sTime.Seconds);
        OLED_Printf(0, 48, OLED_8X16, "菜单");
        OLED_Printf(96, 48, OLED_8X16, "设置");
        OLED_Printf(96, 48, OLED_8X16, "设置");
        OLED_Printf(88, 4, OLED_6X8, "100%%");
        OLED_ShowImage(112, 0, 16, 16, battery);
    }
    OLED_Update();
}

void time_update(void)
{
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);
}
