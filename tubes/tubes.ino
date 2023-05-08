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
int btnValue(int input, String text){
    if (text == "lampu"){
        if(input == 1){
            lampValue++;
            if(lampValue > 1) {
                lampValue = 0;
            }
            delay(250);
        }
        return lampValue;
    }else{
        if(input == 1){
            pompavalue++;
            if(pompavalue > 1) {
                pompavalue = 0;
            }
            delay(250);
        }
        return pompavalue;
    }   
}

               

float range(){
    //jarak in cm
    long durasi = pulseIn(TrigPin, HIGH);
    float jarak = durasi * 0.034/2;

    return jarak;
}

void lampu(){
    if(digitalRead(ldrPin)){
        digitalWrite(relay1, HIGH);
        Serial.println("lampu hidup");
    } else {
        digitalWrite(relay1, LOW);
        Serial.println("lampu mati");
    }
}

void pompa(int range) {
    if(range < bakMandi/5 && range >= bakMandi/9) {
        digitalWrite(relay1, HIGH);
        Serial.print("pompa menyala");
    } else {
        digitalWrite(relay1, HIGH);
        Serial.print("pompa mati");
    }
}

void loop(){
    //jarak in cm
    float jarak = range();

    lampValue = btnValue(digitalRead(btn1), "lampu");
    pompavalue = btnValue(digitalRead(btn2), "pompa");

    pompa(jarak);


    if (digitalRead(pirPin)) {
        lcd.setCursor(0,0);
        lcd.print(pesanAda);
        myservo.write(90);

        lampu();
    } else {
        lcd.setCursor(0,0);
        lcd.print(pesanTidakAda);
        myservo.write(0);
    }
}





