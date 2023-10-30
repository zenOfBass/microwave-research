#include "Util.h"

complex<double> parseComplex(string s)
{
    double re, im;
    char i, c;
    stringstream stream(s);
    stream >> setprecision(numeric_limits<double>::digits10) >> re >> im >> i >> c;
    return complex<double>(re, im);
}

void Log(const string& m)
{
    ofstream fout;
    fout.open("log.txt",ios::app);
    fout << "[" << currentDateTime() << "] " << m << endl;
    fout.close();

}

const string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}