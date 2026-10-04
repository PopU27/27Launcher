#include "downloadLatestZip.h"
#include "getAppDataPath.h"


int downloadLatestZip(const std::string& apiUrl, const std::string& name)
{   
    // Makes get request to apiUrl
    std::cout << "Checking GitHub for the latest ZIP..." << std::endl;
    cpr::Response apiResponse = cpr::Get(
        cpr::Url{apiUrl},
        cpr::Header{
            {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) 27Launcher/1.0"},
            {"Accept", "application/vnd.github+json"},
        }
    );

    if (apiResponse.status_code != 200) {
        std::cerr << "Failed to fetch file list from GitHub API. Status: " << apiResponse.status_code << std::endl;
        std::cerr << "Response Body: " << apiResponse.text << std::endl;
        return 1;
    }

    std::string downloadUrl = "";

    // Gets the url to download by parsing the json from the get
     try {
        auto json_array = nlohmann::json::parse(apiResponse.text);
        for (const auto& item : json_array) {
            std::string name = item["name"].get<std::string>();
            
            if (name.size() >= 4 && name.compare(name.size() - 4, 4, ".zip") == 0) {
                downloadUrl = item["download_url"].get<std::string>(); 
                break;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error parsing GitHub API JSON response: " << e.what() << std::endl;
        return 1;
    }

    if (downloadUrl.empty()) {
        std::cerr << "No .zip file found in the remote directory." << std::endl;
        return 1;
    }

    // By default the download url is raw.githubusercontent.com, but it needs media because of git LFS
    downloadUrl.replace(7, 26, "media.githubusercontent.com/media/");

    std::cout << "Found target file: " << name << std::endl;

    // Makes sure the games folder exists, if not creates it
    std::filesystem::path localPath(name);
    if (localPath.has_parent_path()) {
        std::filesystem::create_directories(localPath.parent_path());
    }

    std::filesystem::path dir = std::filesystem::path(getAppDataPath()) / "PopU27" / "27Launcher";
    std::filesystem::create_directories(dir);

    std::filesystem::path fullFilePath = dir / name;

    std::filesystem::create_directories(fullFilePath.parent_path());

    std::ofstream file(fullFilePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to create target file at: " << fullFilePath << std::endl;
        return 1;
    }

    std::cout << "Downloading update from: " << downloadUrl << std::endl;
    cpr::Response downloadResponse = cpr::Get(
        cpr::Url{downloadUrl},
        cpr::Redirect{true},
        cpr::WriteCallback{[&file](const std::string_view data, intptr_t userdata) -> bool {
            file.write(data.data(), data.size());
            return true;
        }}
    );

    file.close();

    if (downloadResponse.status_code == 200) {
        std::cout << "Download complete: " << name << std::endl;
        return 0;
    } else {
        std::cerr << "Download failed! HTTP Status: " << downloadResponse.status_code << std::endl;
        std::remove(name.c_str());
        return 1;
    }
}