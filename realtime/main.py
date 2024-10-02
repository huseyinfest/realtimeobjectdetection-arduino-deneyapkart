import cv2
import serial
import time
from ultralytics import YOLO

# Modeli yükle
model = YOLO('yolov8n.pt')

# Arduino'ya bağlan
arduino = serial.Serial('COM3', 9600)  # Port numarasını sistemine göre ayarla
time.sleep(2)  # Bağlantı kurulmasını bekle

# Video kaynağını ayarla (0, webcam için)
cap = cv2.VideoCapture(0)

# Veri gönderim döngüsü
while True:
    ret, frame = cap.read()  # Webcam'den bir kare oku
    if not ret:
        break  # Eğer kare okunamazsa döngüyü kır

    # Görüntü üzerinde nesne tespiti yap
    results = model(frame, show=True, conf=0.4)  # Tespitleri göster

    # Tespit edilen nesneleri döngüyle işle
    for result in results:
        for detection in result.boxes.data:  # Her bir tespit için
            # Tespit edilen nesnenin adı ve güven oranını al
            class_id = int(detection[5])  # Nesne sınıfı
            confidence = float(detection[4])  # Güven oranı

            # Sınıf ID'sini kullanarak nesne adını belirle
            object_name = model.names[class_id] if class_id < len(model.names) else "Bilinmeyen"

            # LCD ekranı güncellemek için nesne adını gönder
            arduino.write((object_name + '\n').encode())  # Arduino'ya nesne adını gönder
            print(f"Veri gönderildi: {object_name}")  # Konsola yaz

    time.sleep(1)  # Tespit aralığı (1 saniye)

# Kaynakları serbest bırak
cap.release()
cv2.destroyAllWindows()
