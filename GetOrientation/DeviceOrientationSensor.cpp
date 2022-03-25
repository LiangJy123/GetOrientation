#include "DeviceOrientationSensor.h"
#include "Quaternion.hpp"

const DeviceOrientation  orientationsArray[] = { DeviceOrientation::Rotated90DegreesCounterclockwise, DeviceOrientation::Rotated270DegreesCounterclockwise ,  // device x axis points up/down
        DeviceOrientation::NotRotated,DeviceOrientation::Rotated180DegreesCounterclockwise,   // device y axis points up/down
    DeviceOrientation::Faceup,DeviceOrientation::Facedown };      // device z axis points up/down

DeviceOrientationSensor::DeviceOrientationSensor(ISensor* Sensor, const PROPERTYKEY propertykey) :IDeviceOrientationSensor(Sensor, propertykey)
{
    ;
}


DeviceOrientation DeviceOrientationSensor::getOrientation()
{
    PROPVARIANT pvTilt;
    auto hr = getReport(pvTilt);
    if (FAILED(hr))
    {
        return DeviceOrientation::GetError;
    }
    
    auto p_element = (float*)pvTilt.caub.pElems;
    auto x = p_element[0];
    auto y = p_element[1];
    auto z = p_element[2];
    auto w = p_element[3];

    Quaternion quat(x, y, z, w);
    Quaternion cquat = Quaternion::Conjugate(quat);
    auto vec = Quaternion::FromToRotation(Quaternion::ToEuler(cquat), Vector3(0, 0, 1));

    int maxIndex = -1;
    double MaxValue = -1;
    for (int i = 0; i < 3; i++)
    {
        if (MaxValue < abs(vec.data[i]))
        {
            maxIndex = i;
            MaxValue = abs(vec.data[i]);
        }
    }
    if (vec.data[maxIndex] > 0)
    {
        maxIndex = maxIndex * 2;
    }
    else
    {
        maxIndex = maxIndex * 2 + 1;
    }

    PropVariantClear(&pvTilt);
    return orientationsArray[maxIndex];
}
