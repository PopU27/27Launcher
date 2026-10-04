#pragma once

#include <nlohmann/json.hpp>
#include <iostream>
#include <cpr/cpr.h>
#include <string>
#include <cstdio>

#include <filesystem>

#include <fstream>


int downloadLatestZip(const std::string& path, const std::string& name);