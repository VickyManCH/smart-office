#include <HardwareSerial.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <ArtronShop_LineNotify.h>
#include <ESP_Google_Sheet_Client.h>
#include <vector>

// Define Sensor and Serial Pins
#define DHT_PIN 19                  // พินของเซนเซอร์วัดความชื้นและอุณหภูมิ (DHT22)
#define ULTRASONIC_TRIGGER_PIN 18   // พินทริกเกอร์ของเซนเซอร์อัลตราโซนิค วัดระยะห่าง (HC-SR04)
#define ULTRASONIC_ECHO_PIN 17      // พินเอ็คโค่ของเซนเซอร์อัลตราโซนิค วัดระยะห่าง (HC-SR04)
#define MOTION_PIN 26               // พินของเซนเซอร์ตรวจการเคลื่อนไหว (E18-D80NK)
#define VIBRATION_PIN 25            // พินของเซนเซอร์ตรวจจับการสั่นสะเทือน (SW420)
#define GAS_PIN 36                  // พินของเซนเซอร์ตรวจจับแก๊ส (MQ-5)
#define TX_PIN 22
#define RX_PIN 23

// Create Objects
DHT dht(DHT_PIN, DHT22);
HardwareSerial gatewaySerial(1);

String embed(std::vector<float> input){
    String output = "";
    for (auto e:input){
        output += String(e);
        output += "-";
    }
    return output;
}

float getUltrasonicDistance() {
    digitalWrite(ULTRASONIC_TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIGGER_PIN, LOW);

    float duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH);

    float ultrasonic = 0.017 * duration;
    return ultrasonic;
}

void setup() {
    Serial.begin(115200);
    gatewaySerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
    dht.begin();

    // ตั้งค่า pin mode ของ sensor
    pinMode(MOTION_PIN, INPUT);
    pinMode(VIBRATION_PIN, INPUT);
    pinMode(ULTRASONIC_TRIGGER_PIN, OUTPUT);
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);
}

void loop() {
    /* DHT */
    // อ่านค่าจากเซ็นเซอร์
    float temperature = dht.readTemperature(false);
    float humidity = dht.readHumidity();
    float heatindex = dht.computeHeatIndex(temperature, humidity, false);

    // ตรวจสอบว่าอ่านค่าได้สำเร็จหรือไม่
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    /* Motion */
    float motion = digitalRead(MOTION_PIN);
    if (motion == LOW) {
        motion = 1;
    } else {
        motion = 0;
    }

    /* Vibration */
    float vibration = digitalRead(VIBRATION_PIN);

    /* Ultrasonic */
    float ultrasonic = getUltrasonicDistance();

    /* Gas */
    float gas = analogRead(GAS_PIN);


    /* Send data to gateway */
    // ส่งข้อมูลไปยัง Gateway Node
    /*
    Format:
      Temperature:x (Celcius)-Humidity:x-HeatIndex:x-UltrasonicDistance:x (cm)-GasConcentration:x-Vibration:x (T or F - 1 or 0)-Motion:x (T or F - 1 or 0)
    */
    String dataLog = "\n";
    dataLog = "Temperature: ";
    dataLog += String(temperature);
    dataLog += "\n";
    dataLog += "Humidity: ";
    dataLog += String(humidity);
    dataLog += "\n";
    dataLog += "Heat Index: ";
    dataLog += String(heatindex);
    dataLog += "\n";
    dataLog += "Ultrasonic Distance: ";
    dataLog += String(ultrasonic);
    dataLog += "\n";
    dataLog += "Gas Concentration: ";
    dataLog += String(gas);
    dataLog += "\n";
    dataLog += "Earthquake: ";
    dataLog += String(bool(vibration));
    dataLog += "\n";
    dataLog += "Human Presence: ";
    dataLog += String(bool(motion));
    dataLog += "\n";
    Serial.println(dataLog);

    std::vector<float> buffer;
    String dataToSend;
    buffer.push_back(temperature);
    buffer.push_back(humidity);
    buffer.push_back(heatindex);
    buffer.push_back(ultrasonic);
    buffer.push_back(gas);
    buffer.push_back(vibration);
    buffer.push_back(motion);
    dataToSend = embed(buffer);
    
    gatewaySerial.println(dataToSend);
    Serial.println("Data sent to gateway serial.");
    Serial.println();

    delay(5000); // รอ 5 วินาทีก่อนอ่านค่าครั้งถัดไป
}