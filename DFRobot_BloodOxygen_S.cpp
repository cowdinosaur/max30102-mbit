/*!
 * @file DFRobot_BloodOxygen_S.cpp
 * @brief This is the .cpp file for a sensor that can detect human oxygen saturation and heart rate.
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      PengKaixing(kaixing.peng @dfrobot.com)
 * @version  V1.0.0
 * @date  2021-06-21
 * @url https://github.com/DFRobot/DFRobot_BloodOxygen_S
 */
#include "DFRobot_BloodOxygen_S.h"

DFRobot_BloodOxygen_S::DFRobot_BloodOxygen_S(void){}
DFRobot_BloodOxygen_S::~DFRobot_BloodOxygen_S(void){}

void DFRobot_BloodOxygen_S::getHeartbeatSPO2(void)
{
  uint8_t rbuf[8];
  readReg(0x0C,rbuf,8);
  _sHeartbeatSPO2.SPO2 = rbuf[0];
  if(_sHeartbeatSPO2.SPO2 == 0)
  {
    _sHeartbeatSPO2.SPO2 = -1;
  }
  _sHeartbeatSPO2.Heartbeat = ((uint32_t)rbuf[2] << 24) | ((uint32_t)rbuf[3] << 16) | ((uint32_t)rbuf[4] << 8) | ((uint32_t)rbuf[5]);
  if (_sHeartbeatSPO2.Heartbeat == 0)
  {
    _sHeartbeatSPO2.Heartbeat = -1;
  }
}

float DFRobot_BloodOxygen_S::getTemperature_C(void)
{
  uint8_t temp_buf[2];
  readReg(0x14, temp_buf, 2);
  float Temperature = temp_buf[0] * 1.0 + temp_buf[1] / 100.0;
  return Temperature;
}

void DFRobot_BloodOxygen_S::setBautrate(ebautrate bautrate)
{
  uint8_t w_buf[2];
  w_buf[0] = (uint8_t)(bautrate >> 8);
  w_buf[1] = (uint8_t)bautrate;
  writeReg(0x06, w_buf, sizeof(w_buf));
  pxt::uBit.sleep(100);
  w_buf[0] = 0x00;
  w_buf[1] = 0x01;
  writeReg(0x1A, w_buf, sizeof(w_buf));
  pxt::uBit.sleep(1000);
}

uint32_t DFRobot_BloodOxygen_S::getBautrate(void)
{
  uint8_t r_buf[2];
  readReg(0x06, r_buf, sizeof(r_buf));
  uint16_t baudrate_type = (uint16_t)r_buf[0] << 8 | (uint16_t)r_buf[1];
  switch (baudrate_type)
  {
    case 0:
      return 1200;
    case 1:
      return 2400;
    case 3:
      return 9600;
    case 5:
      return 19200;
    case 6:
      return 38400;
    case 7:
      return 57600;
    case 8:
      return 115200;
    default:
      return 9600;
  }
}

void DFRobot_BloodOxygen_S::sensorStartCollect(void)
{
  uint8_t wbuf[2]={0,1};
  writeReg(0x20,wbuf,2);
}

void DFRobot_BloodOxygen_S::sensorEndCollect(void)
{
  uint8_t wbuf[2] = {0, 2};
  writeReg(0x20, wbuf, 2);
}

//I2C underlying communication
DFRobot_BloodOxygen_S_I2C::DFRobot_BloodOxygen_S_I2C(uint8_t addr) : DFRobot_BloodOxygen_S()
{
  this->_I2C_addr = addr;
}

DFRobot_BloodOxygen_S_I2C::~DFRobot_BloodOxygen_S_I2C(void){}


bool DFRobot_BloodOxygen_S_I2C::begin(void)
{
    if(pxt::uBit.i2c.write(this->_I2C_addr, NULL, 0) != MICROBIT_OK){
        return false;
    }
    return true;
}

void DFRobot_BloodOxygen_S_I2C::writeReg(uint16_t reg_addr, uint8_t *data_buf, uint8_t len)
{
    uint8_t buffer[len + 1];
    buffer[0] = (uint8_t)reg_addr;
    memcpy(&buffer[1], data_buf, len);
#if MICROBIT_CODAL
    pxt::uBit.i2c.write(this->_I2C_addr, buffer, len + 1);
#else
    pxt::uBit.i2c.write(this->_I2C_addr, (const char *)buffer, len + 1);
#endif
}

int16_t DFRobot_BloodOxygen_S_I2C::readReg(uint16_t reg_addr, uint8_t *data_buf, uint8_t len)
{
    uint8_t reg = (uint8_t)reg_addr;
#if MICROBIT_CODAL
    pxt::uBit.i2c.write(this->_I2C_addr, &reg, 1, true);
    return pxt::uBit.i2c.read(this->_I2C_addr, data_buf, len);
#else
    pxt::uBit.i2c.write(this->_I2C_addr, (const char*)&reg, 1, true);
    return pxt::uBit.i2c.read(this->_I2C_addr, (char*)data_buf, len);
#endif
}
