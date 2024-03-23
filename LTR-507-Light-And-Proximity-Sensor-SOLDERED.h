/**
 **************************************************
 *
 * @file        LTR-507-Light-And-Proximity-Sensor-SOLDERED.h
 * @brief       Header file for LTR-507 breakout.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Robert @ Soldered.com
 ***************************************************/

#ifndef __LTR_507_Light_Sensor__
#define __LTR_507_Light_Sensor__

#include "Arduino.h"
#include "libs/Generic-easyC/easyC.hpp"

// The registers and constants used for working with the LTR-507
#define LTR507_ALS_CONTR_REG     0x80
#define LTR507_PS_CONTR_REG      0x81
#define LTR507_PS_LED_REG        0x82
#define LTR507_PS_N_PULSES_REG   0x83
#define LTR507_PS_MEAS_RATE_REG  0x84
#define LTR507_ALS_MEAS_PATE_REG 0x85

#define LTR507_ALS_STAND_BY_MODE 0
#define LTR507_ALS_ACTIVE_MODE   2

#define LTR507_ALS_GAIN_RANGE1 0x00 // Default
#define LTR507_ALS_GAIN_RANGE2 0x01
#define LTR507_ALS_GAIN_RANGE3 0x02
#define LTR507_ALS_GAIN_RANGE4 0x03

#define LTR507_ALS_ADC_BIT_WIDTH_20BIT 0x00 // Integration time = 1200ms
#define LTR507_ALS_ADC_BIT_WIDTH_19BIT 0x01 // Integration time = 600ms
#define LTR507_ALS_ADC_BIT_WIDTH_18BIT 0x02 // Integration time = 300ms
#define LTR507_ALS_ADC_BIT_WIDTH_17BIT 0x03 // Integration time = 150ms
#define LTR507_ALS_ADC_BIT_WIDTH_16BIT 0x04 // Integration time = 75ms, Default
#define LTR507_ALS_ADC_BIT_WIDTH_12BIT 0x05 // Integration time = 4.685ms
#define LTR507_ALS_ADC_BIT_WIDTH_8BIT  0x06 // Integration time = 292us
#define LTR507_ALS_ADC_BIT_WIDTH_4BIT  0x07 // Integration time = 18us

// ALS measurement time must be set to be equal or larger than integration time
#define LTR507_ALS_MEASUREMENT_RATE_100MS  0x00
#define LTR507_ALS_MEASUREMENT_RATE_200MS  0x01
#define LTR507_ALS_MEASUREMENT_RATE_500MS  0x02 // Default
#define LTR507_ALS_MEASUREMENT_RATE_1000MS 0x03
#define LTR507_ALS_MEASUREMENT_RATE_2000MS 0x04

#define LTR507_LED_CURRENT_DUTY_DEFAULT 0x01

#define LTR507_PS_MEASUREMENT_RATE_12_5MS 0x00
#define LTR507_PS_MEASUREMENT_RATE_50MS   0x01
#define LTR507_PS_MEASUREMENT_RATE_70MS   0x02
#define LTR507_PS_MEASUREMENT_RATE_100MS  0x03 // Default
#define LTR507_PS_MEASUREMENT_RATE_200MS  0x04
#define LTR507_PS_MEASUREMENT_RATE_500MS  0x05
#define LTR507_PS_MEASUREMENT_RATE_1000MS 0x06
#define LTR507_PS_MEASUREMENT_RATE_2000MS 0x07

#define LTR507_PS_STAND_BY_MODE 0
#define LTR507_PS_ACTIVE_MODE   1

#define LTR507_LED_PULSE_FREQ_30KHZ  0x00
#define LTR507_LED_PULSE_FREQ_40KHZ  0x01
#define LTR507_LED_PULSE_FREQ_50KHZ  0x02
#define LTR507_LED_PULSE_FREQ_60KHZ  0x03 // Default
#define LTR507_LED_PULSE_FREQ_70KHZ  0x04
#define LTR507_LED_PULSE_FREQ_80KHZ  0x05
#define LTR507_LED_PULSE_FREQ_90KHZ  0x06
#define LTR507_LED_PULSE_FREQ_100KHZ 0x07

#define LTR507_LED_PEAK_CURRENT_5MA  0x00
#define LTR507_LED_PEAK_CURRENT_10MA 0x01
#define LTR507_LED_PEAK_CURRENT_20MA 0x02
#define LTR507_LED_PEAK_CURRENT_50MA 0x03 // LTR507 default

#define LTR507_INTERRUPT_TRIGGER 1

// Interrupt tigger INT PIN is low level(INT PIN must Connect pull-up resistor to VDD) default
#define LTR507_INTERRUPT_POLARITY_LOGIC_0 0
// Interrupt tigger INT PIN is high level(INT PIN must Connect pull-down resistor to GND)
#define LTR507_INTERRUPT_POLARITY_LOGIC_1 1

#define LTR507_INTERRUPT_MODE_INACTIVE       0 // interrupt pin is inactive/high impedance state (default)
#define LTR507_INTERRUPT_MODE_PS_TRIGGER     1 // only ps can tigger interrupt
#define LTR507_INTERRUPT_MODE_ALS_TRIGGER    2 // only als can tigger interrupt
#define LTR507_INTERRUPT_MODE_PS_ALS_TRIGGER 3 // both ps and als can tigger interrupt

#define LTR507_EVERY_VALUE_OUTSIDE_TIGGER_INTERRUPT 0 // every ps value outside threshold range
#define LTR507_2_VALUES_OUTSIDE_TIGGER_INTERRUPT    1
#define LTR507_3_VALUES_OUTSIDE_TIGGER_INTERRUPT    2
#define LTR507_4_VALUES_OUTSIDE_TIGGER_INTERRUPT    3
#define LTR507_5_VALUES_OUTSIDE_TIGGER_INTERRUPT    4
#define LTR507_6_VALUES_OUTSIDE_TIGGER_INTERRUPT    5
#define LTR507_7_VALUES_OUTSIDE_TIGGER_INTERRUPT    6
#define LTR507_8_VALUES_OUTSIDE_TIGGER_INTERRUPT    7
#define LTR507_9_VALUES_OUTSIDE_TIGGER_INTERRUPT    8
#define LTR507_10_VALUES_OUTSIDE_TIGGER_INTERRUPT   9
#define LTR507_11_VALUES_OUTSIDE_TIGGER_INTERRUPT   10
#define LTR507_12_VALUES_OUTSIDE_TIGGER_INTERRUPT   11
#define LTR507_13_VALUES_OUTSIDE_TIGGER_INTERRUPT   12
#define LTR507_14_VALUES_OUTSIDE_TIGGER_INTERRUPT   13
#define LTR507_15_VALUES_OUTSIDE_TIGGER_INTERRUPT   14
#define LTR507_16_VALUES_OUTSIDE_TIGGER_INTERRUPT   15

#define LTR507_PS_MODE_MASK               0x02
#define LTR507_PS_MODE_SHIFT              1
#define LTR507_LED_PULSE_FREQ_MASK        0xE0
#define LTR507_LED_PULSE_FREQ_SHIFT       5
#define LTR507_LED_DUTY_CYCLE_MASK        0x18
#define LTR507_LED_DUTY_CYCLE_SHIFT       3
#define LTR507_LED_PEAK_CURRENT_MASK      0x07
#define LTR507_PS_DATA_LOW_MASK           0xFF
#define LTR507_PS_DATA_HIGH_MASK          0x07
#define LTR507_ALS_INTERRUPT_STATUS_MASK  0x08
#define LTR507_ALS_INTERRUPT_STATUS_SHIFT 3
#define LTR507_PS_INTERRUPT_STATUS_MASK   0x02
#define LTR507_PS_INTERRUPT_STATUS_SHIFT  1
#define LTR507_INTERRUPT_POLARITY_MASK    0x04
#define LTR507_INTERRUPT_POLARITY_SHIFT   2
#define LTR507_INTERRUPT_MODE_MASK        0x03
#define LTR507_PS_THRES_UP_1_MASK         0x07
#define LTR507_PS_THRES_LOW_1_MASK        0x07
#define LTR507_PS_INTERRUPT_PERSIST_MASK  0xF0
#define LTR507_PS_INTERRUPT_PERSIST_SHIFT 4
#define LTR507_ALS_INTERRUPT_PERSIST_MASK 0x0F

#define LTR507_ALS_DATA_0_REG        0x88
#define LTR507_ALS_DATA_1_REG        0x89
#define LTR507_ALS_PS_STATUS_REG     0x8A
#define LTR507_PS_DATA_LOW_REG       0x8B
#define LTR507_PS_DATA_HIGH_REG      0x8C
#define LTR507_ALS_DATA_CH1_0_REG    0x8D
#define LTR507_ALS_DATA_CH1_1_REG    0x8E
#define LTR507_ALS_DATA_CH1_2_REG    0x8F
#define LTR507_ALS_DATA_CH2_0_REG    0x90
#define LTR507_ALS_DATA_CH2_1_REG    0x91
#define LTR507_ALS_DATA_CH2_2_REG    0x92
#define LTR507_INTERRUPT_REG         0x98
#define LTR507_PS_THRES_UP_0_REG     0x99
#define LTR507_PS_THRES_UP_1_REG     0x9A
#define LTR507_PS_THRES_LOW_0_REG    0x9B
#define LTR507_PS_THRES_LOW_1_REG    0x9C
#define LTR507_ALS_THRES_UP_0_REG    0x9E
#define LTR507_ALS_THRES_UP_1_REG    0x9F
#define LTR507_ALS_THRES_LOW_0_REG   0xA0
#define LTR507_ALS_THRES_LOW_1_REG   0xA1
#define LTR507_INTERRUPT_PERSIST_REG 0xA4

#define LTR507_ALS_MODE_MASK           0x02
#define LTR507_ALS_MODE_SHIFT          0
#define LTR507_ALS_GAIN_MASK           0x18
#define LTR507_ALS_GAIN_SHIFT          3
#define LTR507_ALS_ADC_BIT_WIDTH_MASK  0xE0
#define LTR507_ALS_ADC_BIT_WIDTH_SHIFT 5
#define LTR507_ALS_MEASURE_RATE_MASK   0x07
#define LTR507_ALS_MEASURE_RATE_SHIFT  0
#define LTR507_ALS_DATA_LOW_MASK       0xF0
#define LTR507_ALS_DATA_MID_MASK       0xFF
#define LTR507_ALS_DATA_HIGH_MASK      0xFF
#define LTR507_PS_PULSES_MASK          0xFF
#define LTR507_PS_MEAS_RATE_MASK       0x07
#define LTR507_VALID_PS_DATA_MASK      0x10
#define LTR507_VALID_PS_DATA_SHIFT     4

#define LTR507_ADDRESS 0x3A

class LTR507 : public EasyC
{
  public:
    LTR507(){};
    void init();
    void setPSMode(bool mode);
    void setALSMode(bool mode);
    void setLEDPulseFreq(uint8_t freq);
    void setLEDDutyCycle(uint8_t duty);
    void setPSMeasRate(uint8_t psMeasRate);
    void setLEDPeakCurrent(uint8_t peakCurrent);
    void setPSNumPulses(uint8_t numPulses);
    void setALSGain(uint8_t alsGain);
    void setALSBitWidth(uint8_t alsBitWidth);
    void setALSMeasRate(uint8_t alsMeasRate);

    uint16_t getLightIntensity();
    uint16_t getProximity();

  protected:
    void initializeNative();

  private:
    uint8_t raw[2];
};

#endif
