#include "ConfigurationSpace.h"

int main()
{
    Log("Program Start");
    vector<string> IQFiles;
    IQFiles.push_back("files\\0000_EmptyField_2.0-6.0_1000_8_0.csv");

    ConfigurationSpace c = ConfigurationSpace("files\\antenna_locations_cylinder.csv", "files\\channel_names.csv", "files\\frequencies_1.4-3.2.csv", IQFiles);
    Log("Program End");
    return 0;
}