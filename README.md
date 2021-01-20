# DS3231-RTC-AVR-Atmega-Library
ATmega compatible library for the DS3231 RTC.
## Functionality:

```C
DS3231_setTime(); // initialize the RTC to a particular date and time.

DS3231_getTime(); // returns the current date and time stored on the RTC.

DS3231_getTemperature(); // the RTC has a built in temperature sensor, this returns the read temperature.
```
