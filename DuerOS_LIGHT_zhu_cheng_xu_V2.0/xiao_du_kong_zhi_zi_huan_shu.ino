void duerPowerState(const String &state) //小度电源类操作的回调函数
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

    BlinkerDuerOS.powerState("on");
    BlinkerDuerOS.print();
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

    BlinkerDuerOS.powerState("off");
    BlinkerDuerOS.print();
  }
}

void duerColor(int32_t color) //小度颜色设置的回调函数
{
  BLINKER_LOG("需要设置颜色: ", color);

  colorR = color >> 16 & 0xFF;
  colorG = color >> 8 & 0xFF;
  colorB = color & 0xFF;

  BLINKER_LOG("红基色: ", colorR, ", 绿基色: ", colorG, ", 蓝基色: ", colorB);

  wsMode = BLINKER_CMD_COMMON;

  BlinkerDuerOS.color(color);
  BlinkerDuerOS.print();
}

void duerMode(const String &mode) //小度模式设置的回调函数
{
  BLINKER_LOG("需要设置模式: ", mode);
  wsState = true;
  if (mode == BLINKER_CMD_DUEROS_READING) //阅读模式
  {
    colorR = 255;
    colorG = 150;
    colorB = 50;
    colorW = 255; //杏黄色
  }
  else if (mode == BLINKER_CMD_DUEROS_SLEEP) //睡眠
  {
    colorR = 255;
    colorG = 50;
    colorB = 0;
    colorW = 64; //红橙光，四分之一亮度
  }
  else if (mode == BLINKER_CMD_DUEROS_NIGHT_LIGHT || BLINKER_CMD_DUEROS_MOON) //夜灯/月亮
  {
    colorR = 254;
    colorG = 221;
    colorB = 120;
    colorW = 85; //茉莉，三分之一亮度
  }
  else if (mode == BLINKER_CMD_DUEROS_LIGHTING || BLINKER_CMD_DUEROS_SUN) //照明/太阳
  {
    colorR = 255;
    colorG = 255;
    colorB = 255;
    colorW = 255;
  }
  else if (mode == BLINKER_CMD_DUEROS_ROMANTIC) //浪漫
  {
    a = colorR;
    b = colorG;
    c = colorB;
    d = colorW;
  }
  else if (mode == BLINKER_CMD_DUEROS_JUDI) //蹦迪
  {
    a = colorR;
    b = colorG;
    c = colorB;
    d = colorW;
  }
  else if (mode == BLINKER_CMD_DUEROS_RELAX) //放松
  {
    a = colorR;
    b = colorG;
    c = colorB;
    d = colorW;
  }
  wsMode = mode;
  update_ing();

  BlinkerDuerOS.mode(mode);
  BlinkerDuerOS.print();
}

void duercMode(const String &cmode) //小度取消模式设置的回调函数
{
  BLINKER_LOG("需要取消模式: ", cmode);

  colorR = 255;
  colorG = 255;
  colorB = 255;
  colorW = 255;

  wsMode = BLINKER_CMD_COMMON; //恢复普通模式(照明模式)
  update_ing();

  BlinkerDuerOS.mode(wsMode);
  BlinkerDuerOS.print();
}

void duerBright(const String &bright) //小度亮度控制的回调函数
{
  BLINKER_LOG("需要设置亮度: ", bright);
  if (bright == BLINKER_CMD_MAX)
    colorW = 255;
  else if (bright == BLINKER_CMD_MIN)
    colorW = 2;
  else
    colorW = bright.toInt() * 2.55;
  BLINKER_LOG("现在设置亮度: ", colorW);
  if (wsState)
  {
    pixels.setBrightness(colorW);
    pixels.show();
  }
  BlinkerDuerOS.brightness(colorW);
  BlinkerDuerOS.print();
}

void duerRelativeBright(int32_t bright) //小度步长设置亮度的回调函数
{
  BLINKER_LOG("需要设置步长亮度: ", bright);
  if (colorW + bright < 255 && colorW + bright >= 0)
    colorW += bright;

  BLINKER_LOG("现在设置亮度: ", colorW);
  if (wsState)
  {
    pixels.setBrightness(colorW);
    pixels.show();
  }
  BlinkerDuerOS.brightness(bright);
  BlinkerDuerOS.print();
}

void duerQuery(int32_t queryCode) //小度查询设备运行时间
{
  BLINKER_LOG("小度查询运行时间:", queryCode);
  BlinkerDuerOS.time(millis());
  BlinkerDuerOS.print();
}
