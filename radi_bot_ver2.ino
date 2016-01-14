#include <NewPing.h>
#include <Servo.h>

#define TRIGGER_PIN  17
#define ECHO_PIN     18
#define MAX_DISTANCE 200

const int
PWM_A   = 3,
PWM_B   = 11,
DIR_A   = 12,
DIR_B   = 13,
BRAKE_A = 9,
BRAKE_B = 8;

int brzina = 120; //mjenjanje brzine
//int berzinaa
Servo servo;
NewPing DistanceSensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing DistanceSensor2(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  // Configure the A output
  pinMode(BRAKE_A, OUTPUT);  // Brake pin za channel A
  pinMode(DIR_A, OUTPUT);    // Direction pin za channel A
  // Configure the B output
  pinMode(BRAKE_B, OUTPUT);  // Brake pin za channel B
  pinMode(DIR_B, OUTPUT);    // Direction pin za channel B
  
}

void loop()
{
test:
  servo.detach();
  unsigned int cm = DistanceSensor.ping_cm();
  Serial.print(cm);
  Serial.println("cm");

/*  servo.write(95);  //naprijed
  delay(3000);
  unsigned int cm1 = DistanceSensor.ping_cm();
  Serial.print(cm1);
  Serial.println(" naprijed");
  
  servo.write(180);  //lijevo
  delay(3000);
  unsigned int cm2 = DistanceSensor.ping_cm();
  Serial.print(cm2);
  Serial.println(" lijevo");
  
  servo.write(20); //desno
  delay(3000);
  unsigned int cm3 = DistanceSensor.ping_cm();
  Serial.print(cm3);
  Serial.println(" desno");*/
  
  

  //provjera();

  //pregledava dal ima kakvih ulaznih vrijednosti na bluetoothu
  if (Serial.available() > 0) {
    char ch = Serial.read();
    Serial.print(cm);
    Serial.println("cm");
    //Serial.print("Primljeno: ");
    //Serial.println(ch);
    //pregledava znakove f = naprijed, b = nazad, r = okret u desno, l = okret u ljevo, s = stop, a = auto pilot
    if (ch == 'f') {
      unsigned int cm = DistanceSensor.ping_cm();
      Serial.print(cm);
      Serial.println("cm");
      naprijed();
    }

    if (ch == 'b') {
      unsigned int cm = DistanceSensor.ping_cm();
      Serial.print(cm);
      Serial.println("cm");
      nazad();
    }
    if (ch == 'r') {
      unsigned int cm = DistanceSensor.ping_cm();
      Serial.print(cm);
      Serial.println("cm");
      okretDesno();
    }
    if (ch == 'l') {
      unsigned int cm = DistanceSensor.ping_cm();
      Serial.print(cm);
      Serial.println("cm");
      okretLjevo();
    }
    if (ch == 's') {
      unsigned int cm = DistanceSensor.ping_cm();
      Serial.print(cm);
      Serial.println("cm");
      stani();
    }
    if (ch == 'a') {
pocetak:  
      servo.attach(9);
      servo.write(95);
      delay(500);
      unsigned int cm = DistanceSensor.ping_cm();
      Serial.print(cm);
      Serial.println("cm");
      char ch = Serial.read();
      if (ch == 's'){
        stani();
        goto test;
      }

      if (cm <= 25 && cm > 1) {
        stani();
        servo.write(185);
        delay(1000);
        unsigned int cm = DistanceSensor.ping_cm();
        Serial.print(cm);
        Serial.println("cm");
        delay(1000);
         if(cm < 25 || cm == 0){
          okretDesno();
          servo.write(95);
          delay(750);
          goto pocetak;
          }
        servo.write(20);
        delay(1000);
        cm = DistanceSensor.ping_cm();
        Serial.print(cm);
        Serial.println("cm");
        delay(1000);
        if(cm < 25 || cm == 0){
          okretLjevo();
          servo.write(95);
          delay(750);
          goto pocetak;
          }
      }
      if (cm > 25 || cm == 0) {
        unsigned int cm = DistanceSensor.ping_cm();
        Serial.print(cm);
        Serial.println("cm");
        naprijed();
        goto pocetak;
      }
    }
  
    //     default:
    //        break;
    //    }
  }
}



void okretDesno() {
  digitalWrite(BRAKE_A, LOW);  // postavlja koÄŤnicu na LOW za motor A
  digitalWrite(DIR_A, HIGH);   // postavlja smijer za naprijed HIGH za motor A
  analogWrite(PWM_A, brzina);     // postavlja brzinu motora, 255 je max za motor A
  digitalWrite(BRAKE_B, LOW);  // postavlja koÄŤnicu na LOW za motor B
  digitalWrite(DIR_B, HIGH);    // postavlja smijer za naprijed HIGH za motor B
  analogWrite(PWM_B, brzina);     // postavlja brzinu motora, 255 je max za motor B
}
void okretLjevo() {
  //Serial.println("zid");
  digitalWrite(BRAKE_A, LOW);  // postavlja koÄŤnicu na LOW za motor A
  digitalWrite(DIR_A, LOW);    // postavlja smijer za nazad LOW za motor A
  analogWrite(PWM_A, brzina);     // postavlja brzinu za motor A
  digitalWrite(BRAKE_B, LOW);  // postavlja koÄŤnicu na LOW za motor B
  digitalWrite(DIR_B, LOW);    // postavlja smijer za nazad LOW za motor B
  analogWrite(PWM_B, brzina);     // postavlja brzinu za motor B
  //delay(5000);
}
void nazad() {
  digitalWrite(BRAKE_A, LOW);  // postavlja koÄŤnicu na LOW za motor A
  digitalWrite(DIR_A, HIGH);    // postavlja smijer za naprijed HIGH za motor A
  analogWrite(PWM_A, brzina);     // postavlja brzinu za motor A
  digitalWrite(BRAKE_B, LOW);  // postavlja koÄŤnicu na LOW za motor B
  digitalWrite(DIR_B, LOW);    // postavlja smijer za nazad LOW za motor B
  analogWrite(PWM_B, brzina);     // postavlja brzinu za motor B
  //delay(5000);
}
void naprijed() {
  digitalWrite(BRAKE_A, LOW);  // postavlja koÄŤnicu na LOW za motor A
  digitalWrite(DIR_A, LOW);    // postavlja smijer za nazad LOW za motor A
  analogWrite(PWM_A, brzina);     // postavlja brzinu za motor A
  digitalWrite(BRAKE_B, LOW);  // postavlja koÄŤnicu na LOW za motor B
  digitalWrite(DIR_B, HIGH);    // postavlja smijer za naprijed HIGH za motor B
  analogWrite(PWM_B, brzina);     // postavlja brzinu za motor B
}
void stani() {
  digitalWrite(BRAKE_A, HIGH);  // postavlja koÄŤnicu na HIGH za motor A
  digitalWrite(BRAKE_B, HIGH);    //postavlja koÄŤnicu na HIGH za motor B
  analogWrite(PWM_A, 0);        //postavlja brzinu motora na 0
  analogWrite(PWM_B, 0);        //postavlja brzinu motora na 0
}



