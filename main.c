#define LEFT_SENSOR 10
#define RIGHT_SENSOR 9
#define LEFT_WHEEL_SPEED 5
#define RIGHT_WHEEL_SPEED 6

int deltaTime = 200;
int speed = 50;

int leftRot;
int rightRot;
int lastTime;
int newTime;
int leftSensorSpeed;
int rightSensorSpeed;
boolean leftSensorPingFirst;
boolean leftSensorPingSecond;
boolean rightSensorPingFirst;
boolean rightSensorPingSecond;


void setup() {
    // put your setup code here, to run once:

    Serial.begin(9600);
    pinMode(LEFT_SENSOR, INPUT);
    pinMode(RIGHT_SENSOR, INPUT);
    for (int i = 4; i < 8; i++)
        pinMode(i, OUTPUT);
    lastTime = 0;
}

void loop() {
    // put your main code here, to run repeatedly:

    // задаётся скорость приводов колёс
    analogWrite(LEFT_WHEEL_SPEED, speed); // левого
    analogWrite(RIGHT_WHEEL_SPEED, speed); // правого

    // чтение первого сигнала с левого датчика
    leftSensorPingFirst = digitalRead(LEFT_SENSOR);
    delay(1);
    // чтение первого сигнала с правого датчика
    rightSensorPingFirst = digitalRead(RIGHT_SENSOR);
    delay(1);
    // чтение второго сигнала с правого левого датчика
    leftSensorPingSecond = digitalRead(LEFT_SENSOR);
    delay(1);
    // чтение второго сигнала с правого правого датчика
    rightSensorPingSecond = digitalRead(RIGHT_SENSOR);

    // если не совпадают
    if (leftSensorPingFirst != leftSensorPingSecond)
    {
        leftRot += 1; // записываем количество срабатываний датчика
    }
    if (rightSensorPingFirst != rightSensorPingSecond)
    {
        rightRot += 1; // то же самое для правого
    }

    newTime = millis();

    if (newTime >= lastTime + deltaTime)
    {   // прошёл интервал замера скорости
        leftSensorSpeed = (leftRot*1000)/deltaTime; // расчёт скорости
        rightSensorSpeed = (rightRot*1000)/deltaTime;
        Serial.print(leftSensorSpeed);
        Serial.print("\t");
        Serial.println(rightSensorSpeed);
        leftRot = 0;
        rightRot = 0;
        lastTime = newTime; // обнуляем счётчики для нового расчёта скорости
    }
}