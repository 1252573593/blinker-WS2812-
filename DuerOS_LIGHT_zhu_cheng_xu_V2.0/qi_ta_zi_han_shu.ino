String getColor()
{
  uint32_t color = colorR << 16 | colorG << 8 | colorB;
  switch (color)
  {
    case 0xFF0000:
      return "Red"; //红
    case 0xFFFF00:
      return "Yellow"; //黄
    case 0x0000FF:
      return "Blue"; //蓝
    case 0x00FF00:
      return "Green"; //绿
    case 0xFFFFFF:
      return "White"; //白
    case 0x000000:
      return "Black"; //黑
    case 0x00FFFF:
      return "Cyan"; //青
    case 0x800080:
      return "Purple"; //紫
    case 0xFFA500:
      return "Orange"; //橘
    default:
      return "White"; //白
  }
}


void pixelShow() //设置颜色及亮度，每个LED色彩输出相同
{
  pixels.fill(pixels.Color(colorR, colorG, colorB), 0, NUMPIXELS);
  pixels.setBrightness(colorW);
  pixels.show();
}


void rainbowCycle(uint8_t wait) //彩虹流水子函数
{
  uint16_t i, j;
  for (j = 0; j < 256 * 2 && wsMode == BLINKER_CMD_DUEROS_ROMANTIC && wsState; j++)
  {
    Blinker.run();
    update_ing();
    for (i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, Wheel(((i * 256 / NUMPIXELS) + j) & 255));
    }
    pixels.setBrightness(colorW);
    pixels.show();
    //      Blinker.delay(wait);
  }
}


uint32_t Wheel(byte WheelPos) //彩虹流水颜色转化函数
{
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85)
  {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170)
  {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


void langman() //浪漫模式(幻彩呼吸)
{
  for (uint16_t j = 0; j < 256 * 2 && wsMode == BLINKER_CMD_DUEROS_ROMANTIC && wsState; j++) //幻彩呼吸
  {
    update_ing();
    for (uint16_t i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, Wheel(j));
    }
    pixels.setBrightness(colorW);
    pixels.show();
    Blinker.delay(15);
  }

  for (int i = colorW; i >= 0 && wsMode == BLINKER_CMD_DUEROS_ROMANTIC && wsState; i--) //渐灭
  {
    pixels.setBrightness(i);
    pixels.show();
    Blinker.delay(7);
  }

  update_ing();

  for (int i = 0; i <= colorW && wsMode == BLINKER_CMD_DUEROS_ROMANTIC && wsState; i++) //彩虹🌈渐亮
  {
    for (int j = 0; j < NUMPIXELS; j++)
    {
      pixels.setPixelColor(j, Wheel((j * 256 / NUMPIXELS) & 255));
    }
    pixels.setBrightness(i);
    pixels.show();
    Blinker.delay(10);
  }

  update_ing();

  rainbowCycle(0); //彩虹流水

  update_ing();

  for (int i = colorW; i >= 0 && wsMode == BLINKER_CMD_DUEROS_ROMANTIC && wsState; i--) //渐灭
  {
    pixels.setBrightness(i);
    pixels.show();
    Blinker.delay(10);
  }

  update_ing();

  for (int i = 0; i <= colorW && wsMode == BLINKER_CMD_DUEROS_ROMANTIC && wsState; i++) //渐亮红色
  {
    for (int j = 0; j < NUMPIXELS; j++)
    {
      pixels.setPixelColor(j, 255, 0, 0);
    }
    pixels.setBrightness(i);
    pixels.show();
    Blinker.delay(7);
  }

  update_ing();
}


void bengdi() //蹦迪模式(DJ爆闪)
{
  for (uint16_t j = 0; j < 256 * 3 && wsMode == BLINKER_CMD_DUEROS_JUDI && wsState; j = j + 45)
  {
    update_ing();

    for (int i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, Wheel(j));
    }
    pixels.setBrightness(colorW);
    pixels.show();
    Blinker.delay(150);

    pixels.clear();
    pixels.show();
    Blinker.delay(100);
  }
}


void yinyue() //放松模式(音乐灯)
{


}


void heartbeat() //心跳包
{
  BLINKER_LOG("状态同步!");
  update_ing();
}


void update_ing() //更新APP显示的模式状态
{
  if (wsState)
  {
    Button0.icon("far fa-laugh-wink"); //开心脸
    Button0.color("#7FFF00");          //绿
    Button0.text("状态为开启");
    Button0.print("on");
  }
  else
  {
    Button0.icon("fas fa-sad-tear"); //悲伤脸
    Button0.color("#DC143C");        //红
    Button0.text("状态为关闭");
    Button0.print("off");
  }

  Slider.print(NUMPIXELS);                      //滑动条状态更新
  WS2812.print(colorR, colorG, colorB, colorW); //取色板及亮度组件更新

  if (wsMode == BLINKER_CMD_COMMON) //模式1
  {
    Button1.color("#FF1493"); //红
    Button2.color("#3CB371"); //绿
    Button3.color("#3CB371"); //绿
    Button8.color("#3CB371"); //绿
    Button4.color("#1E90FF"); //蓝
    Button5.color("#1E90FF"); //蓝
    Button6.color("#1E90FF"); //蓝
    Button7.color("#1E90FF"); //蓝
    Button1.print();
    Button2.print();
    Button3.print();
    Button4.print();
    Button5.print();
    Button6.print();
    Button7.print();
    Button8.print();
  }
  else if (wsMode == BLINKER_CMD_DUEROS_ROMANTIC) //模式2
  {
    Button1.color("#3CB371"); //绿
    Button2.color("#FF1493"); //红
    Button3.color("#3CB371"); //绿
    Button8.color("#3CB371"); //绿
    Button4.color("#1E90FF"); //蓝
    Button5.color("#1E90FF"); //蓝
    Button6.color("#1E90FF"); //蓝
    Button7.color("#1E90FF"); //蓝
    Button1.print();
    Button2.print();
    Button3.print();
    Button4.print();
    Button5.print();
    Button6.print();
    Button7.print();
    Button8.print();
  }
  else if (wsMode == BLINKER_CMD_DUEROS_JUDI) //模式3
  {
    Button1.color("#3CB371"); //绿
    Button2.color("#3CB371"); //绿
    Button3.color("#FF1493"); //红
    Button8.color("#3CB371"); //绿
    Button4.color("#1E90FF"); //蓝
    Button5.color("#1E90FF"); //蓝
    Button6.color("#1E90FF"); //蓝
    Button7.color("#1E90FF"); //蓝
    Button1.print();
    Button2.print();
    Button3.print();
    Button4.print();
    Button5.print();
    Button6.print();
    Button7.print();
    Button8.print();
  }
  else if (wsMode == BLINKER_CMD_DUEROS_READING) //模式4
  {
    Button1.color("#3CB371"); //绿
    Button2.color("#3CB371"); //绿
    Button3.color("#3CB371"); //绿
    Button8.color("#3CB371"); //绿
    Button4.color("#FF1493"); //红
    Button5.color("#1E90FF"); //蓝
    Button6.color("#1E90FF"); //蓝
    Button7.color("#1E90FF"); //蓝
    Button1.print();
    Button2.print();
    Button3.print();
    Button4.print();
    Button5.print();
    Button6.print();
    Button7.print();
    Button8.print();
  }
  else if (wsMode == BLINKER_CMD_DUEROS_SLEEP) //模式5
  {
    Button1.color("#3CB371"); //绿
    Button2.color("#3CB371"); //绿
    Button3.color("#3CB371"); //绿
    Button8.color("#3CB371"); //绿
    Button4.color("#1E90FF"); //蓝
    Button5.color("#FF1493"); //红
    Button6.color("#1E90FF"); //蓝
    Button7.color("#1E90FF"); //蓝
    Button1.print();
    Button2.print();
    Button3.print();
    Button4.print();
    Button5.print();
    Button6.print();
    Button7.print();
    Button8.print();
  }
  else if (wsMode == BLINKER_CMD_DUEROS_NIGHT_LIGHT) //模式6
  {
    Button1.color("#3CB371"); //绿
    Button2.color("#3CB371"); //绿
    Button3.color("#3CB371"); //绿
    Button8.color("#3CB371"); //绿
    Button4.color("#1E90FF"); //蓝
    Button5.color("#1E90FF"); //蓝
    Button6.color("#FF1493"); //红
    Button7.color("#1E90FF"); //蓝
    Button1.print();
    Button2.print();
    Button3.print();
    Button4.print();
    Button5.print();
    Button6.print();
    Button7.print();
    Button8.print();
  }
  else if (wsMode == BLINKER_CMD_DUEROS_LIGHTING) //模式7
  {
    Button1.color("#3CB371"); //绿
    Button2.color("#3CB371"); //绿
    Button3.color("#3CB371"); //绿
    Button8.color("#3CB371"); //绿
    Button4.color("#1E90FF"); //蓝
    Button5.color("#1E90FF"); //蓝
    Button6.color("#1E90FF"); //蓝
    Button7.color("#FF1493"); //红
    Button1.print();
    Button2.print();
    Button3.print();
    Button4.print();
    Button5.print();
    Button6.print();
    Button7.print();
    Button8.print();
  }
  else if (wsMode == BLINKER_CMD_DUEROS_RELAX) //模式8
  {
    Button1.color("#3CB371"); //绿
    Button2.color("#3CB371"); //绿
    Button3.color("#3CB371"); //绿
    Button8.color("#FF1493"); //红
    Button4.color("#1E90FF"); //蓝
    Button5.color("#1E90FF"); //蓝
    Button6.color("#1E90FF"); //蓝
    Button7.color("#1E90FF"); //蓝
    Button1.print();
    Button2.print();
    Button3.print();
    Button4.print();
    Button5.print();
    Button6.print();
    Button7.print();
    Button8.print();
  }
}
