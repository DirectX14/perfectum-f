#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

bool setWallpaper(string);
bool setComputerName(string);

bool setRegistryOEMInfo(string, string);

int main() {
    cout << "Script started..." << endl;

    const string wallPic = "Perfectum_Background";
    bool status = setWallpaper(wallPic);
    cout << "Status: " << status << endl;

    status = setComputerName("Perfectum-PC");
    cout << "Status: " << status << endl;


    cout << "Editing registry..." << endl;
    status << setRegistryOEMInfo("asd", "asdd");
    cout << "Status: " << status << endl;

	return 0;
}

bool setWallpaper(string imageName)
{
    // Get the current directory and store it into a char string
    char buf[256];
    GetCurrentDirectoryA(256, buf);
    // Create the absolute path to the image
    string file = buf + string("\\images\\") + imageName + string(".png");
    // Convert the string to a wide string
    std::wstring widestr = std::wstring(file.begin(), file.end());
    // Convert the wide string to a c string
    const wchar_t* filenm = widestr.c_str();
    // Set the wallpaper to the given image
    return SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (void*)filenm, SPIF_UPDATEINIFILE);
}

bool setComputerName(string computerName) {
    cout << "Changing PC Name..." << endl;

    DWORD dwLastErr;

    bool flResult = SetComputerNameExA(ComputerNamePhysicalDnsHostname, computerName.c_str());

    if (flResult == 0)
    {
        dwLastErr = GetLastError();
        wcout << dwLastErr << endl;
    }

    return flResult;
}


//https://learn.microsoft.com/en-us/windows/win32/sysinfo/writing-and-deleting-registry-data
bool setRegistryOEMInfo(string key, string value) {
    LSTATUS rgResult;
    HKEY hKeyRoot = HKEY_LOCAL_MACHINE;

    LONG lResult;

    LPCTSTR lpSubKey;
    HKEY hKey;

    lpSubKey = TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\TestDir");


    lResult = RegDeleteKey(hKeyRoot, lpSubKey);

    if (lResult == ERROR_SUCCESS)
        return 1;

    lResult = RegOpenKeyEx(hKeyRoot, lpSubKey, 0, KEY_READ, &hKey);

    if (lResult != ERROR_SUCCESS)
    {
        if (lResult == ERROR_FILE_NOT_FOUND) {
            cout << "Registry Key not found." << endl;
            return 1;
        }
        else {
            cout << "Error opening registry key." << endl;
            return 0;
        }
    }

    RegCloseKey(hKey);

    lResult = RegDeleteKey(hKeyRoot, lpSubKey);

    if (lResult == ERROR_SUCCESS)
        return 1;

    return 0;

    //rgResult = RegOpenKeyExA(HKEY_LOCAL_MACHINE, )

    //return 0;
}