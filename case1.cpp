
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <linux/limits.h>
#include <unistd.h>

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

bool isUnderDebugger()
{
    bool result = false;
    /*
     * /proc/self/stat has PID of parent process as fourth parameter.
     */
    std::string stat;
    std::ifstream file("/proc/self/stat");

    for(int i = 0; i < 4; ++i)
        file >> stat;

    std::string parent_path = std::string("/proc/") + stat + "/exe";
    char path[PATH_MAX + 1];
    memset(path, 0, PATH_MAX + 1);
    readlink(parent_path.c_str(), path, PATH_MAX);

    std::vector<std::string> debuggers = {"gdb", "lldb-server"};

    for (auto &p: debuggers)
    {
        if (hasEnding(std::string(path), p))
        {
            result = true;
            break;
        }
    }

    return result;
}

int main() {
    if (isUnderDebugger())
        std::cout << "I am being debugged." << std::endl;
    else
        std::cout << "I am not being debugged" << std::endl;
    return 0;
}

