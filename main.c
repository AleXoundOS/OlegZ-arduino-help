#include "main.h"

#define LEFT_SENSOR_PIN 10
#define RIGHT_SENSOR_PIN 9
#define LEFT_WHEEL_PIN 5
#define RIGHT_WHEEL_PIN 6

#define DRIVES_SPEED 50
#define DELTA_TIME 200

void measure(int pin, boolean *lastRead, Mickeys ms);

Mickeys measureLeft, measureRight;

unsigned long firstMeasureTime, currentMeasureTime;

boolean lastSensorReadLeft, lastSensorReadRight;

void setup() {
    Serial.begin(9600);

    pinMode(LEFT_SENSOR_PIN,  INPUT);
    pinMode(RIGHT_SENSOR_PIN, INPUT);
    pinMode(LEFT_WHEEL_PIN , OUTPUT);
    pinMode(RIGHT_WHEEL_PIN, OUTPUT);

    // задание начальной скорости приводов колёс
    analogWrite(LEFT_WHEEL_PIN,  DRIVES_SPEED); // левого
    analogWrite(RIGHT_WHEEL_PIN, DRIVES_SPEED); // правого

    // установка начальных измерений с датчиков
    lastSensorReadLeft  = digitalRead(LEFT_SENSOR_PIN);
    lastSensorReadRight = digitalRead(RIGHT_SENSOR_PIN);
} // setup

void loop() {
    unsigned int leftSensorSpeed, rightSensorSpeed;

    currentMeasureTime = millis();

    // (принебрегаем разностью во времени между левым-правым измерениями)
    measure(LEFT_SENSOR_PIN,  &lastSensorReadLeft,  &measureLeft );
    measure(RIGHT_SENSOR_PIN, &lastSensorReadRight, &measureRight);

    if (currentMeasureTime >= firstMeasureTime + DELTA_TIME)
    {   // прошёл интервал замера скорости
        // расчёт двух скоростей
        leftSensorSpeed  = (measureLeft  * 1000) / deltaTime;
        rightSensorSpeed = (measureRight * 1000) / deltaTime;

        // обнуление счётчиков срабатываний
        measureLeft = measureRight = 0;

        Serial.print(leftSensorSpeed);
        Serial.print("\t");
        Serial.println(rightSensorSpeed);

        // обновление времени для начальной точки отсчёта нового измерения
        firstMeasureTime = currentMeasureTime;
    }
} // loop

void measure(int pin, boolean *lastRead, Mickeys *ms)
{
    boolean curRead;

    // чтение сигнала с датчика по заданному pin
    curRead = digitalRead(pin);

    if (curRead != *lastRead) // новое измерение отличается от старого?
        ++(*ms); // инкрементация счётчика срабатываний

    *lastRead = curRead;
} // measure
