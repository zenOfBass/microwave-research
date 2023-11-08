#include "ConfigurationSpace.h"

void ConfigurationSpace::ReadData(const string& antennasFile, const string& channelsFile, const string& frequenciesFile, const string& IQFile)
{
    try
    {
        ReadAntennas(antennasFile);
        ReadChannels(channelsFile);
        ReadFrequencies(frequenciesFile);
        ReadIQ(IQFile);
        Log("Succesfully read input files");
    }
    catch(UnknownFiletype& e){std::cerr << e.what() << '\n';}
    catch(FileOpenError& e){std::cerr << e.what() << '\n';} 
}

void ConfigurationSpace::ReadAntennas(const string& antennasFile)
{
    // CSV file
    if (antennasFile.substr(antennasFile.find_last_of('.')+1, 3) == "csv")
    {
        ifstream fileIn;
        string line;
        char c; // For discarding comma from input stream
        Antenna ant;

        fileIn.open(antennasFile);
        if (!fileIn.fail())
        {
            while(getline(fileIn, line))
            {
                stringstream s(line);
                s >> ant.x >> c >> ant.y >> c >> ant.z;
                antennas.push_back(ant);
            }
            fileIn.close();
        }
        else
        {
            throw FileOpenError(antennasFile);
        }    
    }
    // SQL file
    else if (antennasFile.substr(antennasFile.find_last_of(".") + 1) == "mdf")
    {
        // read sql    
    }
    else{ throw UnknownFiletype(antennasFile.substr(antennasFile.find_last_of('.')+1, 3)); }
}

void ConfigurationSpace::ReadChannels(const string& channelsFile)
{
    // CSV File
    if (channelsFile.substr(channelsFile.find_last_of(".") + 1) == "csv")
    {
        ifstream fileIn;
        string line;
        char c; // For discarding comma from input stream
        int T, R; // Integers for antenna array indices
        Channel channel;


        fileIn.open(channelsFile);
        if (!fileIn.fail())
        {
            while(getline(fileIn, line))
            {
                stringstream s(line);
                s >> T >> c >> R;
                channel.TX = antennas[T-1];
                channel.RX = antennas[R-1];

                channels.push_back(channel);
            }
            fileIn.close();
        }
        else{throw FileOpenError(channelsFile);}
    }
    else if (channelsFile.substr(channelsFile.find_last_of(".") + 1) == "mdf")
    {
        // sql
    }
    else {throw UnknownFiletype(channelsFile);}
    
}

void ConfigurationSpace::ReadFrequencies(const string& frequenciesFile)
{
    // CSV File
    if (frequenciesFile.substr(frequenciesFile.find_last_of(".") + 1) == "csv")
    {
        ifstream fileIn;
        unsigned long int freq;

        fileIn.open(frequenciesFile);
        if (!fileIn.fail())
        {
            while(fileIn >> freq)
            {
                frequencies.push_back(freq);
            }
            fileIn.close();
        }
        else{throw FileOpenError(frequenciesFile);}
    }
    else if (frequenciesFile.substr(frequenciesFile.find_last_of(".") + 1) == "mdf")
    {
        // sql
    }
    else{throw UnknownFiletype(frequenciesFile);}
}

void ConfigurationSpace::ReadIQ(const string& IQFile)
{

    // CSV File
    if (IQFile.substr(IQFile.find_last_of(".") + 1) == "csv")
    {
    ifstream fileIn;
    string line;
    vector<complex<double>> iqLine;
    fileIn.open(IQFile);
    string z;
    if (!fileIn.fail())
    {
        while(getline(fileIn, line))
        {
            stringstream s(line);
            string t;
            while (getline(s, t, ','))
            {
                iqLine.push_back(parseComplex(t));
            }
            iq_data.push_back(iqLine);
            iqLine.clear();
        }
        fileIn.close();
    }
    else{throw FileOpenError(IQFile);}
    }
    else if (IQFile.substr(IQFile.find_last_of(".") + 1) == "mdf")
    {
        // sql
    }
    else {throw UnknownFiletype(IQFile);}

}


void ConfigurationSpace::ReadConfig(const string& configFile)
{
    ifstream fin;
    fin.open(configFile);
    string line;
    string entry;
    vector<string> container;
    float height=0, width=0, depth=0, resolution=0;
    
    while (getline(fin, line))
    {
        if (line[0] != '#') // Ignore comment lines
        {
            istringstream iss(line);
            while (iss >> entry)
            {
                container.push_back(entry);
            }

            if (container.size()!=0)
            {
                if (container[0] == "AntennasFilePath"){this->ReadAntennas(container[2]);}
                else if (container[0] == "ChannelsFilePath"){this->ReadChannels(container[2]);}
                else if (container[0] == "FrequenciesFilePath"){this->ReadFrequencies(container[2]);}
                else if (container[0] == "IQFilePath"){this->ReadIQ(container[2]);}
                else if (container[0] == "height"){height = stof(container[2]);}
                else if (container[0] == "width"){width = stof(container[2]);}
                else if (container[0] == "depth"){depth = stof(container[2]);}
                else if (container[0] == "resolution"){resolution = stof(container[2]);}
                container.clear();
            }

        }
    }

    this->imagingDomain = ImagingDomain(height, width, depth, resolution);
    fin.close();
}


// Constructors

ConfigurationSpace::ConfigurationSpace(){}

ConfigurationSpace::ConfigurationSpace(const string& configFile)
{
    this->ReadConfig(configFile);
}

ConfigurationSpace::ConfigurationSpace(const string& antennasFile, const string& channelsFile, const string& frequenciesFile, const string& IQFile)
{
    ReadData(antennasFile, channelsFile, frequenciesFile, IQFile);
}
