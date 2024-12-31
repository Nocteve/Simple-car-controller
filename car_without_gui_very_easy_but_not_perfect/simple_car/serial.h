#pragma once
#ifndef SERIAL_H
#define SERIAL_H

#include <windows.h>
#include <string>

extern HANDLE hSerial;

void sendCommandToESP32(const char* command);
bool receiveDataFromESP32(std::string& receivedData);
void closeSerialPort();
void readData();
#endif // SERIAL_H
#pragma once
