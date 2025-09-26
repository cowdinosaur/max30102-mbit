/**
* DFRobot Blood Oxygen Sensor
* 
* This file is for MakeCode extensions.
*/

#include "pxt.h"
#include "DFRobot_BloodOxygen_S.h"

using namespace pxt;

namespace dfrBloodOxygen {
    DFRobot_BloodOxygen_S_I2C *sensor;

    //%
    void begin() {
        if (sensor == NULL) {
            sensor = new DFRobot_BloodOxygen_S_I2C(DEV_ADDRESS);
            sensor->begin();
        }
    }

    //%
    int16_t getHeartbeat() {
        if (sensor == NULL) {
            begin();
        }
        sensor->getHeartbeatSPO2();
        return sensor->_sHeartbeatSPO2.Heartbeat;
    }

    //%
    int16_t getSPO2() {
        if (sensor == NULL) {
            begin();
        }
        sensor->getHeartbeatSPO2();
        return sensor->_sHeartbeatSPO2.SPO2;
    }

    //%
    float getTemperature() {
        if (sensor == NULL) {
            begin();
        }
        return sensor->getTemperature_C();
    }
}
