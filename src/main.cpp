#include <Arduino.h>
#include <IBusBM.h>
#include <iostream>
#include <string>
#include <sstream>

#include <TFT_eSPI.h> 
#include <SPI.h>

IBusBM IBus;    // IBus object
int vals[6];    // array to hold channel values
int loopnr = 0; // loop counter

#define AA_FONT_SMALL "NotoSansBold15"
#define AA_FONT_LARGE "NotoSansBold36"

#ifndef TFT_DISPOFF
#define TFT_DISPOFF 0x28
#endif

#ifndef TFT_SLPIN
#define TFT_SLPIN   0x10
#endif

#define ADC_EN          14
#define ADC_PIN         34
#define BUTTON_1        35
#define BUTTON_2        0

TFT_eSPI tft = TFT_eSPI(135, 240); // Invoke custom library

static const char *TAG = "main";

std::stringstream ss;

//! Long time delay, it is recommended to use shallow sleep, which can effectively reduce the current consumption
void espDelay(int ms) //use-> espDelay(6000);
{   
    esp_sleep_enable_timer_wakeup(ms * 1000);
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH,ESP_PD_OPTION_ON);
    esp_light_sleep_start();
}

void setup() {
    // put your setup code here, to run once:

    Serial.begin(115200);     // debug info
    Serial2.begin(115200);    // iBUS input from receiver
    Serial2.setPins(12,13);   // set RX1 to pin 12 and TX1 to pin 13
    
    IBus.begin(Serial2,1);    // iBUS object connected to serial2 RX2 pin and use timer 1

    // adding 2 sensors
    IBus.addSensor(IBUSS_INTV);

    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK, true);
    setCpuFrequencyMhz(240);
}

void loop() {
    // read channel 1-6
    for (int i=0; i<6; i++) {
        vals[i] = IBus.readChannel(i);  // read channel i, value is between 1000 and 2000
        // print channel values
        /*
        Serial.print("Channel ");
        Serial.print(i+1);
        Serial.print(": ");
        Serial.print(vals[i]);
        Serial.print("\t");
        tft.drawString(String(vals[i]), 10, 10, 2);
        */
        ss.str("");
        ss << "Channel " << i+1 << ": " << vals[i] << "\t";
        tft.drawString(ss.str().c_str(), 10, i*16, 2);
        Serial.print(ss.str().c_str());
    }
    // print loop counter
    ss.str("");
    ss << "Loop: " << loopnr++;
    tft.drawString(ss.str().c_str(), 10, 100, 2);
    Serial.println();
    IBus.setSensorMeasurement(0, loopnr); // set sensor value to 1234
    
    espDelay(1000);
}

