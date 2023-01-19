
#include <iostream>
#include <unistd.h>
#include <vector>

bool isBreakpointPresent(const unsigned char *func, const std::vector<unsigned int>& offsets)
{
    bool result = false;

    for (auto &i : offsets) {
        if (*(func + i) == 0xCC)
        {
            result = true;
            break;
        }
    }

    return result;
}

void secret()
{
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Try a breakpoint at secret()" << std::endl;
    }
}

int main()
{
    auto *ptr_secret = (unsigned char*)secret;

    std::vector<unsigned int> offsets = {0, 1, 4, 8, 15, 19, 21, 28, 35, 40, 43, 50, 53, 56, 61, 65, 67, 68, 69};

    if (isBreakpointPresent(ptr_secret, offsets))
        std::cerr << "Breakpoint detected" << std::endl;
    else
        secret();
    return 0;
}


