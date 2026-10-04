#pragma once

#include <nlohmann/json.hpp>
#include <iostream>
#include <cpr/cpr.h>
#include <string>
#include <cstdio>
#include <string_view>
#include <filesystem>

#include <fstream>
#include <shlobj.h>
#include <windows.h>

int downloadLatestZip(const std::string& path, const std::string& name);