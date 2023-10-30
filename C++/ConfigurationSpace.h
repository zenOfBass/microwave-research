#ifndef CONFIGURATION_SPACE_H
#define CONFIGURATION_SPACE_H

#include <vector>
#include "Util.h"
#include "ImagingDomain.hpp"

using namespace std;

struct Antenna {float x, y, z;};
struct Channel {Antenna TX, RX;};
struct Files 
{
    const string& AntennasFile; 
    const string& ChannelsFile; 
    const string& FrequenciesFile; 
    vector<string> IQFiles;
};

class ConfigurationSpace
{

private:
vector<Channel> channels;
vector<Antenna> antennas;
vector<unsigned long int> frequencies;
vector<vector<complex<double>>> iq_data;
ImagingDomain imagingDomain;

void ReadData(const string&, const string&, const string&, vector<string> IQFiles);
void ReadAntennas(const string&);
void ReadChannels(const string&);
void ReadFrequencies(const string&);
void ReadIQ(vector<string> IQFiles);

void ReadConfig();


public:
ConfigurationSpace();
ConfigurationSpace(const string&, const string&, const string&, vector<string>);
ConfigurationSpace(Files files);

};

#endif