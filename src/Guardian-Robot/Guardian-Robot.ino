#include <Servo.h>
#include <MusicWithoutDelay.h>
#include <Tone-master.h>

#define SERVO_MIN           10
#define SERVO_MAX           190
#define SERVO_MOVEMENT      30  // maximum degree of movement at one time

#define LED_PIN             0   // "Eye" LED is connected here
#define SERVO_PIN           1   // Pin connected to the servo motor
#define GLOW_PIN            2   // Tramsistor connected to the lights glowing body of robot
#define SPEAKER_PIN1        8   // Transistor amplified speaker connects here
#define SPEAKER_PIN2        9   // Transistor amplified speaker connects here
#define SPEAKER_PIN3        10  // Transistor amplified speaker connects here
#define SPEAKER_PIN4        11  // Transistor amplified speaker connects here
const int delayAmount = 10;  // loops every 10 milliseconds
const int headRotationExecution = 5;  // executes every 50 milliseconds
const int eyeBlinkExecution = 5;         // executes every 50 milliseconds
const int flickerExecution = 5;           // executes every 50 milliseconds

Servo myservo;

char *introSoprano = ":d=12,o=5,b=160,f=aeb:2b,p,p,b,b,b,b,8.b,16a,4b,p,p,b,b,b,b,8.b,16a,4b,p,p,b,b,b,b,8b,16f,16f,8f,16f,16f,8f,16f,16f,8f,8f";
char *introAlto = ":d=12,o=5,b=160,f=aeb:2b,p,p,b,b,b,b,8.b,16a,4b,p,p,b,b,b,b,8.b,16a,4b,p,p,b,b,b,b,8b,16f,16f,8f,16f,16f,8f,16f,16f,8f,8f";
//char *introTenor = ":d=12,o=5,b=160,f=aeb:2b,p,p,b,b,b,b,8.b,16a,4b,p,p,b,b,b,b,8.b,16a,4b,p,p,b,b,b,b,8b,16f,16f,8f,16f,16f,8f,16f,16f,8f,8f";
//char *introBass = ":d=12,o=5,b=160,f=aeb:2b,p,p,b,b,b,b,8.b,16a,4b,p,p,b,b,b,b,8.b,16a,4b,p,p,b,b,b,b,8b,16f,16f,8f,16f,16f,8f,16f,16f,8f,8f";

Tone myTone1;
Tone myTone2;
//Tone myTone3;
//Tone myTone4;
MusicWithoutDelay voice1(introSoprano);
MusicWithoutDelay voice2(introAlto);
//MusicWithoutDelay voice3(introTenor);
//MusicWithoutDelay voice4(introBass);

int randomHeadTurn;
int servoPosition;
int tempServoPosition;
int eyeBlinkRandom;
int flickerRandom1;
int flickerRandom2;
int count1;
int count2;
int count3;
int count4;
int headRotationTiming;
int eyeBlinkTiming;
int musicTiming;
int flickerTiming;

boolean flickering;
boolean playingMusic;

void HeadRotation();
void EyeBlink();
void Flicker();
void Music();

void HeadRotation() {
  if (random(3) == 0) { // 1-in-3 chance of the head moving
    tempServoPosition = random(servoPosition - SERVO_MOVEMENT, servoPosition + SERVO_MOVEMENT);
    if (tempServoPosition > SERVO_MAX) {
      tempServoPosition = SERVO_MAX;
    } else if (tempServoPosition < SERVO_MIN) {
      tempServoPosition = SERVO_MIN;
    }
    myservo.write(tempServoPosition);
    servoPosition = tempServoPosition;
  }
  if (randomHeadTurn == count1) {
    myservo.write(random(SERVO_MIN, SERVO_MAX));
    count1 = 0;
    randomHeadTurn = random(5, 16);
  }
  count1++;
}

void EyeBlink() {
  if (random(12) == 0) { // there's a 1-in-12 chance of an "eye blink":
    digitalWrite(LED_PIN, LOW);  // The LED turns OFF
    eyeBlinkRandom = random(3, 12);
  }
  if (count2 == eyeBlinkRandom) {
    digitalWrite(LED_PIN, HIGH);
    count2 = 0;
  }
  count2++;
}

void Flicker() {
  if (random(20) == 0 && !flickering) { // There's a 1-in-20 chance of flickering
    flickering = true;
    count4 = 0;
    flickerRandom2 = random(1, 5);   // flickers between 1 and 5 times
  }

  if (flickering && count4 < flickerRandom2) {
    if (flickerRandom1 == count3) {
      digitalWrite(GLOW_PIN, HIGH);   // back on
      count3 = 0;
      count4++;
    }

    if (flickering && count3 == 0) {
      digitalWrite(GLOW_PIN, LOW);     // The LED turns OFF
      flickerRandom1 = random(1, 4);   // for just a short random moment
    }
  }
}

void Music() {
  //  if (random(50) == 0 && !playingMusic) {
  //    playingMusic = true;
  //  }
  //
  //  if (playingMusic) {
  //    playSong(guardianRobotMusic, SPEAKER_PIN);
  //    if (!isPlayingMusic()) {
  //      playingMusic = false;
  //    }
  //  }
}

void setup() {
  myservo.attach(SERVO_PIN);
  servoPosition = 90;
  myservo.write(servoPosition);
  randomHeadTurn = 6;
  flickering = false;

  pinMode(LED_PIN, OUTPUT);
  pinMode(GLOW_PIN, OUTPUT);

  myTone1.begin(SPEAKER_PIN1);
  myTone2.begin(SPEAKER_PIN2);
//  myTone3.begin(SPEAKER_PIN3);
//  myTone4.begin(SPEAKER_PIN4);

  digitalWrite(LED_PIN, HIGH);
  digitalWrite(GLOW_PIN, HIGH);
}

void loop() {
  if (headRotationTiming == headRotationExecution) {
    HeadRotation();
    headRotationTiming = 0;
  }

  if (eyeBlinkTiming == eyeBlinkExecution) {
    EyeBlink();
    eyeBlinkTiming = 0;
  }

  if (flickerTiming == flickerExecution) {
    Flicker();
    flickerTiming = 0;
  }

  Music();

  headRotationTiming++;
  eyeBlinkTiming++;
  flickerTiming++;

  delay(delayAmount);
}
