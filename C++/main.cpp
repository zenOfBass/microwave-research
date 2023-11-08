#include "ConfigurationSpace.h"

int main()
{
    Log("Program Start");
    
    ConfigurationSpace c = ConfigurationSpace("config.ini");
    Log("Program End");
    return 0;
}