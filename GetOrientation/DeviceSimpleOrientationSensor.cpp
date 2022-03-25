#include "DeviceSimpleOrientationSensor.h"
DeviceSimpleOrientationSensor::DeviceSimpleOrientationSensor(ISensor* Sensor, const PROPERTYKEY propertykey):IDeviceOrientationSensor(Sensor , propertykey)
{
    ;
}
DeviceOrientation DeviceSimpleOrientationSensor::getOrientation()
{
    PROPVARIANT pvTilt;
    PropVariantInit(&pvTilt);
    auto hr = getReport(pvTilt);
    if (FAILED(hr))
    {
        return DeviceOrientation::GetError;
    }
    float fRet = V_UI4(&pvTilt);
    PropVariantClear(&pvTilt);
    int iRet = fRet;
    return (DeviceOrientation)iRet;
}
