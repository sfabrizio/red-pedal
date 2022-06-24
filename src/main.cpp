#include "Keyboard.h"

#define BTN_1_PIN 2
#define BTN_2_PIN 3
#define BTN_3_PIN 4
#define BTN_4_PIN 5

#define LED_1_PIN 21
#define LED_2_PIN 20
#define LED_3_PIN 19
#define LED_4_PIN 18

const unsigned long standByTime = 5 * 60000; // in mins
const unsigned long initTimeOFF = 2000; // secs
boolean isInit = true;
unsigned long previousMillis = 0; 


static void setAllLeds(uint8_t state)
{   
    digitalWrite(LED_1_PIN, state);
    digitalWrite(LED_2_PIN, state);
    digitalWrite(LED_3_PIN, state);
    digitalWrite(LED_4_PIN, state);
}

static void onBtnPress(char key, uint8_t ledNumber)
{
    if (isInit)
    {
        return;
    }
    setAllLeds(HIGH);
    digitalWrite(ledNumber, LOW);
    Keyboard.press(key);
    Keyboard.releaseAll(); // for just send once press
    delay(500); // led turn off & on time
    digitalWrite(ledNumber, HIGH);
    previousMillis = millis(); // reset standBy time
}

void setup(void)
{
    Keyboard.begin();
    pinMode(BTN_1_PIN, INPUT);
    pinMode(BTN_2_PIN, INPUT);
    pinMode(BTN_3_PIN, INPUT);
    pinMode(BTN_4_PIN, INPUT);

    pinMode(LED_1_PIN, OUTPUT);
    pinMode(LED_2_PIN, OUTPUT);
    pinMode(LED_3_PIN, OUTPUT);
    pinMode(LED_4_PIN, OUTPUT);
    setAllLeds(HIGH);
}

void loop(void)
{
    static uint8_t btn1StateLast = 0;
    static uint8_t btn2StateLast = 0;
    static uint8_t btn3StateLast = 0;
    static uint8_t btn4StateLast = 0;
    unsigned long currentMillis = millis();

    uint8_t btn1State;
    uint8_t btn2State;
    uint8_t btn3State;
    uint8_t btn4State;

    btn1State = digitalRead(BTN_1_PIN);
    btn2State = digitalRead(BTN_2_PIN);
    btn3State = digitalRead(BTN_3_PIN);
    btn4State = digitalRead(BTN_4_PIN);

    if (currentMillis - previousMillis >= standByTime)
    {
        previousMillis += standByTime;
        setAllLeds(LOW);
    }

    if (isInit && currentMillis - previousMillis >= initTimeOFF)
    {
        previousMillis += initTimeOFF;
        animationStart();
        setAllLeds(LOW);
        isInit = false;
    }

    if (btn1State != btn1StateLast)
    {
        btn1StateLast = btn1State;
        onBtnPress('1', LED_1_PIN);
    }
    if (btn2State != btn2StateLast)
    {
        btn2StateLast = btn2State;
        onBtnPress('2', LED_2_PIN);
    }
    if (btn3State != btn3StateLast)
    {
        btn3StateLast = btn3State;
        onBtnPress('3', LED_3_PIN);
    }
    if (btn4State != btn4StateLast)
    {
        btn4StateLast = btn4State;
        onBtnPress('4', LED_4_PIN);
    }
    delay(50);
}
