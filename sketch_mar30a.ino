#include <MPU6050.h>
#include <Wire.h>

MPU6050 MPU;

int GYRO_X , GYRO_Y , GYRO_Z;
const int BUZZER_PIN = 13;
const int LED_PIN = 12;
const int BUZZER_FREQUENCY = 2800;
const int DELAY = 50;
const unsigned long DELAY_BEFORE_ALARM = 30000 / 2;
const int GYRO_X_VALUE = 4999;
const int GYRO_Y_VALUE = 4999;
const int GYRO_Z_VALUE = 4999;
int TO_SUM_X_VALUE = 0;
int TO_SUM_Y_VALUE = 0;
int TO_SUM_Z_VALUE = 0;
long START_TIME;

void setup() {
  initiliazePin();
  initializeSerial();
  initializeWire();
  MPU.initialize();
}

void initiliazePin() {
  pinMode(BUZZER_PIN,OUTPUT); 
}

void initializeSerial() {
  Serial.begin(9600);
}

void initializeWire() {
  Wire.begin();  
}

void buzz() {
  for(int i = 0; i <= 20; i++) {
    if(i % 2) {
      digitalWrite(LED_PIN, HIGH);
    } else { 
      digitalWrite(LED_PIN, LOW);
    }
    tone(BUZZER_PIN, BUZZER_FREQUENCY);
    delay(DELAY);
    noTone(BUZZER_PIN);
    delay(DELAY);
 }
}

void loop() {
  unsigned long CURRENT_TIME = millis(); // Get current time
  int ITERATION = 0;

  while(millis() - CURRENT_TIME < DELAY_BEFORE_ALARM) {
    MPU.getRotation(&GYRO_X, &GYRO_Y, &GYRO_Z);
    if(
      GYRO_X < -GYRO_X_VALUE || GYRO_X > GYRO_X_VALUE || 
      GYRO_Y < -GYRO_Y_VALUE || GYRO_Y > GYRO_Y_VALUE ||
      GYRO_Z < -GYRO_Z_VALUE || GYRO_Z > GYRO_Z_VALUE 
    ) {
      TO_SUM_X_VALUE += GYRO_X;
      TO_SUM_Y_VALUE += GYRO_Y;
      TO_SUM_Z_VALUE += GYRO_Z;
      ITERATION++;
    } 

    /* PWEDE TO IDELTE PANG CHECK LANG TO NG MGA ACCUMULATED / PINAG ADD NA VALUE SA LOOB NG 15 SECONDS */
    Serial.print("GYRO X ");
    Serial.println(TO_SUM_X_VALUE);
    Serial.print("GYRO Y ");
    Serial.println(TO_SUM_Y_VALUE);
    Serial.print("GYRO Z ");
    Serial.println(TO_SUM_Y_VALUE);
    Serial.print("ITERATION ");
    Serial.println(ITERATION);
    Serial.print("CURRENT TIME ");
    Serial.println(millis() - CURRENT_TIME);
    delay(1000);
  }

   int AVERAGE_X_VALUE = TO_SUM_X_VALUE / ITERATION;
   int AVERAGE_Y_VALUE = TO_SUM_Y_VALUE / ITERATION;
   int AVERAGE_Z_VALUE = TO_SUM_Z_VALUE / ITERATION;

    /* PWEDE TO IDELTE PANG CHECK LANG TO NG MGA AVERAGE */
    Serial.print("AVERAGE GYRO X ");
    Serial.println(AVERAGE_X_VALUE);
    Serial.print("AVERAGE GYRO Y ");
    Serial.println(AVERAGE_Y_VALUE);
    Serial.print("AVERAGE GYRO Z ");
    Serial.println(AVERAGE_Z_VALUE);
    delay(1000);

  /* I adjust nyo ung value nitong tatlo GYRO_X_VALUE, GYRO_Y_VALUE, GYRO_Z_VALUE */
   if(
     AVERAGE_X_VALUE > GYRO_X_VALUE || 
     AVERAGE_Y_VALUE > GYRO_Y_VALUE ||
     AVERAGE_Z_VALUE > GYRO_Z_VALUE 
   ) { 
     buzz();
     Serial.println("DETECTED");
   }

   ITERATION = 0;
}
