#include "Logger.h"

int main(int argc, char const *argv[])
{
    Logger a;
    a.newLog("its a proccess log!");
    a.newWarning("its a warning log!");
    a.newError("its an Error log!");
    return 0;
}
