#include <iostream>
#include <windows.h>

void wipeBootSector(const std::string& drive) {
    // Открываем диск для записи
    HANDLE hDrive = CreateFile(
        drive.c_str(), // Например, "\\\\.\\PhysicalDrive0"
        GENERIC_WRITE,  // Открыть для записи
        0,             // Нет совместного доступа
        nullptr,       // Нет атрибутов безопасности
        OPEN_EXISTING, // Открыть существующий диск
        0,             // Нет дополнительных флагов
        nullptr        // Нет шаблона
    );

    if (hDrive == INVALID_HANDLE_VALUE) {
        std::cerr << "Ошибка открытия диска: " << GetLastError() << std::endl;
        return;
    }

    // Записываем 512 байт нулей
    char buffer[512] = {0};
    DWORD bytesWritten;

    BOOL result = WriteFile(hDrive, buffer, sizeof(buffer), &bytesWritten, nullptr);
    if (!result) {
        std::cerr << "Ошибка записи на диск: " << GetLastError() << std::endl;
    } else {
        std::cout << "Загрузочный сектор успешно стер." << std::endl;
    }

    // Закрываем дескриптор диска
    CloseHandle(hDrive);
}

int main() {
    std::string drive;
    std::cout << "Введите букву диска (например, \\\\.\\PhysicalDrive0): ";
    std::getline(std::cin, drive);

    wipeBootSector(drive);

    return 0;
}
