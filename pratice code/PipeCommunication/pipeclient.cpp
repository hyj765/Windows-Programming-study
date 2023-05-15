#include <iostream>
#include <Windows.h>

#define PIPE_NAME "\\\\.\\pipe\\MyPipe"

int main()
{
    HANDLE hPipe;
    DWORD dwBytesWritten;
    char buffer[1024];

    // 파이프 연결
    hPipe = CreateFileA(
        PIPE_NAME,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hPipe == INVALID_HANDLE_VALUE)
    {
        std::cout << "Failed to connect to the pipe" << std::endl;
        return 1;
    }

    std::cout << "Connected to the server" << std::endl;

    // 데이터 송신
    const char* sendData = "Hello, server!";
    WriteFile(hPipe, sendData, strlen(sendData) + 1, &dwBytesWritten, NULL);

    // 데이터 수신
    DWORD dwBytesRead;
    if (ReadFile(hPipe, buffer, sizeof(buffer), &dwBytesRead, NULL))
    {
        std::cout << "Received data: " << buffer << std::endl;
    }
    else
    {
        std::cout << "Failed to read data" << std::endl;
    }

    // 파이프 닫기
    CloseHandle(hPipe);

    return 0;
}
