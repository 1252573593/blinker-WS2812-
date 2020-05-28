/*      2 RGB信号输出       */
#define BLINKER_WIFI            //定义Blinker接入方式为WIFI
#define BLINKER_ESP_SMARTCONFIG //采用EspTouch/SmartConfig方式配网
#define BLINKER_DUEROS_LIGHT    //定义小度设备类型

#include <Blinker.h>
#include <Adafruit_NeoPixel.h>

char auth[] = "2fce699bb138";

#define PIN 2       //定义控制引脚
int NUMPIXELS = 60; //定义LED个数
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

BlinkerRGB WS2812("RGBKey");      //新建颜色组件, 用于读取/设置RGB及亮度值
BlinkerButton Button0("kaiguan"); //新建开关组件
BlinkerButton Button1("M1");      //新建普通模式组件
BlinkerButton Button2("M2");      //新建跑马灯1组件
BlinkerButton Button3("M3");      //新建跑马灯2组件
BlinkerButton Button4("M4");      //新建阅读模式组件
BlinkerButton Button5("M5");      //新建睡眠模式组件
BlinkerButton Button6("M6");      //新建夜灯模式组件
BlinkerButton Button7("M7");      //新建照明模式组件
BlinkerButton Button8("M8");      //新建放松模式组件
BlinkerSlider Slider("geshu");    //新建滑动条组件，用于设置点亮LED个数

uint8_t colorR = 255, colorG = 255, colorB = 255, colorW = 255;
uint8_t a = 255, b = 255, c = 255, d = 255; //临时存储灯的四变量，用于普通模式时恢复
bool wsState = true;                        //定义灯的开关状态存储位，初始开
String wsMode = BLINKER_CMD_COMMON;         //定义灯的模式存储位，初始普通模式

void setup()
{
  Serial.begin(115200);
  BLINKER_DEBUG.stream(Serial);

  pinMode(PIN, OUTPUT);

  Blinker.begin(auth);
  Blinker.attachData(dataRead);
  Blinker.attachHeartbeat(heartbeat);

  BlinkerDuerOS.attachPowerState(duerPowerState);
  BlinkerDuerOS.attachColor(duerColor);
  BlinkerDuerOS.attachMode(duerMode);
  BlinkerDuerOS.attachCancelMode(duercMode);
  BlinkerDuerOS.attachBrightness(duerBright);
  BlinkerDuerOS.attachRelativeBrightness(duerRelativeBright);
  BlinkerDuerOS.attachQuery(duerQuery);

  WS2812.attach(ws2812_callback);   //注册颜色组件
  Button0.attach(button0_callback); //注册开关组件
  Button1.attach(button1_callback); //注册普通模式组件
  Button2.attach(button2_callback); //注册跑马灯1组件
  Button3.attach(button3_callback); //注册跑马灯2组件
  Button4.attach(button4_callback); //注册阅读模式组件
  Button5.attach(button5_callback); //注册睡眠模式组件
  Button6.attach(button6_callback); //注册夜灯模式组件
  Button7.attach(button7_callback); //注册照明模式组件
  Button8.attach(button8_callback); //注册放松模式组件
  Slider.attach(slider_callback);   //注册滑动条组件

  update_ing();

  pixels.begin();
  pixelShow(); //开机默认普通模式=照明模式
}

void loop()
{
  Blinker.run();
  update_ing();
  if (wsState)
  {
    if (wsMode == BLINKER_CMD_DUEROS_ROMANTIC)
      langman();
    else if (wsMode == BLINKER_CMD_DUEROS_JUDI)
      bengdi();
    else if (wsMode == BLINKER_CMD_DUEROS_RELAX)
      yinyue();
    else
    {
      pixelShow();
      Blinker.delay(500);
    }
  }
}
