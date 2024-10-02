"""
Bu kod Hüseyin Eren'e aittir.
YouTube:huseyinfest
GitHub:huseyinfest
Instagram:huseyinfest

"""



"Kütüphaneleri ekle"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

"Lcd ekranın adres ve ölçüsünü yaz"
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD ekranın adresi (0x27 olabilir)

"Görüntü işleme kısmında veri çok hızlı işlendiği için delay verdik"
unsigned long previousMillis = 0;
const long interval = 1000;  // 5 saniyelik aralık

"Seri haberleşme ve lcd ekranı başlatıyoruz"
String received_data = "";  // Gelen veriyi tutmak için değişken

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hazir...");
  
  Serial.begin(9600);  // Seri haberleşmeyi başlat
}

void loop() {
  // Seri porttan gelen veriyi kontrol et
  if (Serial.available() > 0) {
    // Gelen veriyi oku ve '\n' karakterine kadar bekle
    String new_data = Serial.readStringUntil('\n');
    
    // Gelen verinin boş olmadığını kontrol et
    if (new_data.length() > 0) {
      // Veriyi sakla
      received_data = new_data;
      Serial.print("Gelen veri: ");
      Serial.println(received_data);
    }
  }

  // Zaman kontrolü, 5 saniye geçti mi?
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Zamanlayıcıyı sıfırla
    
    // Eğer geçerli bir veri varsa LCD ekranı güncelle
    if (received_data.length() > 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Nesne:");
      lcd.setCursor(0, 1);
      lcd.print(received_data);  // Veriyi LCD'ye yaz
    }
  }
}
