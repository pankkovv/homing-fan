#define DIST_MAX 200    // максимальное расстояние
#define MAX_ANGLE 180   // максимальный угол поворота
#define MIN_ANGLE 0    // минимальный угол поворота

#include <Servo.h>.

#define ECHO 5
#define TRIG 4
#define SERVO 3

#include <NewPing.h>
NewPing sonar(TRIG, ECHO, DIST_MAX);

long duration;
int distance;
Servo myServo;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(115200);
  myServo.attach(SERVO);
}

void loop() {
  for (int i = MIN_ANGLE; i <= MAX_ANGLE; i++) {
    myServo.write(i);
    delay(30);
    int curr_dist = sonar.ping_cm();
    if (curr_dist == 0) curr_dist = DIST_MAX;
    Serial.print(i);
    Serial.print(",");
    Serial.print(curr_dist);
    Serial.print(".");
  }

  for (int i = MAX_ANGLE; i > MIN_ANGLE; i--) {
    myServo.write(i);
    delay(30);
    int curr_dist = sonar.ping_cm();
    if (curr_dist == 0) curr_dist = DIST_MAX;
    Serial.print(i);
    Serial.print(",");
    Serial.print(curr_dist);
    Serial.print(".");
  }
}
