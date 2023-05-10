#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ssid = "Rejoagung";
const char* password = "rizkaaja";

// inisialisasi Bot Token
#define BOTtoken "5861437332:AAE6rjcH2UyLY32Us56ao6GJKO195SJIzag"  // Bot Token dari BotFather

// chat id dari @myidbot
#define CHAT_ID "1554993424"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

const int Pinled1 = 2;
bool Statusled1 = LOW;

const int Pinled2 = 4;
bool Statusled2 = LOW;

const int Pinled3 = 5;
bool Statusled3 = LOW;

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String control = "Selamat Datang, " + from_name + ".\n";
      control += "Gunakan Commands Di Bawah Untuk Control Lednya.\n\n";
      control += "/led1_Nyala Untuk Menyalakan Led 1 \n";
      control += "/led1_Mati Untuk Matikan Led 1\n";
      control += "/led2_Nyala Untuk Menyalakan Led 2\n";
      control += "/led2_Mati Untuk Matikan Led 2\n";
      control += "/led3_Nyala Untuk Menyalakan Led 3\n";
      control += "/led3_Mati Untuk Matikan Led 3\n";
      control += "/Status Untuk Cek Status Led Saat Ini \n";
      bot.sendMessage(chat_id, control, "");
    }

    if (text == "/led1_Nyala") {
      bot.sendMessage(chat_id, "Led 1 Nyala", "");
      Statusled1 = HIGH;
      digitalWrite(Pinled1, Statusled1);
    }
    
    if (text == "/led1_Mati") {
      bot.sendMessage(chat_id, "LED 1 Mati", "");
      Statusled1 = LOW;
      digitalWrite(Pinled1, Statusled1);
    }

        if (text == "/led2_Nyala") {
      bot.sendMessage(chat_id, "Led 2 Nyala", "");
      Statusled2 = HIGH;
      digitalWrite(Pinled2, Statusled2);
    }
    
    if (text == "/led2_Mati") {
      bot.sendMessage(chat_id, "LED 2 Mati", "");
      Statusled2 = LOW;
      digitalWrite(Pinled2, Statusled2);
    }

    if (text == "/led3_Nyala") {
      bot.sendMessage(chat_id, "Led 3 Nyala", "");
      Statusled3 = HIGH;
      digitalWrite(Pinled3, Statusled3);
    }
    
    if (text == "/led3_Mati") {
      bot.sendMessage(chat_id, "LED 3 Mati", "");
      Statusled3 = LOW;
      digitalWrite(Pinled3, Statusled3);
    }
    
    if (text == "/Status") {
      if (digitalRead(Pinled1)){
        bot.sendMessage(chat_id, "LED 1 Nyala", "");
      }
      else{
        bot.sendMessage(chat_id, "LED 1 Mati", "");
      }
      if (digitalRead(Pinled2)){
        bot.sendMessage(chat_id, "LED 2 Nyala", "");
      }
      else{
        bot.sendMessage(chat_id, "LED 2 Mati", "");
      }
      if (digitalRead(Pinled3)){
        bot.sendMessage(chat_id, "LED 3 Nyala", "");
      }
      else{
        bot.sendMessage(chat_id, "LED 3 Mati", "");
      } 
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(Pinled1, OUTPUT);
  digitalWrite(Pinled1, Statusled1);

  pinMode(Pinled2, OUTPUT);
  digitalWrite(Pinled2, Statusled2);
  
  pinMode(Pinled3, OUTPUT);
  digitalWrite(Pinled3, Statusled3);
  
  // Koneksi Ke Wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  #endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
}

void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}