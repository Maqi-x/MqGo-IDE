#include <Utils/Types.hpp>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

string GetPath(const string &tool) {
#ifdef _WIN32
    string cmd = "where " + tool + " 2>NUL";
#else
    string cmd = "which " + tool + " 2>/dev/null";
#endif

    FILE *pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        throw SysError("Failed to run command (" + tool + ")");
    }

    char buf[128];
    std::string result;
    if (fgets(buf, sizeof(buf), pipe)) {
        result = buf;
    }
    pclose(pipe);

    if (result.empty()) {
        throw SysError(tool + " is not installed or not in $PATH");
    }

    result.erase(result.find_last_not_of(" \n\r\t") + 1);
    return result;
}