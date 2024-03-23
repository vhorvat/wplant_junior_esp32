/**
 **************************************************
 *
 * @file        LTR-507-Light-And-Proximity-Sensor-SOLDERED.cpp
 * @brief       Functions file for LTR-507 breakout.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Robert @ Soldered.com
 ***************************************************/

#include "LTR-507-Light-And-Proximity-Sensor-SOLDERED.h"

/**
 * @brief                   Overloaded function for virtual in base class to
 * initialize sensor specific.
 */
void LTR507::initializeNative()
{
}

/**
 * @brief                   Function which initializes sensor, also begins I2C communication
 *
 * @returns                 none
 *
 */
void LTR507::init()
{
    // Init I2C (easyC) communication
    begin(LTR507_ADDRESS);

    // Begin measuring
    setALSMode(true);
    setPSMode(true);

    // Configure PS and ALS mode with default settings
    setALSGain(LTR507_ALS_GAIN_RANGE1);
    setALSBitWidth(LTR507_ALS_ADC_BIT_WIDTH_16BIT);
    setALSMeasRate(LTR507_ALS_MEASUREMENT_RATE_100MS);
    setLEDPulseFreq(LTR507_LED_PULSE_FREQ_60KHZ);
    setLEDDutyCycle(LTR507_LED_CURRENT_DUTY_DEFAULT);
    setPSMeasRate(LTR507_PS_MEASUREMENT_RATE_100MS);
    setLEDPeakCurrent(LTR507_LED_PEAK_CURRENT_50MA);
    setPSNumPulses(1);
}

/**
 * @brief                   Function that enables or disables PS measurements
 *
 * @param                   bool mode: true to enable, false to disable
 */
void LTR507::setPSMode(bool mode)
{
    char read;
    uint8_t tmp;
    uint8_t toWrite[2];
    readRegister(LTR507_PS_CONTR_REG, &read, 1);
    read &= (~LTR507_PS_CONTR_REG);
    tmp = (mode << LTR507_PS_MODE_SHIFT) & LTR507_PS_MODE_MASK;
    toWrite[1] = read | tmp;
    toWrite[0] = LTR507_PS_CONTR_REG;
    sendData(toWrite, 2);
}

/**
 * @brief                   Function that enables or disables ALS measurements
 *
 * @param                   bool mode: true to enable, false to disable
 */
void LTR507::setALSMode(bool mode)
{
    uint8_t reg_state[2];
    char buff;
    readRegister(LTR507_ALS_CONTR_REG, &buff, sizeof(char));
    if (mode)
    {
        reg_state[1] = buff | 0x02;
    }
    else
    {
        reg_state[1] = buff & 0xFD;
    }
    reg_state[0] = LTR507_ALS_CONTR_REG;
    sendData(reg_state, sizeof(uint8_t) * 2);
}

/**
 * @brief                   Function that sets the pulse frequency of the LED
 *
 * @param                   uint8_t freq:
 *                           You can use:
 *                          -LTR507_LED_PULSE_FREQ_30KHZ
 *                          -LTR507_LED_PULSE_FREQ_40KHZ
 *                          -LTR507_LED_PULSE_FREQ_50KHZ
 *                          -LTR507_LED_PULSE_FREQ_60KHZ
 *                          -LTR507_LED_PULSE_FREQ_70KHZ
 *                          -LTR507_LED_PULSE_FREQ_80KHZ
 *                          -LTR507_LED_PULSE_FREQ_90KHZ
 *                          -LTR507_LED_PULSE_FREQ_100KHZ
 */
void LTR507::setLEDPulseFreq(uint8_t freq)
{
    char read;
    uint8_t tmp, toWrite;
    readRegister(LTR507_PS_LED_REG, &read, 1);
    read &= (~LTR507_LED_PULSE_FREQ_MASK);
    tmp = (freq << LTR507_LED_PULSE_FREQ_SHIFT) & LTR507_LED_PULSE_FREQ_MASK;
    toWrite = read | tmp;
    sendAddress(LTR507_PS_LED_REG);
    sendData(&toWrite, 1);
}

/**
 * @brief                   Function that sets the duty cycle of the LED
 *
 * @param                   uint8_t duty:
 *                           You can use:
 *                          -LTR507_LED_CURRENT_DUTY_DEFAULT
 */
void LTR507::setLEDDutyCycle(uint8_t duty)
{
    char read;
    uint8_t tmp;
    uint8_t toWrite[2];
    readRegister(LTR507_PS_LED_REG, &read, 1);
    read &= (~LTR507_LED_DUTY_CYCLE_MASK);
    tmp = (duty << LTR507_LED_DUTY_CYCLE_SHIFT) & LTR507_LED_DUTY_CYCLE_MASK;
    toWrite[1] = read | tmp;
    toWrite[0] = LTR507_PS_LED_REG;
    sendData(toWrite, 0);
}

/**
 * @brief                   Function that sets the measuring rate of the proximity sensor
 *
 * @param                   uint8_t psMeasRate:
 *                           You can use:
 *                          -LTR507_PS_MEASUREMENT_RATE_12_5MS
 *                          -LTR507_PS_MEASUREMENT_RATE_50MS
 *                          -LTR507_PS_MEASUREMENT_RATE_70MS
 *                          -LTR507_PS_MEASUREMENT_RATE_100MS
 *                          -LTR507_PS_MEASUREMENT_RATE_200MS
 *                          -LTR507_PS_MEASUREMENT_RATE_500MS
 *                          -LTR507_PS_MEASUREMENT_RATE_1000MS
 *                          -LTR507_PS_MEASUREMENT_RATE_2000MS
 */
void LTR507::setPSMeasRate(uint8_t psMeasRate)
{
    uint8_t tmp;
    uint8_t toWrite[2];
    tmp = psMeasRate & LTR507_PS_MEAS_RATE_MASK;
    toWrite[1] = tmp;
    toWrite[0] = LTR507_PS_MEAS_RATE_REG;
    sendData(toWrite, 2);
}

/**
 * @brief                   Function that sets the peak current of the LED
 *
 * @param                   uint8_t peakCurrent:
 *                           You can use:
 *                          -LTR507_LED_PEAK_CURRENT_5MA
 *                          -LTR507_LED_PEAK_CURRENT_10MA
 *                          -LTR507_LED_PEAK_CURRENT_20MA
 *                          -LTR507_LED_PEAK_CURRENT_50MA
 */
void LTR507::setLEDPeakCurrent(uint8_t peakCurrent)
{
    char read;
    uint8_t tmp;
    uint8_t toWrite[2];
    readRegister(LTR507_PS_LED_REG, &read, 1);
    read &= (~LTR507_LED_PEAK_CURRENT_MASK);
    tmp = peakCurrent & LTR507_LED_PEAK_CURRENT_MASK;
    toWrite[1] = read | tmp;
    sendAddress(LTR507_PS_LED_REG);
    sendData(toWrite, 2);
}

/**
 * @brief                   Function that sets the number of pulses for each measurement
 *
 * @param                   uint8_t numPulses:
 *                           You can use values from 1 to 15. Default is 1.
 */
void LTR507::setPSNumPulses(uint8_t numPulses)
{
    // Fix values if it's out of range
    if (numPulses > 15)
        numPulses = 15;
    if (numPulses < 1)
        numPulses = 1;

    uint8_t tmp;
    uint8_t toWrite[2];
    tmp = numPulses & LTR507_PS_PULSES_MASK;
    toWrite[1] = tmp;
    toWrite[0] = LTR507_PS_N_PULSES_REG;
    sendData(toWrite, 2);
}

/**
 * @brief                   Function that sets the gain for ALS measurement
 *
 * @param                   uint8_t alsGain:
 *                           You can use:
 *                          -LTR507_ALS_GAIN_RANGE1
 *                          -LTR507_ALS_GAIN_RANGE2
 *                          -LTR507_ALS_GAIN_RANGE3
 *                          -LTR507_ALS_GAIN_RANGE4
 */
void LTR507::setALSGain(uint8_t alsGain)
{
    char read;
    uint8_t tmp;
    uint8_t toWrite[2];
    readRegister(LTR507_ALS_CONTR_REG, &read, 1);
    read &= (~LTR507_ALS_GAIN_MASK);
    tmp = (alsGain << LTR507_ALS_GAIN_SHIFT) & LTR507_ALS_GAIN_MASK;
    toWrite[1] = read | tmp;
    toWrite[0] = LTR507_ALS_CONTR_REG;
    sendData(toWrite, 2);
}

/**
 * @brief                   Function that sets ALS measurement bit width
 *
 * @param                   uint8_t bitWidth:
 *                           You can use:
 *                          -LTR507_ALS_ADC_BIT_WIDTH_20BIT
 *                          -LTR507_ALS_ADC_BIT_WIDTH_19BIT
 *                          -LTR507_ALS_ADC_BIT_WIDTH_18BIT
 *                          -LTR507_ALS_ADC_BIT_WIDTH_17BIT
 *                          -LTR507_ALS_ADC_BIT_WIDTH_16BIT
 *                          -LTR507_ALS_ADC_BIT_WIDTH_12BIT
 *                          -LTR507_ALS_ADC_BIT_WIDTH_8BIT
 *                          -LTR507_ALS_ADC_BIT_WIDTH_4BIT
 */
void LTR507::setALSBitWidth(uint8_t alsBitWidth)
{
    char read;
    uint8_t tmp;
    uint8_t toWrite[2];
    readRegister(LTR507_ALS_MEAS_PATE_REG, &read, 1);
    read &= (~LTR507_ALS_ADC_BIT_WIDTH_MASK);
    tmp = (alsBitWidth << LTR507_ALS_ADC_BIT_WIDTH_SHIFT) & LTR507_ALS_ADC_BIT_WIDTH_MASK;
    toWrite[1] = read | tmp;
    toWrite[0] = LTR507_ALS_MEAS_PATE_REG;
    sendData(toWrite, 2);
}

/**
 * @brief                   Function that sets ALS measurement rate
 *
 * @param                   uint8_t alsMeasRate:
 *                           You can use:
 *                          -LTR507_ALS_MEASUREMENT_RATE_100MS
 *                          -LTR507_ALS_MEASUREMENT_RATE_200MS
 *                          -LTR507_ALS_MEASUREMENT_RATE_500MS
 *                          -LTR507_ALS_MEASUREMENT_RATE_1000MS
 *                          -LTR507_ALS_MEASUREMENT_RATE_2000MS
 */
void LTR507::setALSMeasRate(uint8_t alsMeasRate)
{
    char read;
    uint8_t tmp;
    uint8_t toWrite[2];
    readRegister(LTR507_ALS_MEAS_PATE_REG, &read, 1);
    read &= (~LTR507_ALS_MEASURE_RATE_MASK);
    tmp = (alsMeasRate << LTR507_ALS_MEASURE_RATE_SHIFT) & LTR507_ALS_MEASURE_RATE_MASK;
    toWrite[1] = read | tmp;
    toWrite[0] = LTR507_ALS_MEAS_PATE_REG;
    sendData(toWrite, 2);
}

/**
 * @brief                   Get the light intensity
 *
 * @returns                 uint16_t, the light intensity value read by the sensor
 */
uint16_t LTR507::getLightIntensity()
{
    // First, check if the status is valid
    readRegister(LTR507_ALS_PS_STATUS_REG, (char *)raw, sizeof(uint8_t));
    if (!(0x4 & raw[0]))
        return 0;

    // Read ALS data and return it as a combined uint16_t
    readRegister(LTR507_ALS_DATA_0_REG, (char *)raw, 2);
    return raw[0] | raw[1] << 8;
}

/**
 * @brief                   Get the proximity
 *
 * @returns                 uint16_t, the proximity value read by the sensor
 */
uint16_t LTR507::getProximity()
{
    // Read ALS data and return it as a combined uint16_t
    readRegister(LTR507_PS_DATA_LOW_REG, (char *)raw, 2);
    raw[0] &= LTR507_PS_DATA_LOW_MASK;
    raw[1] &= LTR507_PS_DATA_HIGH_MASK;
    return raw[0] | raw[1] << 8;
}
