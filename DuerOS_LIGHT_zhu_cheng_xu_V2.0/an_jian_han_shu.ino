void ws2812_callback(uint8_t r_value, uint8_t g_value, uint8_t b_value, uint8_t bright_value) //颜色组件回调函数
{
  BLINKER_LOG("取色板颜色设置");
  if (wsMode != BLINKER_CMD_DUEROS_ROMANTIC && wsMode != BLINKER_CMD_DUEROS_JUDI)
  {
    BLINKER_LOG("R 值: ", r_value);
    BLINKER_LOG("G 值: ", g_value);
    BLINKER_LOG("B 值: ", b_value);
    BLINKER_LOG("亮度值: ", bright_value);

    colorR = r_value;
    colorG = g_value;
    colorB = b_value;
    colorW = bright_value;

    wsMode = BLINKER_CMD_COMMON;
    update_ing();
  }
  else if (wsState)
  {
    BLINKER_LOG("亮度值: ", bright_value);
    colorW = bright_value;
    pixels.setBrightness(colorW);
    pixels.show();
  }
}

void button0_callback(const String &state) //开关组件回调
{
  BLINKER_LOG("需要设置电源状态: ", state);
  if (state == BLINKER_CMD_ON)
  {
    BLINKER_LOG("打开!");

    Button0.icon("far fa-laugh-wink"); //开心脸
    Button0.color("#7FFF00");          //绿
    Button0.text("状态为开启");
    Button0.print("on");

    wsState = true;
    if (colorW == 0)
      colorW = 255;
  }
  else if (state == BLINKER_CMD_OFF)
  {
    BLINKER_LOG("关闭!");

    Button0.icon("fas fa-sad-tear"); //悲伤脸
    Button0.color("#DC143C");        //红
    Button0.text("状态为关闭");
    Button0.print("off");

    wsState = false;

    pixels.clear();
    pixels.show();//关闭所有灯参数
  }
}

void button1_callback(const String &state) //普通模式组件
{
  BLINKER_LOG("普通: ", state);
  colorR = a;
  colorG = b;
  colorB = c;
  colorW = d;

  wsMode = BLINKER_CMD_COMMON;
  update_ing();
}

void button2_callback(const String &state) //跑马灯1组件(幻彩呼吸)
{
  BLINKER_LOG("浪漫: ", state);
  a = colorR;
  b = colorG;
  c = colorB;
  d = colorW;

  wsMode = BLINKER_CMD_DUEROS_ROMANTIC;
  update_ing();
}

void button3_callback(const String &state) //跑马灯2组件(DJ爆闪)
{
  BLINKER_LOG("蹦迪: ", state);
  a = colorR;
  b = colorG;
  c = colorB;
  d = colorW;

  wsMode = BLINKER_CMD_DUEROS_JUDI;
  update_ing();
}

void button4_callback(const String &state) //阅读模式组件
{
  BLINKER_LOG("阅读: ", state);
  colorR = 255;
  colorG = 150;
  colorB = 50;
  colorW = 255; //杏黄色
  wsMode = BLINKER_CMD_DUEROS_READING;
  update_ing();
}

void button5_callback(const String &state) //睡眠模式组件
{
  BLINKER_LOG("睡眠: ", state);
  colorR = 255;
  colorG = 50;
  colorB = 0;
  colorW = 64; //红橙光，四分之一亮度
  wsMode = BLINKER_CMD_DUEROS_SLEEP;
  update_ing();
}

void button6_callback(const String &state) //夜灯模式组件
{
  BLINKER_LOG("夜灯: ", state);
  colorR = 254;
  colorG = 221;
  colorB = 120;
  colorW = 85; //茉莉，三分之一亮度
  wsMode = BLINKER_CMD_DUEROS_NIGHT_LIGHT;
  update_ing();
}

void button7_callback(const String &state) //照明模式组件
{
  BLINKER_LOG("照明: ", state);
  colorR = 255;
  colorG = 255;
  colorB = 255;
  colorW = 255;
  wsMode = BLINKER_CMD_DUEROS_LIGHTING;
  update_ing();
}

void button8_callback(const String &state) //放松模式组件(音乐灯)
{
  BLINKER_LOG("放松: ", state);
  a = colorR;
  b = colorG;
  c = colorB;
  d = colorW;

  wsMode = BLINKER_CMD_DUEROS_RELAX;
  update_ing();
}

void slider_callback(int32_t value) //滑动条组件回调
{
  BLINKER_LOG("滑动条数值: ", value);
  pixels.clear();
  pixels.show();//关闭所有灯
  NUMPIXELS = value;
}

void dataRead(const String &data) //未定义组件触发时的回调函数
{
  BLINKER_LOG("未定义组件触发: ", data);
  Blinker.vibrate();
  uint32_t BlinkerTime = millis();
  Blinker.print("millis", BlinkerTime);
}
