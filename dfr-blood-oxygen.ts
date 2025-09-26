/**
* Functions for working with the DFRobot Blood Oxygen Sensor
*/ 
//% color=#D93922 icon="\uf08a"
namespace dfrBloodOxygen {
    
    /**
    * Initializes the DFRobot Blood Oxygen sensor
    */	
    //% weight=100
    //% blockId="dfr_begin"
    //% block="initialize DFRobot Blood Oxygen sensor"
    //% shim=dfrBloodOxygen::begin
    export function begin(){
        return
    }

    /**
    * Get the heartbeat value in beats per minute (BPM).
    */
    //% weight=90
    //% blockId="dfr_get_heartbeat"
    //% block="heartbeat (BPM)"
    //% shim=dfrBloodOxygen::getHeartbeat
    export function getHeartbeat(): number {
        return 0
    }

    /**
    * Get the blood oxygen saturation (SpO2) value as a percentage.
    */
    //% weight=80
    //% blockId="dfr_get_spo2"
    //% block="blood oxygen (SpO2)"
    //% shim=dfrBloodOxygen::getSPO2
    export function getSPO2(): number {
        return 0
    }

    /**
    * Get the temperature in degrees Celsius.
    */
    //% weight=70
    //% blockId="dfr_get_temperature"
    //% block="temperature (C)"
    //% shim=dfrBloodOxygen::getTemperature
    export function getTemperature(): number {
        return 0
    }
}
