// --- 引脚设置 ---
const int buttonPin = 2;   // 按钮（按下开始表演）
const int ledPin    = 5;   // LED 灯（舞台主角）
const int potPin    = A0;  // 电位器旋钮（控制速度）

// --- 变量 ---
int buttonState = 0;   // 按钮状态
int fadeAmount  = 0;   // LED 每次亮度变化多少
int ms          = 0;   // 电位器读到的数值

void setup() {
  Serial.begin(9600);          // 打开串口，方便调试
  pinMode(buttonPin, INPUT_PULLUP);   // 设置按钮为输入
  pinMode(ledPin, OUTPUT);     // 设置LED为输出
  pinMode(potPin, INPUT);      // 设置电位器为输入
}

void loop() {
  detect();                    // 检查按钮和旋钮
  digitalWrite(ledPin, LOW);   // 默认灯是关的

  // 如果按钮被按下，开始表演
  if (!buttonState) {
    blinkLED();   // 灯眨两下
    fadeLED();    // 灯像呼吸一样渐亮渐暗
  }
}

// --- 检测按钮和电位器 ---
void detect() {
  buttonState = digitalRead(buttonPin);  // 读取按钮
  ms = analogRead(potPin);               // 读取旋钮 (0~1023)

  // 把旋钮数值换算成步长 (1~13)，数值越大，灯变快
  fadeAmount = map(ms, 0, 1023, 6, 1);

  Serial.println(String(ms) + " " + String(fadeAmount)); // 输出到电脑看
}

// --- LED 闪烁两次 ---
void blinkLED() {
  for (int i = 0; i < 2; i++) {   // 循环2次
    digitalWrite(ledPin, HIGH);   // 灯亮
    delay(ms);                    // 等一会儿
    digitalWrite(ledPin, LOW);    // 灯灭
    delay(ms);                    // 等一会儿
  }
}

// --- LED 渐亮渐暗（像呼吸）---
void fadeLED() {
  // 逐渐变亮
  for (int i = 0; i <= 255; i += fadeAmount) {
    analogWrite(ledPin, i);
    delay(20);
  }
  // 逐渐变暗
  for (int i = 255; i >= 0; i -= fadeAmount) {
    analogWrite(ledPin, i);
    delay(20);
  }
}
