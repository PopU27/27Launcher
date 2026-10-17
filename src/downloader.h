#pragma once

#include <nlohmann/json.hpp>
#include <iostream>
#include <cpr/cpr.h>
#include <string>
#include <cstdio>

#include <filesystem>

#include <fstream>

#include <functional>

int downloadAppUpdate(const std::string& url, const std::string& dir,
                std::function<void(size_t, size_t)> progressCallback);


int downloadLatestZip(const std::string& path, const std::string& name,
                    std::function<void(size_t, size_t)> progressCallback = nullptr);