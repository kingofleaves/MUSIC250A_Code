    #include "ColorSensor.h"
    
    ColorSensor::COLOR ColorSensor::getColor() {
        return current_color;
    }

    void ColorSensor::setup(i2c_t3 *theWire) {
        _wire = theWire;
        if (tcs != NULL) delete tcs; // memory management
        tcs = new Adafruit_TCS34725(_int_time, _gain);
        tcs->begin(TCS34725_ADDRESS, _wire);
    }

    void ColorSensor::setup(tcs34725IntegrationTime_t int_time, tcs34725Gain_t gain, i2c_t3 *theWire) {
        _int_time = int_time;
        _gain = gain;
        _wire = theWire;
        if (tcs != NULL) delete tcs; // memory management
        tcs = new Adafruit_TCS34725(_int_time, _gain);
        tcs->begin(TCS34725_ADDRESS, _wire);
    }


    void ColorSensor::update() {
        tcs->getRawData(&r, &g, &b, &c);

        if (c > 600) {
            current_color = NONE;
        }
        else if (g > 1.25*r && g > 1.1*b) {
            current_color = GREEN;
        }
        else if (r > g && r > 1.15*b && g > 1.15*b) {
            current_color = YELLOW;
        }
        else if (b > 1.2*r) {
            current_color = BLUE;
        }
        else {
            current_color = RED;
        }

    }

    void ColorSensor::cleanup() {
        delete tcs;
    }