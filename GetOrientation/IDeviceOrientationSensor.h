#pragma once
#include <windows.h>
#include <sensors.h>
#include <sensorsapi.h>
#include <string>
enum class DeviceOrientation
{
    GetError = -1,
    //
    // 摘要:
    //     设备未旋转。
    NotRotated = 0,
    //
    // 摘要:
    //     设备逆时针旋转 90 度。
    Rotated90DegreesCounterclockwise = 1,
    //
    // 摘要:
    //     设备逆时针旋转 180 度。
    Rotated180DegreesCounterclockwise = 2,
    //
    // 摘要:
    //     设备逆时针旋转 270 度。
    Rotated270DegreesCounterclockwise = 3,
    //
    // 摘要:
    //     将设备面朝上并且显示对用户不可见。
    Faceup = 4,
    //
    // 摘要:
    //     将设备面朝下并且显示对用户隐藏。
    Facedown = 5
};


class IDeviceOrientationSensor
{
public:
    IDeviceOrientationSensor(ISensor* Sensor,  const PROPERTYKEY propertykey) {_pSensor = Sensor; _propertykey = propertykey;};
    ~IDeviceOrientationSensor() { if (_pSensor != nullptr) { _pSensor->Release(); _pSensor = nullptr; } };
    virtual DeviceOrientation getOrientation() = 0;
protected:

    ISensor* _pSensor = nullptr;
    PROPERTYKEY _propertykey;

    HRESULT getReport(PROPVARIANT& pvTilt)
    {
        ISensorDataReport* pReport = nullptr;
        if (_pSensor == nullptr)
            return E_POINTER;
        auto hr = _pSensor->GetData(&pReport);
        if (FAILED(hr))
        {
            OutputDebugString(L"Unable to _pSensor GetData() ");
            return hr;
        }
        hr = pReport->GetSensorValue(_propertykey, &pvTilt);
        if (FAILED(hr))
        {
            OutputDebugString(L"Unable to _pSensor GetSensorValue() ");
            return hr;
        }

        if (pReport != nullptr)
        {
            pReport->Release();
        }

        return hr;
    };
    

};
