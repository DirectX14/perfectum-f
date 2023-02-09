#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

bool setWallpaper(string);

int main() {
    cout << "Script started..." << endl;

    const string wallPic = "Perfectum_Background";
    bool status = setWallpaper(wallPic);
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