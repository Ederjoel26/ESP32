#include <WiFi.h>
#include <FirebaseESP32.h>
#define FIREBASE_HOST "https://aslogic-64fb8-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "P6ME9j0qyDUpSg0ZSEL52PR6IDkI4vKQ4QsH6gsY"

const char* ssid = "Alejandro12";
const char* pass = "12300321#";
FirebaseData firebaseData;
String site = "/Site1/Rack1/";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  Serial.print("Se está conectado a la red WiFi denominada: ");
  Serial.print(ssid);
  Serial.println();
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address:");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void loop() {
  Serial.begin(115200);
  Firebase.setString(firebaseData, site + "Energia", false);
}

void Notificacion(String Mensaje){
  http.begin("https://fcm.googleapis.com/fcm/send");
      String data = "{";
      data = data + "\"to\":\"/topics/Aslogic\",";
      data = data + "\"notification\": {";
      data = data + "\"body\": \"" + Mensaje + "\",";
      data = data + "\"title\":\"CCAI\"";
      data = data + "} }";
      http.addHeader("Authorization", "key=AAAAKn2RV54:APA91bEHRxts4k3zDkL4bZ51LcQhk2uIK-7GxdjsABOop_R-RSMBVhAsQbqrv1fGAYkdI36O6_z1Ie64V-M89lXpUAn3KVrmHBwHv2Yst4_5SHebxdbXLeKL_twgIOE8Fnzau85dueFT");
      http.addHeader("Content-Type", "application/json");
      http.addHeader("Content-Length", (String)data.length());
      int httpResponseCode = http.POST(data);
}
