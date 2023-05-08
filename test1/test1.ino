const int relayPin = 14;
const int btn = 12;   // Pin connected to the relay module

int hasil = 0;
int hasil2 = 0; 
void setup() {
  pinMode(relayPin, INPUT);   // Set relay pin as output
  Serial.begin(9600);          // Start serial communication
}
int btnValue(int input, String text){
    if (text == "lampu"){
        if(input == 1){
            hasil++;
            if(hasil > 1) {
                hasil = 0;
            }
            delay(250);
        }
        return hasil;
    }else{
        if(input == 1){
            hasil2++;
            if(hasil2 > 1) {
                hasil2 = 0;
            }
            delay(250);
        }
        return hasil2;
    }   
}
void loop() {
    // buttonCek(digitalRead(relayPin), hasil );
    // Serial.println(digitalRead(relayPin));

    hasil = btnValue(digitalRead(relayPin), "lampu");
    Serial.println(hasil);
    // if (digitalRead(relayPin)){
    //     hasil ++;
    //     Serial.println(hasil);
    //     delay(250);
    // }  
    int btnvalu2 = btnValue(digitalRead(btn), "pompa");
    Serial.println(btnvalu2);

    // delay(1000);

}