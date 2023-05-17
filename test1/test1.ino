#include <ESP32Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myservo;

const int btn1 = 2;
const int btn2 = 4;

const int servo1Pin = 15;

const int relay1 = 18;
const int relay2 = 19;

const int TrigPin = 13;
const int echoPin = 12;

const int ldrPin = 14;

const int pirPin = 27;

// dalam bak mandi in cm 
int bakMandi = 12;

int lampValue = 0;
int pompavalue = 0;

int BtnlampValue = 0;
int Btnpompavalue = 0;

int pirStatus = 0;

float jarak;

// pesan status
String pesanAda = "sedang ada orang";
String pesanTidakAda = "tidak ada orang";

void setup(){
    myservo.attach(servo1Pin);

    lcd.init();
    lcd.backlight();                
    lcd.setCursor(0,1); 
    lcd.print("----------------");

    pinMode(btn1, INPUT);
    pinMode(btn2, INPUT);

    pinMode(relay1, OUTPUT);
    pinMode(relay2, OUTPUT);

    pinMode(TrigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    pinMode(ldrPin, INPUT);

    pinMode(pirPin, INPUT);

    Serial.begin(9600);

}

void onLamp(){
    digitalWrite(relay2, HIGH);
    lampValue = 1;
}
void offLamp(){
    digitalWrite(relay2, LOW);
    lampValue = 0;
}

void onPompa(){
    digitalWrite(relay1, HIGH);
    pompavalue = 1;
}

void offPompa(){
    digitalWrite(relay1, LOW);
    pompavalue = 0;
}


int btnValue(int input, String text){
    if (text == "lampu"){
        if(input){
            BtnlampValue++;
            if(BtnlampValue > 1) {
                BtnlampValue = 0;
            }
            delay(250);
        }
        return lampValue;
    }else{
        if(input){
            Btnpompavalue++;
            if(Btnpompavalue > 1) {
                Btnpompavalue = 0;
            }
            delay(250);
        }
        return pompavalue;
    }   
}

 

float range(){
    //jarak in cm
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    long durasi = pulseIn(echoPin, HIGH);
    float jarak = durasi * 0.034/2;

    Serial.println(jarak);

    return jarak;
}

void lampu(){
    if(analogRead(ldrPin) < 1300){
        if(lampValue != 1) {
            onLamp();
        }
    } 
}

void pompa(int range) {
    if(range < bakMandi/5) {
        onPompa();
        Serial.print("pompa menyala");
    } if (range >= bakMandi/9) {
        offPompa();
        Serial.print("pompa mati");
    }
}

void loop(){
    //jarak in cm
    jarak = range();

    BtnlampValue = btnValue(digitalRead(btn1), "lampu");
    if(BtnlampValue == 1 && lampValue != 1){
        onLamp();
    }else if(BtnlampValue != 1 && lampValue == 1){
        onLamp();
    }
    Btnpompavalue = btnValue(digitalRead(btn2), "pompa");
    if(Btnpompavalue == 1 && pompavalue != 1){
        onPompa();
    }else if(Btnpompavalue != 1 && pompavalue == 1){
        onPompa();
    }

    pompa(jarak);


    if (digitalRead(pirPin)) {
        pirStatus = 1;
        lcd.setCursor(0,0);
        lcd.print(pesanAda);
        myservo.write(90);

        lampu();
    } else {
        delay(10000);
        pirStatus = 0;
        lcd.setCursor(0,0);
        lcd.print(pesanTidakAda);
        myservo.write(0);
        if(lampValue == 1){
            offLamp();
        }
    }

    // Serial.println(pirStatus);
    // Serial.println(lampValue);
    // Serial.println(pompavalue);
    Serial.println(jarak);
}





