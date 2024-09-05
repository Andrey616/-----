#include <EasyHID.h>
boolean but0;
boolean but1;
boolean but2;
boolean but3;
boolean but4;
boolean but5;
boolean key_but1;
boolean key_but2;
boolean key_but3;
boolean key_but4;
boolean key_but5;

boolean key_berds = 1;

void setup() {
  Serial.begin(9600);
  HID.begin();                          // Инициализация USB
  pinMode(5, INPUT_PULLUP);             // Кнопка
  pinMode(6, INPUT_PULLUP); 
  pinMode(7, INPUT_PULLUP); 
  pinMode(8, INPUT_PULLUP); 
  pinMode(9, INPUT_PULLUP); 
  pinMode(10, INPUT_PULLUP); 
  pinMode(13, OUTPUT);                  // Светодиод на борту платы
  digitalWrite(13, 1);

}

void loop() {
  but0 = !digitalRead(5);  
  but1 = !digitalRead(6); 
  but2 = !digitalRead(7); 
  but3 = !digitalRead(8); 
  but4 = !digitalRead(9);
  but5 = !digitalRead(10); // считывает кнопку
  
  if (but0 && but1){ // попугай
    static uint32_t timer1 = millis(); 
    Keyboard.click(KEY_LEFT_WIN,KEY_R);
    timer1 = millis();
    while (key_berds){
      if (millis()- timer1 >= 600 && millis()- timer1 <= 650){
        Keyboard.write("cmd");
        Keyboard.click(KEY_ENTER);
      }  
      if (millis()- timer1 >= 1200 && millis()- timer1 <= 1250){
        Keyboard.write("curl parrot.live");
        Keyboard.click(KEY_ENTER);
        Keyboard.click(KEY_PAGE_UP);
        Keyboard.click(KEY_ENTER);
        key_berds = 0;
      }
    }
  } 
  
  key_berds = 1;
  
  
  static uint32_t timer = millis();     // Миллис - таймер (НЕ DELAY!!!)
  if (millis() - timer >= 120) {        // Каждые 120 мс
    timer = millis();
    //Serial.print(!digitalRead(5)); Serial.print("\n");

  
    if (but0){                        // Ctrl+c
      Serial.print("But0"); 
      Keyboard.press(KEY_LEFT_CONTROL);  
      Keyboard.click(KEY_C);  
      Keyboard.releaseAll(); 
    }
    if (but1){                        // Ctrl+v
      Serial.print("But1");
      if (!digitalRead(6) && key_but1 == 0){
          key_but1 = 1;
          Keyboard.press(KEY_LEFT_CONTROL);  
          Keyboard.click(KEY_V);
          Keyboard.releaseAll(); 
        }
    }
    if (digitalRead(6) && key_but1 == 1){
          key_but1 = 0;
    }
    if (but2){
      Serial.print("But2"); // Alt+Tab
      Keyboard.press(KEY_LEFT_ALT);  
      Keyboard.click(KEY_TAB);  
      Keyboard.releaseAll();
      while (!digitalRead(7)) {
        Serial.print("Go");
        Keyboard.press(KEY_LEFT_ALT);
        if (!digitalRead(8) && key_but2 == 0){
          key_but2 = 1;
          Keyboard.click(KEY_TAB); 
        }
        if (digitalRead(8) && key_but2 == 1){
            key_but2 = 0;
        }
      }
      Keyboard.releaseAll();
    }
    if (but3){
      Serial.print("But3"); // Space
      if (!digitalRead(8) && key_but3 == 0){
        key_but3 = 1;
        Keyboard.press(KEY_LEFT_CONTROL);  
        Keyboard.click(KEY_I);  
        Keyboard.releaseAll();  
      }
    } 
    if (digitalRead(8) && key_but3 == 1){
          key_but3 = 0;
    }
    if (but4){
      Serial.print("But4"); // Delete
      if (!digitalRead(9) && key_but4 == 0){
        key_but4 = 1;
        Keyboard.press(KEY_LEFT_SHIFT);  
        Keyboard.click(KEY_TAB);  
        Keyboard.releaseAll(); 
      }
    } 
    if (digitalRead(9) && key_but4 == 1){
          key_but4 = 0;
    }
    if (but5){ // Ctrl+B
      Serial.print("But5");
      if (!digitalRead(10) && key_but5 == 0){
        key_but5 = 1;
        Keyboard.press(KEY_LEFT_CONTROL);  
        Keyboard.click(KEY_B);  
        Keyboard.releaseAll();
      }
    }
    if (digitalRead(10) && key_but5 == 1){
          key_but5 = 0;
    }
    
  }
  
            
        
        
//    if (but == 1){
//      digitalWrite(13, 1);
//       Keyboard.press(KEY_1);              // Зажимаем клавишу '1'
//      Keyboard.releaseAll();              // Отпускаем все клавиши
//      Keyboard.click(KEY_SPACE);          // Кликаем пробел (press + releaseAll)
//      Keyboard.write('-');                // Выводим тире
//      Keyboard.println(" Hello world!");  // Печать в println
// 
//    }else{
//      digitalWrite(13, 0);
//    }
//    Serial.print("Button: "); Serial.print(!digitalRead(3)); Serial.print("\n");
//
//  
//    }

  HID.tick();   // Вызываем тикер не реже чем каждые 10 мс!
}
