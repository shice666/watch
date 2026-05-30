#include "allhead.h"

uint16_t ui_state, ui_state_last = 99;
uint16_t battery_value = 100;
uint16_t key1, key2, key3, key4, key1_last, key2_last, key3_last, key4_last;
uint16_t key_value;
int select0, select10, select21, select11, select12;
int year, month, date, hour, minute, second;
uint16_t select21_state;
uint32_t cnt21;
uint16_t cnt21_state;
RTC_TimeTypeDef sTime = {0};
RTC_DateTypeDef DateToUpdate = {0};
uint16_t icon_x[] = {48, 92, 136, 180, 224};
const uint16_t icon_y = 16;
int icon_x_change;
uint32_t cnt10;
int icon_x_change_current;
uint16_t hour_11, minute_11, second_11;
uint16_t miaobiao_state;
uint32_t cnt11;
uint16_t time_clear_state;
uint32_t cnt11_time;
int16_t ax, ay, az, gx, gy, gz;
double roll_g, pitch_g, yaw_g;
double roll_a, pitch_a;
double roll, pitch, yaw;
double a = 0.9;
double delta_t = 0.005;
double pi = 3.1415927;
uint32_t cnt13;

void oled_show(void)
{
    if (ui_state != ui_state_last)
    {
        OLED_Clear();
    }
    if (ui_state == 0)
    {
        OLED_Printf(0, 0, OLED_6X8, "20%02d-%02d-%02d", DateToUpdate.Year, DateToUpdate.Month, DateToUpdate.Date);
        OLED_Printf(16, 20, OLED_12x24, "%02d:%02d:%02d", sTime.Hours, sTime.Minutes, sTime.Seconds);
        OLED_Printf(0, 48, OLED_8X16, "菜单");
        OLED_Printf(96, 48, OLED_8X16, "设置");
        OLED_Printf(88, 4, OLED_6X8, "100%%");
        OLED_ShowImage(112, 0, 16, 16, battery);

        if (select0 == 0)
        {
            OLED_ReverseArea(0, 48, 32, 16);
        }
        else if (select0 == 1)
        {
            OLED_ReverseArea(96, 48, 32, 16);
        }
    }
    else if (ui_state == 20)
    {
        OLED_Printf(0, 0, OLED_8X16, "时间日期设置");
        OLED_ReverseArea(0, 0, 96, 16);
    }
    else if (ui_state == 21)
    {
        OLED_Printf(0, 0, OLED_8X16, "时:%02d", hour);
        OLED_Printf(0, 24, OLED_8X16, "分:%02d", minute);
        OLED_Printf(0, 48, OLED_8X16, "秒:%02d", second);
        OLED_Printf(64, 0, OLED_8X16, "年:20%02d", year);
        OLED_Printf(64, 24, OLED_8X16, "月:%02d", month);
        OLED_Printf(64, 48, OLED_8X16, "日:%02d", date);

        if (select21_state == 0)
        {
            if (select21 == 0)
            {
                OLED_ReverseArea(0, 0, 40, 16);
            }
            if (select21 == 1)
            {
                OLED_ReverseArea(0, 24, 40, 16);
            }
            if (select21 == 2)
            {
                OLED_ReverseArea(0, 48, 40, 16);
            }
            if (select21 == 3)
            {
                OLED_ReverseArea(64, 0, 56, 16);
            }
            if (select21 == 4)
            {
                OLED_ReverseArea(64, 24, 40, 16);
            }
            if (select21 == 5)
            {
                OLED_ReverseArea(64, 48, 40, 16);
            }
        }
        else
        {
            if (HAL_GetTick() - cnt21 >= 500)
            {
                cnt21_state = (cnt21_state + 1) % 2;
                cnt21 = HAL_GetTick();
            }
            if (cnt21_state == 0)
            {
                if (select21 == 0)
                {
                    OLED_ReverseArea(0, 0, 40, 16);
                }
                if (select21 == 1)
                {
                    OLED_ReverseArea(0, 24, 40, 16);
                }
                if (select21 == 2)
                {
                    OLED_ReverseArea(0, 48, 40, 16);
                }
                if (select21 == 3)
                {
                    OLED_ReverseArea(64, 0, 56, 16);
                }
                if (select21 == 4)
                {
                    OLED_ReverseArea(64, 24, 40, 16);
                }
                if (select21 == 5)
                {
                    OLED_ReverseArea(64, 48, 40, 16);
                }
            }
        }
    }
    else if (ui_state == 10)
    {
        if (icon_x_change_current != icon_x_change)
        {
            if (HAL_GetTick() - cnt10 > 10)
            {
                OLED_Clear();
                cnt10 = HAL_GetTick();
                if (icon_x_change > icon_x_change_current)
                {
                    for (int i = 0; i < 5; i++)
                    {
                        icon_x[i] += 4;
                    }
                    icon_x_change_current += 4;
                }
                else if (icon_x_change < icon_x_change_current)
                {
                    for (int i = 0; i < 5; i++)
                    {
                        icon_x[i] -= 4;
                    }
                    icon_x_change_current -= 4;
                }
            }
        }
        OLED_ShowImage(42, 10, 44, 44, biankuang);
        OLED_ShowImage(icon_x[0], icon_y, 32, 32, menu_icon[0]);
        OLED_ShowImage(icon_x[1], icon_y, 32, 32, menu_icon[1]);
        OLED_ShowImage(icon_x[2], icon_y, 32, 32, menu_icon[2]);
        OLED_ShowImage(icon_x[3], icon_y, 32, 32, menu_icon[3]);
        OLED_ShowImage(icon_x[4], icon_y, 32, 32, menu_icon[4]);
    }
    else if (ui_state == 11)
    {
        OLED_Printf(16, 20, OLED_12x24, "%02d:%02d:%02d", hour_11, minute_11, second_11);
        OLED_Printf(8, 48, OLED_8X16, "开始");
        OLED_Printf(48, 48, OLED_8X16, "停止");
        OLED_Printf(88, 48, OLED_8X16, "清除");

        if (select11 == 0)
        {
            OLED_ReverseArea(8, 48, 32, 16);
        }
        else if (select11 == 1)
        {
            OLED_ReverseArea(48, 48, 32, 16);
        }
        else if (select11 == 2)
        {
            OLED_ReverseArea(88, 48, 32, 16);
        }
    }
    else if (ui_state == 12)
    {
        OLED_Printf(20, 16, OLED_12x24, "OFF");
        OLED_Printf(84, 16, OLED_12x24, "ON");

        if (select12 == 0)
        {
            OLED_ReverseArea(20, 16, 36, 24);
        }
        else
        {
            OLED_ReverseArea(84, 16, 24, 24);
        }
    }
    else if (ui_state == 13)
    {
        OLED_Printf(0, 0, OLED_8X16, "roll:%.2f     ", roll);
        OLED_Printf(0, 16, OLED_8X16, "pitch:%.2f     ", pitch);
        OLED_Printf(0, 32, OLED_8X16, "yaw:%.2f     ", yaw);
    }
    else if (ui_state == 14)
    {
        OLED_Clear();
        OLED_DrawCircle(64, 32, 30, 0);
        OLED_DrawCircle(64 + roll, 32 - pitch, 3, 1);
    }
    

    ui_state_last = ui_state;
    OLED_Update();
}

void time_update(void)
{
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);

    HAL_PWR_EnableBkUpAccess();
    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR2, DateToUpdate.Year);
    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR3, DateToUpdate.Month);
    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR4, DateToUpdate.Date);
}

void key_scan(void)
{
    key1 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
    key2 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15);
    key3 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9);
    key4 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11);

    if (key1 == 1 && key1_last == 0)
    {
        HAL_Delay(10);
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == 1)
        {
            key_value = 1;
        }
    }
    else if (key2 == 1 && key2_last == 0)
    {
        HAL_Delay(10);
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15) == 1)
        {
            key_value = 2;
        }
    }
    else if (key3 == 1 && key3_last == 0)
    {
        HAL_Delay(10);
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == 1)
        {
            key_value = 3;
        }
    }
    else if (key4 == 1 && key4_last == 0)
    {
        HAL_Delay(10);
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == 1)
        {
            key_value = 4;
        }
    }
    else
    {
        key_value = 0;
    }

    key1_last = key1;
    key2_last = key2;
    key3_last = key3;
    key4_last = key4;
}

void key_chufa(void)
{
    switch (key_value)
    {
    case 1:
        if (ui_state == 0)
        {
            select0 = (select0 - 1 + 2) % 2;
        }
        else if (ui_state == 21)
        {
            if (select21_state == 0)
            {
                select21 = (select21 - 1 + 6) % 6;
            }
            else
            {
                if (select21 == 0)
                {
                    hour = (hour + 1) % 24;
                }
                if (select21 == 1)
                {
                    minute = (minute + 1) % 60;
                }
                if (select21 == 2)
                {
                    second = (second + 1) % 60;
                }
                if (select21 == 3)
                {
                    year++;
                    if (year > 99)
                    {
                        year = 0;
                    }
                }
                if (select21 == 4)
                {
                    month++;
                    if (month > 12)
                    {
                        month = 1;
                    }
                }
                if (select21 == 5)
                {
                    date++;
                    if (date > 31)
                    {
                        date = 1;
                    }
                }
            }
        }
        else if (ui_state == 10)
        {
            if (select10 > 0)
            {
                icon_x_change += 44;
                select10--;
            }
        }
        else if (ui_state == 11)
        {
            select11 = (select11 - 1 + 3) % 3;
        }
        else if (ui_state == 12)
        {
            select12 = (select12 - 1 + 2) % 2;
        }

        break;
    case 2:
        if (ui_state == 0)
        {
            select0 = (select0 + 1) % 2;
        }
        else if (ui_state == 21)
        {
            if (select21_state == 0)
            {
                select21 = (select21 + 1) % 6;
            }
            else
            {
                if (select21 == 0)
                {
                    hour = (hour - 1 + 24) % 24;
                }
                if (select21 == 1)
                {
                    minute = (minute - 1 + 60) % 60;
                }
                if (select21 == 2)
                {
                    second = (second - 1 + 60) % 60;
                }
                if (select21 == 3)
                {
                    year--;
                    if (year < 0)
                    {
                        year = 99;
                    }
                }
                if (select21 == 4)
                {
                    month--;
                    if (month < 1)
                    {
                        month = 12;
                    }
                }
                if (select21 == 5)
                {
                    date--;
                    if (date < 1)
                    {
                        date = 31;
                    }
                }
            }
        }
        else if (ui_state == 10)
        {
            if (select10 < 4)
            {
                icon_x_change -= 44;
                select10++;
            }
        }
        else if (ui_state == 11)
        {
            select11 = (select11 + 1) % 3;
        }
        else if (ui_state == 12)
        {
            select12 = (select12 + 1) % 2;
        }
        break;
    case 3:
        if (ui_state == 0)
        {
            if (select0 == 0)
            {
                ui_state = 10;
            }
            else if (select0 == 1)
            {
                ui_state = 20;
            }
        }
        else if (ui_state == 20)
        {
            ui_state = 21;
            year = DateToUpdate.Year;
            month = DateToUpdate.Month;
            date = DateToUpdate.Date;
            hour = sTime.Hours;
            minute = sTime.Minutes;
            second = sTime.Seconds;
            select21 = 0;
            select21_state = 0;
        }
        else if (ui_state == 21)
        {
            if (select21_state == 0)
            {
                select21_state = 1;
            }
            else if (select21_state == 1)
            {
                select21_state = 0;
                cnt21_state = 0;
            }
        }
        else if (ui_state == 10)
        {
            if (select10 == 0)
            {
                ui_state = 11;
            }
            else if (select10 == 1)
            {
                ui_state = 12;
            }
            else if (select10 == 2)
            {
                ui_state = 13;
            }
            else if (select10 == 3)
            {
                ui_state = 14;
            }
            else if (select10 == 4)
            {
                ui_state = 15;
            }
        }
        else if (ui_state == 11)
        {
            if (select11 == 0)
            {
                if (miaobiao_state == 0)
                {
                    miaobiao_state = 1;
                    if (time_clear_state == 0)
                    {
                        time_clear_state = 1;
                        cnt11 = HAL_GetTick();
                    }
                    else
                    {
                        cnt11 = HAL_GetTick() - cnt11_time;
                    }
                }
            }
            else if (select11 == 1)
            {
                miaobiao_state = 0;
            }
            else if (select11 == 2)
            {
                if (miaobiao_state == 0)
                {
                    time_clear_state = 0;
                    hour_11 = 0;
                    minute_11 = 0;
                    second_11 = 0;
                }
            }
        }
        else if (ui_state == 12)
        {
            if (select12 == 1)
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
            }
            else
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
            }
        }

        break;
    case 4:
        if (ui_state == 10 || ui_state == 20)
        {
            ui_state = 0;
        }
        else if (ui_state == 21)
        {
            ui_state = 20;

            DateToUpdate.Year = year;
            DateToUpdate.Month = month;
            DateToUpdate.Date = date;
            sTime.Hours = hour;
            sTime.Minutes = minute;
            sTime.Seconds = second;

            HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
            HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);
        }
        else if (ui_state == 11 || ui_state == 12 || ui_state == 13 || ui_state == 14 || ui_state == 15)
        {
            ui_state = 10;
        }

        break;
    default:
        break;
    }
}

void miaobiao(void)
{
    if (miaobiao_state == 1)
    {
        cnt11_time = HAL_GetTick() - cnt11;
        hour_11 = cnt11_time / 1000 / (60 * 60);
        minute_11 = cnt11_time / 1000 % (60 * 60) / 60;
        second_11 = cnt11_time / 1000 % 60;
    }
}

void mpu6050(void)
{
    if (HAL_GetTick() - cnt13 > 5)
    {
        cnt13 = HAL_GetTick();

        MPU6050_GetData(&ax, &ay, &az, &gx, &gy, &gz);

        roll_g = roll + gx * delta_t;
        pitch_g = pitch + gy * delta_t;
        yaw_g = yaw + gz * delta_t;

        pitch_a = atan2(-ax, az) * 180 / pi;
        roll_a = atan2(ay, az) * 180 / pi;

        roll = roll_g * a + roll_a * (1 - a);
        pitch = pitch_g * a + pitch_a * (1 - a);
        yaw = yaw_g * a;
    }
}
