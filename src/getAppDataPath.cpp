#include "getAppDataPath.h"

using namespace std;

string getAppDataPath() {
    PWSTR rawPath = NULL;
    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_CREATE, NULL, &rawPath))) {
        char strPath[MAX_PATH];
        wcstombs_s(NULL, strPath, sizeof(strPath), rawPath, _TRUNCATE);
        CoTaskMemFree(rawPath);
        return string(strPath);
    }
    return "";
}