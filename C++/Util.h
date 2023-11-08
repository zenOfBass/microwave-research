#ifndef UTIL_H
#define UTIL_H

#include <complex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <exception>
#include <time.h>

using namespace std;

complex<double> parseComplex(string s);

const string currentDateTime();
void Log(const string&);


class UnknownFiletype : public exception
{
private:

    string errmsg;

public:

    UnknownFiletype(const string& f) {errmsg = "Unknown filetype  " + f;}

    const char* what() const throw()
    {
        Log(errmsg);
        return errmsg.c_str();
    }
};

class FileOpenError : public exception
{
private:

    string errmsg;

public:

    FileOpenError(const string& f) {errmsg = "Error opening file " + f;}

    const char* what() const throw()
    {
        Log(errmsg);
        return errmsg.c_str();
    }
};

class ImagingDomainParameterError : public exception
{
private:

    string errmsg;

public:

    ImagingDomainParameterError() {errmsg = "Imaging Domain Parameter Error: ";}

    const char* what() const throw()
    {
        Log(errmsg);
        return errmsg.c_str();
    }
};


#endif