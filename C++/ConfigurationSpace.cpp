#include "ConfigurationSpace.h"

void ConfigurationSpace::ReadData(const string& antennasFile, const string& channelsFile, const string& frequenciesFile, vector<string> IQFiles)
{
    try
    {
        ReadAntennas(antennasFile);
        ReadChannels(channelsFile);
        ReadFrequencies(frequenciesFile);
        ReadIQ(IQFiles);
        Log("Succesfully read input files");
    }
    catch(UnknownFiletype& e){std::cerr << e.what() << '\n';}
    catch(FileOpenError& e){std::cerr << e.what() << '\n';} 
}

void ConfigurationSpace::ReadAntennas(const string& antennasFile)
{
    // CSV file
    if (antennasFile.substr(antennasFile.find_last_of(".") + 1) == "csv")
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
    else{ throw UnknownFiletype(antennasFile); }
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

void ConfigurationSpace::ReadIQ(vector<string> IQFiles)
{
    for (int i=0;i<IQFiles.size();i++)
    {
    
        // CSV File
        if (IQFiles[i].substr(IQFiles[i].find_last_of(".") + 1) == "csv")
        {
        ifstream fileIn;
        string line;
        vector<complex<double>> iqLine;
        fileIn.open(IQFiles[i]);
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
        else{throw FileOpenError(IQFiles[i]);}
        }
        else if (IQFiles[i].substr(IQFiles[i].find_last_of(".") + 1) == "mdf")
        {
            // sql
        }
        else {throw UnknownFiletype(IQFiles[i]);}
    }

}


void ConfigurationSpace::ReadConfig()
{
    
}


ConfigurationSpace::ConfigurationSpace(const string& antennasFile, const string& channelsFile, const string& frequenciesFile, vector<string> IQFiles)
{
    ReadData(antennasFile, channelsFile, frequenciesFile, IQFiles);
}

ConfigurationSpace::ConfigurationSpace(Files files)
{
    ReadData(files.AntennasFile, files.ChannelsFile, files.FrequenciesFile, files.IQFiles);
}