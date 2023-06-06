#define STEP_DELAY 15   // скорость серво
#define TIMEOUT 3000    // таймаут на новый поиск цели из режима удержания
#define MAX_ANGLE 140   // максимальный угол поворота
#define MIN_ANGLE 0    	// минимальный угол поворота
#define DIST_MAX 50    	// максимальное расстояние (см). Датчик бьёт до 4 метров, но будут шумы

#define DEADZONE 10     // зона нечувствительности (мин. разность с калибровкой)
#define MIN_CATCH 8    // мин. количество точек подряд, чтобы  считать цель целью
#define MISTAKES 4      // допустимое количество пропусков при сканировании цели

#define ECHO 5
#define TRIG 4
#define SERVO 3
#define MOS 2

#include "Servo.h"
Servo servo;

#include "GyverHacks.h"
GTimer stepTimer(STEP_DELAY);
GTimer sonarTimer(100);
GTimer timeoutTimer(TIMEOUT);

#include <NewPing.h>
NewPing sonar(TRIG, ECHO, DIST_MAX);

boolean direct;
boolean next;
const byte steps_num = (MAX_ANGLE - MIN_ANGLE) / 2;
int angle = MIN_ANGLE;
int distance[steps_num + 1];
boolean catch_flag, catched_flag, hold_flag;
byte catch_num;
byte mistakes;
byte mode = true;
byte catch_pos;
int hold_signal;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO);
  servo.write(MIN_ANGLE);
  delay(1000);
  calibration();
}

void loop() {
  if (mode) seek();
  else hold();
}

void seek() {
  if (direct) {
    if (angle < MAX_ANGLE)
      turn_to(MAX_ANGLE);
    else {
      direct = false;
      delay(50);
    }
  }
  else {
    if (angle > MIN_ANGLE)
      turn_to(MIN_ANGLE);
    else {
      direct = true;
      delay(50);
    }
  }
  search();
}

void hold() {
  if (!hold_flag)
    turn_to(catch_pos);
  else {

    if (sonarTimer.isReady()) {
      byte pos = (angle - MIN_ANGLE) / 2;
      int curr_dist = sonar.ping_cm();
      if (curr_dist == 0) curr_dist = DIST_MAX;
      int diff = distance[pos] - curr_dist;
      if ((diff < DEADZONE) || (curr_dist > 1 && curr_dist < 10)) {
        if (timeoutTimer.isReady())
          mode = true;
        hold_flag = false;
      } else {
        timeoutTimer.reset();
      }
    }
  }
}

void search() {
  if (angle % 2 == 0 && next) {
    next = false;
    byte pos = (angle - MIN_ANGLE) / 2;
    int curr_dist = sonar.ping_cm();
    if (curr_dist == 0) curr_dist = DIST_MAX;
    int diff = distance[pos] - curr_dist;
    if (diff > DEADZONE) {
      if (!catch_flag) {
        catch_flag = true;
        catch_pos = angle;
      }
      catch_num++;
      if (catch_num > MIN_CATCH)
        catched_flag = true;
    } else {
      if (catch_flag) {
        if (mistakes > MISTAKES) {
          // сбросить всё
          catch_flag = false;
          catched_flag = false;
          catch_num = 0;
          mistakes = 0;
        } else {
          mistakes++;
        }
      }

      if (catched_flag) {
        mode = false;
        if (direct) catch_pos += catch_num;
        else catch_pos -= catch_num;
        
        hold_flag = false;
        catch_flag = false;
        catched_flag = false;
        catch_num = 0;
        mistakes = 0;        
      }
    }
  }
}

void calibration() {
  for (angle = MIN_ANGLE; angle <= MAX_ANGLE; angle++) {
    servo.write(angle);
    if (angle % 2 == 0) {
      byte pos = (angle - MIN_ANGLE) / 2;
      int curr_dist = sonar.ping_cm();
      if (curr_dist == 0) distance[pos] = DIST_MAX;
      else distance[pos] = sonar.ping_cm();
    }
    delay(STEP_DELAY * 1.5);
  }
}

void turn_to(byte to_angle) {
  if (stepTimer.isReady()) {
    if (angle < to_angle) angle++;
    else if (angle > to_angle) angle--;
    else hold_flag = true;
    servo.write(angle);
    next = true;
  }
}
