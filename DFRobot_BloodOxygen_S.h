/*!
 * @file DFRobot_BloodOxygen_S.h
 * @brief This is the .h file for a sensor that can detect human oxygen saturation and heart rate.
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      PengKaixing(kaixing.peng @dfrobot.com)
 * @version  V1.0.0
 * @date  2021-06-21
 * @url https://github.com/DFRobot/DFRobot_BloodOxygen_S
 */
#ifndef _DFROBOT_BLOODOXYGEN_S_
#define _DFROBOT_BLOODOXYGEN_S_

#include "pxt.h"
#include <cstdint>

#define I2C_MODE 1
#define UART_MODE 2

#define DEV_ADDRESS 0x0D

class DFRobot_BloodOxygen_S
{
public:
  typedef struct
  {
    int16_t SPO2;
    int16_t Heartbeat;
  } sHeartbeatSPO2_t;

  typedef enum
  {
    eBaudrate_1200 = 0,
    eBaudrate_2400,
    eBaudrate_4800,
    eBaudrate_9600,
    eBaudrate_19200,
    eBaudrate_38400,
    eBaudrate_57600,
    eBaudrate_115200,
  } ebautrate;

  sHeartbeatSPO2_t _sHeartbeatSPO2;

public:
  DFRobot_BloodOxygen_S(void);
  ~DFRobot_BloodOxygen_S(void);
  virtual bool begin(void) = 0;
  void getHeartbeatSPO2(void);
  float getTemperature_C(void);
  void setBautrate(ebautrate bautrate);
  uint32_t getBautrate(void);
  void sensorStartCollect(void);
  void sensorEndCollect(void);

protected:
  virtual void writeReg(uint16_t reg_addr, uint8_t *data_buf, uint8_t len) = 0;
  virtual int16_t readReg(uint16_t reg_addr, uint8_t *data_buf, uint8_t len) = 0;
};

class DFRobot_BloodOxygen_S_I2C : public DFRobot_BloodOxygen_S
{
public:
  DFRobot_BloodOxygen_S_I2C(uint8_t addr);
  ~DFRobot_BloodOxygen_S_I2C(void);
  bool begin(void);

protected:
  void writeReg(uint16_t reg_addr, uint8_t *data_buf, uint8_t len);
  int16_t readReg(uint16_t reg_addr, uint8_t *data_buf, uint8_t len);

private:
  uint8_t _I2C_addr;
};

#endif
