#include <iostream>
#include <Windows.h>

#define PIPE_NAME "\\\\.\\pipe\\MyPipe"

int main()
{
    HANDLE hPipe;
    DWORD dwBytesRead;
    char buffer[1024];

    // 파이프 생성
    hPipe = CreateNamedPipeA(
        PIPE_NAME,
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        1024,
        1024,
        0,
        NULL
    );

    if (hPipe == INVALID_HANDLE_VALUE)
    {
        std::cout << "Failed to create the pipe" << std::endl;
        return 1;
    }

    std::cout << "Waiting for client connection..." << std::endl;

    // 클라이언트 연결 대기
    if (ConnectNamedPipe(hPipe, NULL))
    {
        std::cout << "Client connected" << std::endl;

        // 데이터 수신
        if (ReadFile(hPipe, buffer, sizeof(buffer), &dwBytesRead, NULL))
        {
            std::cout << "Received data: " << buffer << std::endl;

            // 데이터 송신
            const char* sendData = "Hello, client!";
            DWORD dwBytesWritten;
            WriteFile(hPipe, sendData, strlen(sendData) + 1, &dwBytesWritten, NULL);
        }
        else
        {
            std::cout << "Failed to read data" << std::endl;
        }
    }

    // 파이프 닫기
    CloseHandle(hPipe);

    return 0;
}
