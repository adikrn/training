
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

bool isUnderDebugger()
{
    bool result = false;

    std::string line;
    std::ifstream file("/proc/self/status");

    while (std::getline(file, line))
    {
        std::istringstream _stream(line);
        std::string tag, value;
        _stream >> tag >> value;
        
        if (tag == "TracerPid:" && value != "0")
            result = true;
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

