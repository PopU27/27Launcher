#include "downloadLatestZip.h"
#include "getAppDataPath.h"

using namespace std;
using namespace cpr;
using namespace filesystem;
using namespace nlohmann;

int downloadLatestZip(const string& apiUrl, const string& name)
{   
    // Makes get request to apiUrl
    cout << "Checking GitHub for the latest ZIP..." << endl;
    Response apiResponse = Get(
        Url{apiUrl},
        Header{
            {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) 27Launcher/1.0"},
            {"Accept", "application/vnd.github+json"},
        }
    );

    if (apiResponse.status_code != 200) {
        cerr << "Failed to fetch file list from GitHub API. Status: " << apiResponse.status_code << endl;
        cerr << "Response Body: " << apiResponse.text << endl;
        return 1;
    }

    string downloadUrl = "";

    // Gets the url to download by parsing the json from the get
     try {
        auto json_array = json::parse(apiResponse.text);
        for (const auto& item : json_array) {
            string name = item["name"].get<string>();
            
            if (name.size() >= 4 && name.compare(name.size() - 4, 4, ".zip") == 0) {
                downloadUrl = item["download_url"].get<string>(); 
                break;
            }
        }
    } catch (const exception& e) {
        cerr << "Error parsing GitHub API JSON response: " << e.what() << endl;
        return 1;
    }

    if (downloadUrl.empty()) {
        cerr << "No .zip file found in the remote directory." << endl;
        return 1;
    }

    // By default the download url is raw.githubusercontent.com, but it needs media because of git LFS
    downloadUrl.replace(7, 26, "media.githubusercontent.com/media/");

    cout << "Found target file: " << name << endl;

    // Makes sure the games folder exists, if not creates it
    path localPath(name);
    if (localPath.has_parent_path()) {
        create_directories(localPath.parent_path());
    }

    path dir = path(getAppDataPath()) / "PopU27" / "27Launcher";
    create_directories(dir);

    path fullFilePath = dir / name;

    create_directories(fullFilePath.parent_path());

    ofstream file(fullFilePath, ios::binary);
    if (!file.is_open()) {
        cerr << "Failed to create target file at: " << fullFilePath << endl;
        return 1;
    }

    cout << "Downloading update from: " << downloadUrl << endl;
    Response downloadResponse = Get(
        Url{downloadUrl},
        Redirect{true},
        WriteCallback{[&file](const string_view data, intptr_t userdata) -> bool {
            file.write(data.data(), data.size());
            return true;
        }}
    );

    file.close();

    if (downloadResponse.status_code == 200) {
        cout << "Download complete: " << name << endl;
        return 0;
    } else {
        cerr << "Download failed! HTTP Status: " << downloadResponse.status_code << endl;
        remove(fullFilePath.string().c_str());
        return 1;
    }
}