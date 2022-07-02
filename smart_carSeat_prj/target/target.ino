#include <avr/sleep.h>
#define interruptPin 2

int Led = 9;                                         // LED를 3번핀 설정
int FSRsensor = A0;                           // 센서값을 아나로그 A0핀 설정
int value = 0;                                       // loop에서 사용할 변수 설정
void setup() 

{
  pinMode(interruptPin,INPUT_PULLUP);
  pinMode(Led, OUTPUT);                     // 핀모드 LED를 출력으로 설정
  Serial.begin(9600);                       // 시리얼 통신 설정 (보드레이트 9600)
}


void loop() 

{
  int w_value = 0;
  if(w_value <= 3){
    Going_To_Sleep();
  }
  value = analogRead(FSRsensor);              // 센서값을 아나로그로 읽어 value 변수에 저장
  Serial.println(value);                      // 센서값을 시리얼 모니터에 출력
  value = map(value, 0, 1023, 0, 255);        // value에 저장된 센서값(0~1023)을 PWM값 0~255의 범위로 변환
  analogWrite(Led, value);                    // 변환된 PWM값으로 LED를 켠다 (변하는 값으로 밝기를 조절) 
  delay(1000);                                 // 1초의 딜레이
  

}


void Going_To_Sleep(){
    sleep_enable();//Enabling sleep mode
    attachInterrupt(0, wakeUp, LOW);//attaching a interrupt to pin d2
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);//Setting the sleep mode, in our case full sleep
    digitalWrite(LED_BUILTIN,LOW);//turning LED off
    delay(1000); //wait a second to allow the led to be turned off before going to sleep
    sleep_cpu();//activating sleep mode
    Serial.println("just woke up!");//next line of code executed after the interrupt 
    digitalWrite(LED_BUILTIN,HIGH);//turning LED on
  }

void wakeUp(){
  Serial.println("Interrrupt Fired");//Print message to serial monitor
   sleep_disable();//Disable sleep mode
  detachInterrupt(0); //Removes the interrupt from pin 2;
}
