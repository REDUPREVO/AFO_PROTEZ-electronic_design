// Sensör Pin Tanımları
#define echoPin1 6
#define trigPin1 7
#define echoPin2 10
#define trigPin2 11
#define echoPin3 2
#define trigPin3 3
#define echoPin4 4
#define trigPin4 5
#define buzzerPin 8

// Mesafe sınırları (cm cinsinden)
int maximumRange = 50;
int minimumRange = 0;

void setup() {
  // Birinci sensör pinleri
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  
  // İkinci sensör pinleri
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  // Üçüncü sensör pinleri
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  
  // Dördüncü sensör pinleri
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  
  // Buzzer pini
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Her sensörden mesafe ölçümü
  int distance1 = mesafe(trigPin1, echoPin1, maximumRange, minimumRange);
  int distance2 = mesafe(trigPin2, echoPin2, maximumRange, minimumRange);
  int distance3 = mesafe(trigPin3, echoPin3, maximumRange, minimumRange);
  int distance4 = mesafe(trigPin4, echoPin4, maximumRange, minimumRange);

  // Ölçümleri bir diziye atayalım
  int distances[4] = {distance1, distance2, distance3, distance4};
  int minDistance = 0;
  
  // En küçük (geçerli) mesafeyi bulalım
  for (int i = 0; i < 4; i++) {
    if (distances[i] != 0) {  // 0 değeri, geçersiz ölçüm anlamına gelir
      if (minDistance == 0 || distances[i] < minDistance) {
        minDistance = distances[i];
      }
    }
  }
  
  // Eğer geçerli bir mesafe varsa, buzzer'ı bu mesafeye göre çalıştır
  if (minDistance != 0) {
    melodi(minDistance * 10);
  } else {
    // Geçerli ölçüm yoksa kısa bir süre bekle
    delay(100);
  }
}

// Belirtilen trig ve echo pinleriyle mesafe ölçümü yapan fonksiyon
int mesafe(int trig, int echo, int maxrange, int minrange) {
  long duration;
  int distance;
  
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration / 58.2;  // cm cinsinden mesafe hesaplaması
  delay(50);

  // Ölçüm sınırlarının dışında kalan değerleri geçersiz sayıyoruz
  if (distance >= maxrange || distance <= minrange)
    return 0;
    
  return distance;
}

// Buzzer için basit melodi oluşturma fonksiyonu
int melodi(int dly) {
  tone(buzzerPin, 440);  // 440 Hz sesi çal
  delay(dly);
  noTone(buzzerPin);
  delay(dly);
}
