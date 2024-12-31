#include "serial.h"
#include <iostream>
#include <windows.h>


HANDLE hSerial;

void sendCommandToESP32(const char* command) {
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Serial port not initialized." << std::endl;
        return;
    }

    DWORD bytesWritten;
    WriteFile(hSerial, command, strlen(command), &bytesWritten, NULL);
    WriteFile(hSerial, "\r\n", 2, &bytesWritten, NULL);
}

bool receiveDataFromESP32(std::string& receivedData) {
    char buffer[256];
    DWORD bytesRead = 0;
    if (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        receivedData = buffer;
        return true;
    }
    return false;
}

void closeSerialPort() {
    CloseHandle(hSerial);
}

void readData() {
    static std::string data;
    if (!receiveDataFromESP32(data)) {
        system("cls");
        std::cerr << "Fail to receive !" << std::endl;
        return;
    }
    int s = data.find("PWM_L");
    data[s] = '0';
    int e = data.find("PWM_L");
    data[s] = 'P';
    system("cls");
    std::wcout << "Êý¾ÝÏÔÊ¾£º" << std::endl << std::endl;
    for (size_t i = s; i < e; i++) {
        std::cout << data[i];
    }
    std::cout << std::endl;
}
