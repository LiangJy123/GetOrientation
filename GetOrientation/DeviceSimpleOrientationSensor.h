#pragma once
#include "IDeviceOrientationSensor.h"
class DeviceSimpleOrientationSensor :
    public IDeviceOrientationSensor
{
public:
    DeviceSimpleOrientationSensor(ISensor* Sensor, const PROPERTYKEY propertykey);
    DeviceOrientation getOrientation();
};

