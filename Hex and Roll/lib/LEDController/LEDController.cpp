#include "LEDController.h"

void LEDController::setup(const int led_pin, const int led_pin2) { 
    FastLED.addLeds<NEOPIXEL, 2>(leds_array, NUM_LEDS); 
    FastLED.addLeds<NEOPIXEL, 0>(leds_array2, NUM_LEDS2); 
}

void LEDController::update() {
    FastLED.show();
}

void LEDController::setColorUpTo(int end_led, CRGB color) {
    for (int led_index = 0; led_index < NUM_LEDS; led_index++) {
        if (led_index < end_led) {
            leds_array[led_index] = color;
        } else {
            leds_array[led_index] = CRGB::Black;
        }
    }
}

void LEDController::setColorForBallCombination(CRGB color1, CRGB color2, CRGB color3, CRGB color4, CRGB color5, CRGB color6) {
    for (int led_index = 0; led_index < NUM_LEDS; led_index++) {
        if (led_index < END_LED_1) {
            leds_array[led_index] = color1;
        } else if (led_index < END_LED_2) {
            int grad_start = END_LED_1;
            int grad_end = END_LED_2;
            uint16_t temp_R = color1.r+((float)(led_index-grad_start)/(grad_end-grad_start))*(color3.r-color1.r);
            uint16_t temp_G = color1.g+((float)(led_index-grad_start)/(grad_end-grad_start))*(color3.g-color1.g);
            uint16_t temp_B = color1.b+((float)(led_index-grad_start)/(grad_end-grad_start))*(color3.b-color1.b);
            color2 = CRGB(temp_R,temp_G,temp_B);
            leds_array[led_index] = color2;
        } else if (led_index < END_LED_3) {
            leds_array[led_index] = color3;
        } else if (led_index < END_LED_4) {
            int grad_start = END_LED_3;
            int grad_end = END_LED_4;
            uint16_t temp_R = color3.r+((float)(led_index-grad_start)/(grad_end-grad_start))*(color5.r-color3.r);
            uint16_t temp_G = color3.g+((float)(led_index-grad_start)/(grad_end-grad_start))*(color5.g-color3.g);
            uint16_t temp_B = color3.b+((float)(led_index-grad_start)/(grad_end-grad_start))*(color5.b-color3.b);
            color4 = CRGB(temp_R,temp_G,temp_B);
            leds_array[led_index] = color4;
        } else if (led_index < END_LED_5) {
            leds_array[led_index] = color5;
        } else if (led_index < END_LED_6) {
            int grad_start = END_LED_5;
            int grad_end = END_LED_6;
            uint16_t temp_R = color5.r+((float)(led_index-grad_start)/(grad_end-grad_start))*(color1.r-color5.r);
            uint16_t temp_G = color5.g+((float)(led_index-grad_start)/(grad_end-grad_start))*(color1.g-color5.g);
            uint16_t temp_B = color5.b+((float)(led_index-grad_start)/(grad_end-grad_start))*(color1.b-color5.b);
            color6 = CRGB(temp_R,temp_G,temp_B);
            leds_array[led_index] = color6;
            
        }
    }
}

void LEDController::setInnerColor(CRGB color1, CRGB color2, CRGB color3, int32_t *p1, int32_t *p2, int32_t *p3, int32_t *p4, int32_t *p5, int32_t *p6) {
    uint8_t fade = 0; 
    for (int led_index = 0; led_index < NUM_LEDS2; led_index++) {
        leds_array2[led_index]=CRGB::Black;
        
        if(led_index<END_LED2_1) {
            uint8_t range_start = 0;
            uint8_t range_end = END_LED2_1;
            if(led_index<range_start+(range_end-range_start)/2) {
                fade=map(p6[0],-31,31,0,255);
            } else {
                fade=map(p6[1],-31,31,0,255);
            }
            CRGB newColor = color1;
            leds_array2[led_index] = newColor.fadeLightBy(fade);
        } else if(led_index<END_LED2_2) {
            uint8_t range_start = END_LED2_1;
            uint8_t range_end = END_LED2_2;
            int16_t r = (color1.r+color2.r)/2; int16_t g = (color1.g+color2.g)/2; int16_t b = (color1.b+color2.b)/2;
            if(led_index<range_start+(range_end-range_start)/2) {
                fade=map(p5[0],-31,31,0,255);
            } else {
                fade=map(p5[1],-31,31,0,255);
            }
            CRGB newColor = CRGB(r,g,b);
            leds_array2[led_index] = newColor.fadeLightBy(fade);
        } else if(led_index<END_LED2_3) {
            uint8_t range_start = END_LED2_2;
            uint8_t range_end = END_LED2_3;
            if(led_index<range_start+(range_end-range_start)/2) {
                fade=map(p2[0],-31,31,0,255);
            } else {
                fade=map(p2[1],-31,31,0,255);
            }
            CRGB newColor = color2;
            leds_array2[led_index] = newColor.fadeLightBy(fade);
        } else if(led_index<END_LED2_4) {
            uint8_t range_start = END_LED2_3;
            uint8_t range_end = END_LED2_4;
            int16_t r = (color2.r+color3.r)/2; int16_t g = (color2.g+color3.g)/2; int16_t b = (color2.b+color3.b)/2;
            if(led_index<range_start+(range_end-range_start)/2) {
                fade=map(p4[0],-31,31,0,255);
            } else {
                fade=map(p4[1],-31,31,0,255);
            }
            CRGB newColor = CRGB(r,g,b);
            leds_array2[led_index] = newColor.fadeLightBy(fade);
        } else if(led_index<END_LED2_5) {
            uint8_t range_start = END_LED2_4;
            uint8_t range_end = END_LED2_5;
            if(led_index<range_start+(range_end-range_start)/2) {
                fade=map(p1[0],-31,31,0,255);
            } else {
                fade=map(p1[1],-31,31,0,255);
            }
            CRGB newColor = color3;
            leds_array2[led_index] = newColor.fadeLightBy(fade);
        } else if(led_index<END_LED2_6) {
            uint8_t range_start = END_LED2_5;
            uint8_t range_end = END_LED2_6;
            int16_t r = (color3.r+color1.r)/2; int16_t g = (color3.g+color1.g)/2; int16_t b = (color3.b+color1.b)/2;
            if(led_index<range_start+(range_end-range_start)/2) {
                fade=map(p3[0],-31,31,0,255);
            } else {
                fade=map(p3[1],-31,31,0,255);
            }
            CRGB newColor = CRGB(r,g,b);
            leds_array2[led_index] = newColor.fadeLightBy(fade);
        }
    }
}


void LEDController::setBrightness(int brightness) {
    FastLED.setBrightness(brightness);
}


void LEDController::cleanup() {
    // TODO: write this if required
}