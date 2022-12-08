#include <ESP8266WiFi.h>

//无线网络初始化方法
void initNetwork();

void setup() {

  WiFi.mode(WIFI_STA);

  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);
  initNetwork();
  digitalWrite(LED_BUILTIN, HIGH);

  
}

void loop() {
}

void toggleLED() {
  static int pinStatus = LOW;

  if (pinStatus == HIGH)
    pinStatus = LOW;
  else
    pinStatus = HIGH;
  digitalWrite(16, pinStatus);
}
void initNetwork(){
  int tryIndex = 0;
  bool ConnectSucc = false;

  Serial.println();
  Serial.print("setAutoConnect(use last config if exist):");
  Serial.println(WiFi.setAutoConnect(true));
  Serial.println("StartWifiConnect");
  WiFi.begin();
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    if (tryIndex++ >= 20)  // 超时10秒
    {
      Serial.println();
      Serial.println("ConnectWifiTimeout,use smartconfig");
      WiFi.beginSmartConfig();
      while (true) {
        delay(500);
        Serial.print(".");
        if (WiFi.smartConfigDone()) {
          Serial.println("\nSmartConfig succ");
          ConnectSucc = true;
          break; 
        }
        toggleLED();
      }
      if (ConnectSucc)
        break;
    }
  }

  // 等待获取网络ip配置成功
  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
  }
  Serial.println();
  //设置Debug信息输出到串口
  WiFi.printDiag(Serial);

  //ip
  Serial.println(WiFi.localIP());
  // //wifi名称
  // Serial.println(WiFi.SSID());
  // //WIFI密码
  // Serial.println(WiFi.psk());
}
