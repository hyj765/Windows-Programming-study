#include <iostream>
#include <Windows.h>

#define PIPE_NAME "\\\\.\\pipe\\MyPipe"

int main()
{
    HANDLE hPipe;
    DWORD dwBytesRead;
    char buffer[1024];

    // ������ ����
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

    // Ŭ���̾�Ʈ ���� ���
    if (ConnectNamedPipe(hPipe, NULL))
    {
        std::cout << "Client connected" << std::endl;

        // ������ ����
        if (ReadFile(hPipe, buffer, sizeof(buffer), &dwBytesRead, NULL))
        {
            std::cout << "Received data: " << buffer << std::endl;

            // ������ �۽�
            const char* sendData = "Hello, client!";
            DWORD dwBytesWritten;
            WriteFile(hPipe, sendData, strlen(sendData) + 1, &dwBytesWritten, NULL);
        }
        else
        {
            std::cout << "Failed to read data" << std::endl;
        }
    }

    // ������ �ݱ�
    CloseHandle(hPipe);

    return 0;
}
