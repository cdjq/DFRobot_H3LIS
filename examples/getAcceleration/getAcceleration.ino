/**！
 * @file getAcceleration.ino
 * @brief Get the acceleration in x, y, z directions
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2021-01-16
 * @get from https://www.dfrobot.com
 * @https://github.com/DFRobot/DFRobot_H3LIS
 */


#include <DFRobot_H3LIS.h>

//当你使用I2C通信时,使用下面这段程序,使用DFRobot_H3LIS_I2C构造对象
/*!
 * @brief Constructor 
 * @param pWire I2c controller
 * @param addr  I2C address(0x18/0x19)
 */
//DFRobot_H3LIS_I2C acce(&Wire,0x19);
DFRobot_H3LIS_I2C acce;

//当你使用SPI通信时,使用下面这段程序,使用DFRobot_H3LIS_SPI构造对象
#if defined(ESP32) || defined(ESP8266)
#define H3LIS_CS  D3
#elif defined(__AVR__) || defined(ARDUINO_SAM_ZERO)
#define H3LIS_CS 3
#elif (defined NRF5)
#define H3LIS_CS P3
#endif
/*!
 * @brief Constructor 
 * @param cs : Chip selection pinChip selection pin
 * @param spi :SPI controller
 */
//DFRobot_H3LIS_SPI acce(/*cs = */H3LIS_CS);

void setup(void){

  Serial.begin(9600);
  //Chip initialization
  while(acce.begin()){
     delay(1000);
     Serial.println("init failure");
  }
  //Get chip id
  Serial.print("chip id : ");
  Serial.println(acce.getID(),HEX);
  
  /**
    set range:Range(g)
          e100_g ,/<±100g>/
          e200_g ,/<±200g>/
  */
  acce.setRange(/*Range = */DFRobot_H3LIS::e100_g);

  /**
    Set data measurement rate：
      ePowerDown_0HZ = 0,
      eLowPower_halfHZ,
      eLowPower_1HZ,
      eLowPower_2HZ,
      eLowPower_5HZ,
      eLowPower_10HZ,
      eNormal_50HZ,
      eNormal_100HZ,
      eNormal_400HZ,
      eNormal_1000HZ,
  */
  acce.setAcquireRate(/*Rate = */DFRobot_H3LIS::eNormal_50HZ);
  delay(1000);
}

void loop(void){



    //Get the acceleration in the three directions of xyz
    float ax,ay,az;
    ax = acce.readAccX();//Get the acceleration in the x direction
    ay = acce.readAccY();//Get the acceleration in the y direction
    az = acce.readAccZ();//Get the acceleration in the z direction
    //acce.getAcceFromXYZ(/*accx = */ax,/*accy = */ay,/*accz = */az);//第二种获取三方向加速度的方法
    Serial.print("Acceleration x: "); //print acceleration
    Serial.print(ax);
    Serial.print(" g \ty: ");
    Serial.print(ay);
    Serial.print(" g \tz: ");
    Serial.print(az);
    Serial.println(" g");
    delay(300);

}