#include <IRremote.h>
#include <IRremoteInt.h>

#include <Servo.h> 

#define RECV_PIN  A0

#define SRV1      A1
#define SRV2      A2
#define SRV3      A3
#define SRV4      3
#define SRV5      5
#define SRV6      6

IRrecv irrecv(RECV_PIN);

decode_results results;

// twelve servo objects can be created on most boards
Servo myservo1;  // create servo object to control a servo 
Servo myservo2;  // create servo object to control a servo 
Servo myservo3;  // create servo object to control a servo 
Servo myservo4;  // create servo object to control a servo
Servo myservo5;  // create servo object to control a servo
Servo myservo6;  // create servo object to control a servo

const int pos_min = 0;
const int pos_max = 180;

int pos = pos_min;

void setup()
{
  irrecv.enableIRIn(); // Start the receiver
  Serial.setTimeout(3000);
  Serial.begin(115200);
  showHelp();
}

char input[6];  // 受信データ用
int i = 0;

String readstr;
String substr;
String cmdstr;
String angle;

void loop() {
  if (irrecv.decode(&results)) {
    if(results.value != 0xFFFFFFFF){
      Serial.println(results.value, HEX);
    }
    irrecv.resume(); // Receive the next value
  }

  readstr = ""; // シリアルからの読み込み文字列のクリア

  if(Serial.available()){                   //シリアルポートにデータがたまっているか確認
//    readstr = Serial.readStringUntil(';'); // 区切り文字を指定
    input[i] = Serial.read();
    // 文字数が6以上 or 末尾文字
    if (i > 5 || input[i] == ';') {
      // 末尾に終端文字の挿入
      input[i] = '\0';
      // 受信文字列を送信
      Serial.print(input);
      Serial.println("");
     // 文字列にデータを格納
      readstr = String(input);
     // カウンタの初期化
      i = 0;
    }else{
      i++;
    }
    substr = readstr.substring(0, 2);
    cmdstr = readstr.substring(2, 4);
    if(readstr.length() > 4){
      angle = readstr.substring(2, 5);
    }else{
      angle = pos_max + 1;
    }
    // Serial.println(substr);                      //受信したデータを送り返す

    if(substr == "1_"){
      if(cmdstr == "at" || cmdstr == "AT"){
        myservo1.attach(SRV1);
        Serial.println("Servo1 is attached");
      }else if(cmdstr == "dt" || cmdstr == "DT"){
        myservo1.detach();
        Serial.println("Servo1 is detached");
      }else if(angle.toInt() >= pos_min && angle.toInt() <= pos_max){
        myservo1.write(angle.toInt());
        Serial.print("Servo1 angle = ");
        Serial.println(angle.toInt());
      }
    }else if(substr == "2_"){
      if(cmdstr == "at" || cmdstr == "AT"){
        myservo2.attach(SRV2);
        Serial.println("Servo2 is attached");
      }else if(cmdstr == "dt" || cmdstr == "DT"){
        myservo2.detach();
        Serial.println("Servo2 is detached");
      }else if(angle.toInt() >= pos_min && angle.toInt() <= pos_max){
        myservo2.write(angle.toInt());
        Serial.print("Servo2 angle = ");
        Serial.println(angle.toInt());
      }
    }else if(substr == "3_"){
      if(cmdstr == "at" || cmdstr == "AT"){
        myservo3.attach(SRV3);
        Serial.println("Servo3 is attached");
      }else if(cmdstr == "dt" || cmdstr == "DT"){
        myservo3.detach();
        Serial.println("Servo3 is detached");
      }else if(angle.toInt() >= pos_min && angle.toInt() <= pos_max){
        myservo3.write(angle.toInt());
        Serial.print("Servo3 angle = ");
        Serial.println(angle.toInt());
      }
    }else if(substr == "4_"){
      if(cmdstr == "at" || cmdstr == "AT"){
        myservo4.attach(SRV4);
        Serial.println("Servo4 is attached");
      }else if(cmdstr == "dt" || cmdstr == "DT"){
        myservo4.detach();
        Serial.println("Servo4 is detached");
      }else if(angle.toInt() >= pos_min && angle.toInt() <= pos_max){
        myservo4.write(angle.toInt());
        Serial.print("Servo4 angle = ");
        Serial.println(angle.toInt());
      }
    }else if(substr == "5_"){
      if(cmdstr == "at" || cmdstr == "AT"){
        myservo5.attach(SRV5);
        Serial.println("Servo5 is attached");
      }else if(cmdstr == "dt" || cmdstr == "DT"){
        myservo5.detach();
        Serial.println("Servo5 is detached");
      }else if(angle.toInt() >= pos_min && angle.toInt() <= pos_max){
        myservo5.write(angle.toInt());
        Serial.print("Servo5 angle = ");
        Serial.println(angle.toInt());
      }
    }else if(substr == "6_"){
      if(cmdstr == "at" || cmdstr == "AT"){
        myservo6.attach(SRV6);
        Serial.println("Servo6 is attached");
      }else if(cmdstr == "dt" || cmdstr == "DT"){
        myservo6.detach();
        Serial.println("Servo6 is detached");
      }else if(angle.toInt() >= pos_min && angle.toInt() <= pos_max){
        myservo6.write(angle.toInt());
        Serial.print("Servo6 angle = ");
        Serial.println(angle.toInt());
      }
    }else if(substr == "/h" || substr == "/H"){
      showHelp();  
    }
  }
  delay(10);
}

void showHelp(){
  Serial.println("IR receive and Servo Control demo");
  Serial.println("Usage: [CH]_[Command];");
  Serial.println(" CH: Servo No. (1-6)");
  Serial.println(" Command:");
  Serial.println("  at: attach servo");
  Serial.println("  dt: detach servo");
  Serial.println("  000-180: servo angle (need 3 digit)");
  Serial.println(" Finally the terminal character \";\" is required");
  Serial.println("/h; is show this help.");
  Serial.println("");
}

