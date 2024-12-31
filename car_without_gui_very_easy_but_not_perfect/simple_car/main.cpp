#include <iostream>
#include <string>
#include <windows.h>
#include <cstring>
#include "serial.h"
#ifndef SERIAL_H
#define SERIAL_H
#endif

int main() {
    // 用户选择COM端口
    std::wstring comPort;
    std::cout << "请输入COM端口(例如: COM3): ";
    getline(std::wcin, comPort);

    // 用户选择波特率
    int baudRate;
    std::cout << "请输入波特率(例如: 9600): ";
    std::cin >> baudRate;

    std::wstring portName = comPort;
    hSerial = CreateFile(portName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,    // 不共享
        NULL, // 默认安全属性
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    // 设置波特率、数据位、停止位等
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    dcbSerialParams.BaudRate = baudRate; // 使用传入的波特率
    dcbSerialParams.ByteSize = 8;          // 8个数据位
    dcbSerialParams.StopBits = ONESTOPBIT; // 1个停止位
    dcbSerialParams.Parity = NOPARITY;     // 无奇偶校验

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error setting serial port parameters." << std::endl;
        CloseHandle(hSerial);
        std::cerr << "初始化串口失败!\n";
        return 1;
    }

    while (true) {
        readData();
        std::cout << "==============================\n";
        std::cout << "智能车控制菜单\n";
        std::cout << "选择操作:\n";
        std::cout << "1. 前进\n";
        std::cout << "2. 后退\n";
        std::cout << "3. 左转\n";
        std::cout << "4. 右转\n";
        std::cout << "5. 调节速度\n";
        std::cout << "6. 停车\n";
        std::cout << "7. 更新数据\n";
        std::cout << "0. 退出\n";
        std::cout << "==============================\n";
        std::cout << "请输入选项: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            sendCommandToESP32("FORWARD");
            break;

        case 2:
            sendCommandToESP32("BACKWARD");
            break;

        case 3:
            sendCommandToESP32("LEFT");
            break;

        case 4:
            sendCommandToESP32("RIGHT");
            break;

        case 5:
            int pwm;
            std::cout << "请输入速度(0-255): ";
            std::cin >> pwm;

            char command[50];
            sprintf_s(command, sizeof(command), "PWM %.2f",static_cast<float>(pwm));
            sendCommandToESP32(command);
            break;

        case 6:
            sendCommandToESP32("STOP");
            break;
        case 7:
            break;
        case 0:
            CloseHandle(hSerial);
            std::cout << "已退出" << std::endl;
            return 0;

        default:
            std::cout << "无效选项，请重新选择。\n";
            break;
        }
    }
	return 0;
}