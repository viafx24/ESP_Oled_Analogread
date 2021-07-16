
#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h> // Guillaume add

Adafruit_ADS1115 ads1115;

const int Pin_33 = 33;
const int Pin_32 = 32;
const int Pin_35 = 35;
const int Pin_34 = 34;

const uint8_t Number_Samples = 255;

const uint8_t Offset = 159;

uint16_t ADC_Pin_33, ADC_Pin_32, ADC_Pin_35, ADC_Pin_34;

uint16_t ADC_Pin_33_Array[Number_Samples];
uint16_t ADC_Pin_32_Array[Number_Samples];
uint16_t ADC_Pin_35_Array[Number_Samples];
uint16_t ADC_Pin_34_Array[Number_Samples];

uint16_t ADC_Pin_33_Average, ADC_Pin_32_Average, ADC_Pin_35_Average, ADC_Pin_34_Average;

uint16_t adc0, adc1, adc2, adc3;

uint16_t adc0_Corrected, adc1_Corrected, adc2_Corrected, adc3_Corrected;

uint16_t average(uint16_t *array, uint8_t len) // assuming array is int.
{
  long sum = 0L; // sum will be larger than an item, long for safety.
  for (int i = 0; i < len; i++)
    sum += array[i];
  return sum / len; // return an int not a float
}

void setup(void)
{

  Serial.begin(115200);
  ads1115.begin();
}

void loop(void)
{
  for (uint8_t i = 6; i < 250; i++)
  {
    dacWrite(25, i);

    adc0_Corrected = (ads1115.readADC_SingleEnded(0) * (6.144 / 3.3) * pow(2, 12)) / pow(2, 15);


    for (uint8_t j = 0; j < Number_Samples; j++) // 32 à la base semblait suffisant.
    {
      ADC_Pin_34_Array[j] = analogRead(Pin_34);
    }

    ADC_Pin_34_Average = average(ADC_Pin_34_Array, Number_Samples) + Offset;

    Serial.print(i);
    Serial.print(",");
    Serial.println(adc0_Corrected - ADC_Pin_34_Average);




    delay(10);

  }
}
