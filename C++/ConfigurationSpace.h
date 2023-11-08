#ifndef CONFIGURATION_SPACE_H
#define CONFIGURATION_SPACE_H

#include <vector>
#include "Util.h"
#include "ImagingDomain.hpp"

using namespace std;

struct Antenna {float x, y, z;};
struct Channel {Antenna TX, RX;};

class ConfigurationSpace
{

private:

void ReadData(const string&, const string&, const string&, const string&);
void ReadAntennas(const string&);
void ReadChannels(const string&);
void ReadFrequencies(const string&);
void ReadIQ(const string&);

public:
vector<Channel> channels;
vector<Antenna> antennas;
vector<unsigned long int> frequencies;
vector<vector<complex<double>>> iq_data;
ImagingDomain imagingDomain;

void ReadConfig(const string&);
ConfigurationSpace();
ConfigurationSpace(const string&);
ConfigurationSpace(const string&, const string&, const string&, const string&);

};

#endif