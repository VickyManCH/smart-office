#define BLYNK_TEMPLATE_ID       "TMPL6jhVsZh6k"
#define BLYNK_TEMPLATE_NAME     "EmbedProj"
#define BLYNK_AUTH_TOKEN        "rDuaj7jS2MQ8TnjdiVznAkQ1wTuD2R2P"

#define LINE_TOKEN              "WXOS8wnuiXJnpmfY8jK4zqaUbyihdwuS8Vuel0qIpVN"

// Google Project ID
#define PROJECT_ID              "embed-project-443308"

// Service Account's client email
#define CLIENT_EMAIL            "embed-project@embed-project-443308.iam.gserviceaccount.com"

#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>
#include <HardwareSerial.h>
#include <ArtronShop_LineNotify.h>
#include <ESP_Google_Sheet_Client.h>
#include <Adafruit_Sensor.h>
#include <vector>

// Service Account's private key
const char PRIVATE_KEY[] PROGMEM = "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQCdUPWEzB7qsWdm\n2KhOmqK2+TB6h2bA5pDBuX7dmqIO0QPcL6THsvZ9TboU6Cw++d7I1d+w8ujUVYlL\n6h5S/NIfOT0EIZz3sjyC4sdxTqzc8RRlfLinYqtdPz7FRbX8iXY1MmgVcpsJ6s+U\nC7fibE7IZHhYh1m4/0MTtICb3rp16HlosmOEdiqzLR4H3cipnBXkUuTPY27iFMgy\nngbfUmjFdT0kS/Bnnwm3NpfDabRkWQm1KPqXjsvXogC21jMrZXNumNMZ1snjeTV9\nQpQjOBmVEdHh6JOYn/4EchUsHURp1CzjmvEghhIBhknpi645+G91zytqpNKWX+SL\ns0XqKNO1AgMBAAECggEACtQKwkRGkIL7ihG5rAdq0ctfMd/mC7sTFbKN7/T32Ks8\nZ8iDwBcqbj+OYmgEu6T5V7uY9RYTPqJQnAAWbEHouKt47rLdmhMTpTK05bCzp1WU\nwNOP5j2dbAKxcGS2/RX9I/Y/QdKsp0cZWKhh1Nz9oz9/JSDT5S700ANpotD25qyp\nBbLeuV2ZRRrLqTc95npby4IU8bTZyroJi2oiqaLLt7qC+KlECRRRHr7JDflsB3YF\nJ1jSO0QGI/nCBBQ5IJBl25zwoJpkDWuJaooc4iuGU/VIlFWf37tiDgMRxx/LQN8c\nQ0d+vSxT2i67F+4ZVnRZwpSq7bHi5Wv40wEMmgBntQKBgQDc4ceFcgbXcs6o9yv/\nz+ryQr0jlRbvcXgHRKHgY5YhntCoxAXA1Xr8o7ctJPBlynbsRMu0UWxPFz8BQXje\nN5hCSfx9BZAv4fhNcoVglHzCAlQrmiPIvQsGFMVuQ/7KZ5m1MIxqJhLi8ByLdwJv\n/8b0Q9kAzOd7AFhR+TXicYVO5wKBgQC2U/ZAEPDoETSz1It4vCrLyhyRSS3TDo7H\nFvoL0uCxBFpPhz+BqzRTugIRFLbS8vptCd/+euXa5mpDK7B1if1KyyCM7QDukwjG\njhXvRWMuSdbCZLMhm8e3Guk3YbPDzYson9UJzmh05gXZFR1J//w8xhyrwkwXjev6\nXqCYliYBAwKBgAR48eBK2cadBYA4WQS6AgjbvxasWyWIB6UmB50ShySxIYp5RaCM\n8guRiRD58YAuJFBOaE2DZI0JbHYrDDZ7q7KT6u/hH/VIPw3aZsb42rnW8DtdyKG0\n6jc6TnEYIV2Z0WvwyrcPhExiDkHoq/z2keG6SfeRLpK4BBHM2QF3yPo7AoGAK2iU\nAS7HXEj0ZjgdOJJ8Eea9pG1qxov5vDahM31yV1K0+ag2m3WaULDBWzW2TUTiEGHA\nfYLfBJ3FANb+/QzsTAlOZ57pkONavIMJf9ziPxv/UGrPJxpCkzqJ+dB+Dwj5r6NW\nAi6tOd+l1sgrH/odII7+NnpcyWLVotcynwFobOcCgYEAuPRLijNRGqaYMWVGs31b\nZXDE5pEf37JPGyMebJ8O6lyLso//2qjwIM07nlwmNsbkq79PlfoSj6whR8x41h5o\n39K7ZEEDTdlXTRRc9DDaNp5rcsYsiaOxe3lk2nJZAw91k6xhuJrTA6bZuSNfVT3U\nnPHwbMmuZvYqFy2Bkk8ZP9w=\n-----END PRIVATE KEY-----\n";

// WiFi Credentials
const char* ssid = "DaengGuitar"; // Change later
const char* password = "FlukeGark"; // Change later

// Google Sheets ID
const char spreadsheetId[] = "1ZrdJh84JmRUOr-07_ejirrqdgP001FZLMnP4xM71xso";

// Pin Setup
Servo myServo;
int servoPin = 19;  // Pin ที่เชื่อมต่อกับ Servo
int acPin = 21; // Pin ที่เชื่อมต่อกับ LED แสดงการเปิด-ปิดของแอร์
int lightsPin = 18; // Pin ที่เชื่อมต่อกับ LED แสดงการเปิด-ปิดของไฟออฟฟิศ

// Sensor Serial
int txPin = 22;
int rxPin = 23;
HardwareSerial sensorSerial(1);

// Values from sensors
float temp;
float humid;
float heatidx;
float distance;
float gas;
int vibration;
int motion;

// State variables
bool isDoorOpen = false;
bool isDoorManualOpen = false;
bool isAcOn = false;
bool isLightsOn = false;
bool sheetReady = false;

// Timer variables
BlynkTimer timer;
unsigned long lastTime = 0;  
unsigned long timerDelay = 30000;

std::vector<float> seperate(String input)
{
    int i = 0;
    std::vector<float> o;
    String buffer = "";
    while (i < input.length())
    {
        char b = input[i++];
        if (b == '-')
        {
            o.push_back(buffer.toFloat());
            buffer = "";
        }
        else
        {
            buffer += b;
        }
    }
    //o.push_back(stof(buffer));
    return o;
}

void addDoorOpenLogToGoogleSheets() {
  if (sheetReady && millis() - lastTime > timerDelay) {
    FirebaseJson response;
    FirebaseJson valueRange;
    time_t timestamp;
    time(&timestamp);
    timestamp += 7*3600;
    valueRange.add("majorDimension", "COLUMNS");

    valueRange.set("values/[0]/[0]", ctime(&timestamp));

    bool success = GSheet.values.append(&response /* returned response */, spreadsheetId /* spreadsheet Id to append */, "DoorOpenLog" /* range to append */, &valueRange /* data range to append */);
    if (success) {
      response.toString(Serial, true);
      Serial.println("Successfully added door open log.");
      valueRange.clear();
    } else {
      Serial.println(GSheet.errorReason());
    }
  }
}

void addDataLogToGoogleSheets() {
  if (sheetReady && millis() - lastTime > timerDelay) {
    FirebaseJson response;
    FirebaseJson valueRange;
    valueRange.add("majorDimension", "COLUMNS");
    time_t timestamp;
    time(&timestamp);
    timestamp += 7*3600;

    valueRange.set("values/[0]/[0]", ctime(&timestamp));
    valueRange.set("values/[1]/[0]", temp);
    valueRange.set("values/[2]/[0]", humid);
    valueRange.set("values/[3]/[0]", heatidx);
    valueRange.set("values/[4]/[0]", gas);
    valueRange.set("values/[5]/[0]", bool(vibration));
    valueRange.set("values/[6]/[0]", bool(motion));

    bool success = GSheet.values.append(&response /* returned response */, spreadsheetId /* spreadsheet Id to append */, "DataLog" /* range to append */, &valueRange /* data range to append */);
    if (success) {
      response.toString(Serial, true);
      Serial.println("Successfully added data log.");
      valueRange.clear();
    } else {
      Serial.println(GSheet.errorReason());
    }
  }
}

void handleBlynkReads() {
  // ส่งค่าระยะห่างจากคนถึงประตู (ติด sensor ultrasonic)
  if (distance <= 30 && distance != 0 && !isDoorOpen && !isDoorManualOpen) {
    isDoorOpen = true;
    Serial.println("Door automatically opened.");
    myServo.write(90);  // เปิดประตู
    Blynk.virtualWrite(V7, 1);
    addDoorOpenLogToGoogleSheets();
  } else if (distance > 30 && isDoorOpen && !isDoorManualOpen) {
    isDoorOpen = false;
    Serial.println("Door automatically closed.");
    myServo.write(0);   // ปิดประตู
    Blynk.virtualWrite(V7, 0);
  }
  Blynk.virtualWrite(V1, distance);

  // ส่งค่าอุณหภูมิและความชื้น
  if (heatidx >= 27 && !isAcOn && motion) {
    isAcOn = true;
    Serial.println("Air conditioner automatically turned on.");
    digitalWrite(acPin, HIGH);
    Blynk.virtualWrite(V8, 1);
  } else if (!motion && isAcOn) {
    isAcOn = false;
    Serial.println("Air conditioner automatically turned off.");
    digitalWrite(acPin, LOW);
    Blynk.virtualWrite(V8, 0);
  }
  Blynk.virtualWrite(V2, temp);
  Blynk.virtualWrite(V3, humid);

  // ส่งค่าควัน
  if (gas >= 2200) {
    LINE_Notify_Massage_Option_t gasSticker;
    gasSticker.sticker.package_id = 11539;
    gasSticker.sticker.id = 52114142;
    time_t timestamp;
    time(&timestamp);
    timestamp += 7*3600;
    String message = "The office has high concentration of flammable gas at ";
    message += ctime(&timestamp);
    
    Serial.println(message);
    LINE.send(message, &gasSticker);
  }
  Blynk.virtualWrite(V4, gas);

  // ส่งว่าแผ่นดินไหวหรือไม่
  if (vibration) {
    LINE_Notify_Massage_Option_t earthquakeSticker;
    earthquakeSticker.sticker.package_id = 11538;
    earthquakeSticker.sticker.id = 51626511;
    time_t timestamp;
    time(&timestamp);
    timestamp += 7*3600;
    String message = "There's an earthquake at ";
    message += ctime(&timestamp);

    Serial.println(message);
    Blynk.virtualWrite(V5, "True");
    LINE.send(message, &earthquakeSticker);
  } else {
    Blynk.virtualWrite(V5, "False");
  }

  // ส่งว่ามีการเคลื่อนไหวไหม
  if (motion && !isLightsOn) {
    isLightsOn = true;
    Serial.println("Office lights automatically turned on.");
    Blynk.virtualWrite(V6, "True");
    digitalWrite(lightsPin, HIGH);
  } else if (!motion && isLightsOn) {
    isLightsOn = false;
    Serial.println("Office lights automatically turned off.");
    Blynk.virtualWrite(V6, "False");
    digitalWrite(lightsPin, LOW);
  }
}

BLYNK_WRITE(V7) {
  // เปิด-ปิดประตูแบบแมนวล
  int doorState = param.asInt();
  if (doorState) {
    isDoorOpen = true;
    isDoorManualOpen = true;
    Serial.println("Door manually opened.");
    myServo.write(90);  // เปิดประตู
    addDoorOpenLogToGoogleSheets();
  } else {
    isDoorOpen = false;
    isDoorManualOpen = false;
    Serial.println("Door manually closed.");
    myServo.write(0);  // เปิดประตู
  }
}

BLYNK_WRITE(V8) {
  // เปิด-ปิดแอร์แบบแมนวล
  int acState = param.asInt();
  if (acState) {
    isAcOn = true;
    Serial.println("Air conditioner manually turned on.");
    digitalWrite(acPin, HIGH);
  } else {
    isAcOn = false;
    Serial.println("Air conditioner manually turned off.");
    digitalWrite(acPin, LOW);
  }
}

void setup() {
  Serial.begin(115200);
  sensorSerial.begin(9600, SERIAL_8N1, rxPin, txPin);
  timer.setInterval(60000L, addDataLogToGoogleSheets);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  LINE.begin(LINE_TOKEN);
  myServo.attach(servoPin); // เชื่อมต่อ Servo
  pinMode(acPin, OUTPUT);
  pinMode(lightsPin, OUTPUT);

  /* Google Sheets Setup */
  // Set the seconds to refresh the auth token before expire (60 to 3540, default is 300 seconds)
  GSheet.setPrerefreshSeconds(10 * 60);

  // Begin the access token generation for Google API authentication
  GSheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);
  /* Google Sheets Setup */

  Serial.println("Gateway online.");
}

void loop() {
  sheetReady = GSheet.ready();
  Blynk.run(); // ให้ Blynk ทำงาน
  timer.run();
  if (sensorSerial.available() > 0) {
    /*
    Output from sensorSerial:
      Temperature:x (Celcius)-Humidity:x-HeatIndex:x-UltrasonicDistance:x (cm)-GasConcentration:x-Vibration:x (T or F - 1 or 0)-Motion:x (T or F - 1 or 0)
    */
   
    String input = sensorSerial.readStringUntil('\n');
    std::vector<float> buffer=seperate(input);
    auto i=buffer.begin();
    temp=*i;
    i++;
    humid=*i;
    i++;
    heatidx=*i;
    i++;
    distance=*i;
    i++;
    gas=*i;
    i++;
    vibration=*i;
    i++;
    motion=*i;

    String dataLog = "\n";
    dataLog = "Temperature: ";
    dataLog += String(temp);
    dataLog += "\n";
    dataLog += "Humidity: ";
    dataLog += String(humid);
    dataLog += "\n";
    dataLog += "Heat Index: ";
    dataLog += String(heatidx);
    dataLog += "\n";
    dataLog += "Ultrasonic Distance: ";
    dataLog += String(distance);
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

    handleBlynkReads();

  }
}