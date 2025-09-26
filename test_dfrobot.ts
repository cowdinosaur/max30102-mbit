/**
 * Test file for DFRobot Blood Oxygen Sensor
 */

dfrBloodOxygen.begin()
basic.forever(function () {
    serial.writeString("Heartbeat: ")
    serial.writeLine("" + dfrBloodOxygen.getHeartbeat())
    serial.writeString("SPO2: ")
    serial.writeLine("" + dfrBloodOxygen.getSPO2())
    serial.writeString("Temperature: ")
    serial.writeLine("" + dfrBloodOxygen.getTemperature())
    basic.pause(1000)
})
