//
//  NullWolf DS3231.h
//  RTC, EEPROM, TEMP, IIC test
//
//  Created by NullWolf on 06/05/16.
//  
//

#ifndef DS3231_h
#define DS3231_h


#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "simple_twi.h"


#define  DS3231_ADDRESS      0x68
#define  DS3231_REG_SEC		 0x00
#define  DS3231_REG_MIN		 0x01
#define  DS3231_REG_HOUR     0x02
#define  DS3231_REG_DOW		 0x03
#define  DS3231_REG_DATE     0x04
#define  DS3231_REG_MON		 0x05
#define  DS3231_REG_YEAR     0x06
#define  DS3231_REG_CON		 0x0E
#define  DS3231_REG_STATUS	 0x0F
#define  DS3231_REG_AGING	 0x10
#define  DS3231_REG_TEMPM	 0x11
#define  DS3231_REG_TEMPL	 0x12


// Convert normal decimal numbers to binary coded decimal
uint8_t decimalToBcd(uint8_t val){
    return( (val/10*16) + (val%10) );
}

// Convert binary coded decimal to normal decimal numbers
uint8_t bcdToDec(uint8_t val){
    return( (val/16*10) + (val%16) );
}



void DS3231_setTime(uint8_t second, uint8_t minute,uint8_t hour,
                    uint8_t dayOfWeek,
                    uint8_t dayOfMonth,
                    uint8_t month,
                    uint8_t year){
    
    
    twi_START();
    twi_writeChar(DS3231_ADDRESS<<1|TW_WRITE);
    twi_writeChar(0x00);    //move pointer location 0 which is seconds
    twi_writeChar(decimalToBcd(second));
    twi_writeChar(decimalToBcd(minute));
    twi_writeChar(decimalToBcd(hour));
    twi_writeChar(decimalToBcd(dayOfWeek));
    twi_writeChar(decimalToBcd(dayOfMonth));
    twi_writeChar(decimalToBcd(month));
    twi_writeChar(decimalToBcd(year));
    twi_STOP();
    
    
}

void DS3231_getTime(uint8_t *second, uint8_t *minute,
                    uint8_t *hour,
                    uint8_t *dayOfWeek,
                    uint8_t *dayOfMonth,
                    uint8_t *month,
                    uint8_t *year){
    
    twi_START();
    twi_writeChar(DS3231_ADDRESS<<1|TW_WRITE);
    twi_writeChar(0x00);            // set DS3231 register pointer to 00h
    twi_STOP();
    
    twi_START();
    twi_writeChar(DS3231_ADDRESS<<1|TW_READ);
    
    *second     = bcdToDec(twi_readChar_ACK() & 0x7f);
    *minute     = bcdToDec(twi_readChar_ACK());
    *hour       = bcdToDec(twi_readChar_ACK() & 0x3f);
    *dayOfWeek  = bcdToDec(twi_readChar_ACK());
    *dayOfMonth = bcdToDec(twi_readChar_ACK());
    *month      = bcdToDec(twi_readChar_ACK());
    *year       = bcdToDec(twi_readChar_ACK());
    
}


float DS3231_getTemperature(void){
//    uint8_t _msb = _readRegister(REG_TEMPM);
//    uint8_t _lsb = _readRegister(REG_TEMPL);
//    return (float)_msb + ((_lsb >> 6) * 0.25f);
    
    uint8_t tmpMsbbuf[1];
    uint8_t tmpLsbbuf[1];

    twi_read(DS3231_ADDRESS, 1, DS3231_REG_TEMPM, tmpMsbbuf);
    twi_read(DS3231_ADDRESS, 1, DS3231_REG_TEMPL, tmpLsbbuf);
    
    return (float)tmpMsbbuf[0] + ((tmpLsbbuf[0] >> 6) * 0.25f);
}

#endif /* DS3231_h */

