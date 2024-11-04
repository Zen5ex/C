#include <iostream>
#include <windows.h>

void wipeBootSector(const std::string& drive) {
    // Îòêðûâàåì äèñê äëÿ çàïèñè
    HANDLE hDrive = CreateFile(
        drive.c_str(), // Íàïðèìåð, "\\\\.\\PhysicalDrive0"
        GENERIC_WRITE,  // Îòêðûòü äëÿ çàïèñè
        0,             // Íåò ñîâìåñòíîãî äîñòóïà
        nullptr,       // Íåò àòðèáóòîâ áåçîïàñíîñòè
        OPEN_EXISTING, // Îòêðûòü ñóùåñòâóþùèé äèñê
        0,             // Íåò äîïîëíèòåëüíûõ ôëàãîâ
        nullptr        // Íåò øàáëîíà
    );

    if (hDrive == INVALID_HANDLE_VALUE) {
        std::cerr << "Eror disk code: " << GetLastError() << std::endl;
        return;
    }

    // Çàïèñûâàåì 512 áàéò íóëåé
    char buffer[512] = {0};
    DWORD bytesWritten;

    BOOL result = WriteFile(hDrive, buffer, sizeof(buffer), &bytesWritten, nullptr);
    if (!result) {
        std::cerr << "disk write error: " << GetLastError() << std::endl;
    } else {
        std::cout << "MBR deleted." << std::endl;
    }

    // Çàêðûâàåì äåñêðèïòîð äèñêà
    CloseHandle(hDrive);
}

int main() {
    std::string drive;
    std::cout << "Enter Disk name, \\\\.\\PhysicalDrive0): ";
    std::getline(std::cin, drive);

    wipeBootSector(drive);

    return 0;
}
