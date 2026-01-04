#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>

#define ssid "" // GANTI USERNAME WIFI KAMU DI SINI
#define password "" // GANTI PASSWORD KAMU DI SINI
#define token "" // GANTI TOKEN TELEGRAM KAMU DI SINI
#define id "" GANTI DENGAN ID TELEGRAM KAMU DI SINI
#define sensor 19
#define led 23

LiquidCrystal_I2C lcd(0x27,16,2);
WiFiClientSecure client;
UniversalTelegramBot bot(token, client);

int hitung = 0;
bool mulai = HIGH;

void setup(){
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);

  lcd.init();
  lcd.backlight();
  
  //wifi mode
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while (WiFi.status() != WL_CONNECTED)
  {
    lcd.setCursor(0, 0);
    lcd.print("MENGHUBUNGKAN...");
    lcd.setCursor(0, 1);
    for (int i = 0; i < 16; i++){
      lcd.write(byte(255));
      delay(150);
    }
  }

  bot.sendMessage(id, "SELAMAT DATANG VOLTECH!!🫡🫡");
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(200);
  digitalWrite(led, HIGH);
  delay(200);
  digitalWrite(led, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("JUMLAH HITUNGAN");
  lcd.setCursor(0, 1);
  lcd.print("JUMLAH -> 0");

  bot.sendMessage(id, "JUMLAH MASUK -> 0 "); 
}

void loop (){
  bool akhir = digitalRead(sensor);

  if(mulai == HIGH && akhir == LOW){
    hitung++;
    lcd.setCursor(0, 1);
    lcd.print("JUMLAH -> ");
    lcd.print(hitung);
    String pesan = "JUMLAH MASUK -> " + String(hitung) ;
    bot.sendMessage(id, pesan, "");
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(200);
    digitalWrite(led, HIGH);
    delay(200);
    digitalWrite(led, LOW);
    delay(200);

  }

  mulai = akhir;
  delay(100);
}
