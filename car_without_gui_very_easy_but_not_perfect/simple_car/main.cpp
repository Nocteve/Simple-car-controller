#include <iostream>
#include <string>
#include <windows.h>
#include <cstring>
#include "serial.h"
#ifndef SERIAL_H
#define SERIAL_H
#endif

int main() {
    // �û�ѡ��COM�˿�
    std::wstring comPort;
    std::cout << "������COM�˿�(����: COM3): ";
    getline(std::wcin, comPort);

    // �û�ѡ������
    int baudRate;
    std::cout << "�����벨����(����: 9600): ";
    std::cin >> baudRate;

    std::wstring portName = comPort;
    hSerial = CreateFile(portName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,    // ������
        NULL, // Ĭ�ϰ�ȫ����
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    // ���ò����ʡ�����λ��ֹͣλ��
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    dcbSerialParams.BaudRate = baudRate; // ʹ�ô���Ĳ�����
    dcbSerialParams.ByteSize = 8;          // 8������λ
    dcbSerialParams.StopBits = ONESTOPBIT; // 1��ֹͣλ
    dcbSerialParams.Parity = NOPARITY;     // ����żУ��

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error setting serial port parameters." << std::endl;
        CloseHandle(hSerial);
        std::cerr << "��ʼ������ʧ��!\n";
        return 1;
    }

    while (true) {
        readData();
        std::cout << "==============================\n";
        std::cout << "���ܳ����Ʋ˵�\n";
        std::cout << "ѡ�����:\n";
        std::cout << "1. ǰ��\n";
        std::cout << "2. ����\n";
        std::cout << "3. ��ת\n";
        std::cout << "4. ��ת\n";
        std::cout << "5. �����ٶ�\n";
        std::cout << "6. ͣ��\n";
        std::cout << "7. ��������\n";
        std::cout << "0. �˳�\n";
        std::cout << "==============================\n";
        std::cout << "������ѡ��: ";

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
            std::cout << "�������ٶ�(0-255): ";
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
            std::cout << "���˳�" << std::endl;
            return 0;

        default:
            std::cout << "��Чѡ�������ѡ��\n";
            break;
        }
    }
	return 0;
}