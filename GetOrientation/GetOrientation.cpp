// GetOrientation.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "DeviceOrientationSensorFactory.h"
#include "DisplayOrientation.h"
const std::string  deviceOrientationsArray[] = { "NotRotated", "Rotated90DegreesCounterclockwise" ,  // device x axis points up/down
        "Rotated180DegreesCounterclockwise","Rotated270DegreesCounterclockwise",   // device y axis points up/down
    "Faceup","Facedown" };      // device z axis points up/down
const std::string displayOrientationsArray[] = { "Angle0","Angle90","Angle180","Angle270" };
int main()
{
    DisplayOrientation::GetOrientation();
    std::cout << "Start\n";
    auto deviceSensor = DeviceOrientationSensorFactory::FindAndCreatDeviceOrientationSensorInstance();
    do
    {
        if (deviceSensor == nullptr)
        {
            std::cout << "There is NO device orientation sensor (or need running as admin)\n";
            break;
        }

        auto res = deviceSensor->getOrientation();
        if (res == DeviceOrientation::GetError)
        {
            std::cout << "Get error when get sensor data\n";
            break;
        }
        std::cout << "Device orientation : " << deviceOrientationsArray[(int)res] << std::endl;
        Sleep(2000);


    } while (false);

    DeviceOrientationSensorFactory::Release(deviceSensor);

    auto displayOrientation = DisplayOrientation::GetOrientation();
    std::cout << "Display orientation : " << displayOrientationsArray[(int)displayOrientation] << std::endl;


}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
