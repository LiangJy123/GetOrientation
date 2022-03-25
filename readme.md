# Get Orientation
Get deivce Orientation in Windows

There are many ways to get Windows device orientation , such as UWP , Unity and so on .

But if your App isn't built from those platform API, it is not easy.

You need to get datas from sensors and some sensors need you to convert their output to what you want.

So , this sample base on windows API can help you to get datas and convert if it needed.
## Get Datas from Sensor
We can get orientation from two kinds of sensors.
- SimpleOrientationSensor

Sensor Type is SENSOR_TYPE_AGGREGATED_DEVICE_ORIENTATION ( {CDB5D8F7-3CFD-41C8-8542-CCE622CF5D6E} ).

Data Type is SENSOR_DATA_TYPE_SIMPLE_DEVICE_ORIENTATION .

Here is output .
```
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
```
- DevcieOrientationSensor

Sensor Type is SENSOR_TYPE_AGGREGATED_DEVICE_ORIENTATION ( {9F81F1AF-C4AB-4307-9904-C828BFB90829} ).

Data Type is SENSOR_DATA_TYPE_QUATERNION.

Here is output , Quaternion . We need to convert it to orientation .
```
x , y , z , w
```

## Convert datas
- Quaternion -> Orientation
The solution is from [stackoverflow](https://stackoverflow.com/questions/56769428/device-orientation-using-quaternion#:~:text=%20Given%20that%20you%27ve%20already%20managed%20to%20convert,largest%20absolute%20value.%20This%20will%20tell...%20More%20)
```C++
/*
if the device x axis is the most vertical, the device is in a landscape orientation;
if the device y axis is the most vertical, the device is in a portrait orientation;
if the device z axis is the most vertical, the device has the screen pointing up or down.
*/

    Quaternion quat(x, y, z, w);
    Quaternion cquat = Quaternion::Conjugate(quat);
    auto vec = Quaternion::FromToRotation(Quaternion::ToEuler(cquat), Vector3(0, 0, 1));

```
The dependency of  Quaternion headers is from [Quaternion](https://github.com/YclepticStudios/gmath.git)

