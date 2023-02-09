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
