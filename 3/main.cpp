#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
namespace st = std;

#define FILE_PATH "./data.txt"

void readData(st::vector<st::string> &data) {
    st::ifstream f (FILE_PATH);
    st::string lineContent;
    auto index = 0;

    if(f.is_open()) {
        while(f)    {
            st::getline(f, lineContent);
            data.push_back(lineContent);
        }
    }
    else {
        std::cout << "Couldn't open file\n";
    }
    f.close();
}

void findMostCommonBit(st::vector<st::string> &data, st::vector<int> &rate)  {
    for(auto &line: data)   {
        for(auto i = 0; i < line.size(); i++)  {
            char c = line[i];
            if(c == '1') rate[i] += 1;
            else rate[i] -= 1;
        }
    }
    for(auto i = 0; i < rate.size(); i++) {
        if(rate[i] > 0) rate[i] = 1;
        else    rate[i] = 0;
    }
}

int binaryToInteger(st::vector<int> const &binary) {
    auto sum = 0, exp = 11;
    for(auto i = 0; i < binary.size(); i++) {
        sum += binary[i] * pow(2, exp);
        --exp;
    }
    return sum;
}

st::vector<int> findBitInPlace(st::vector<st::string> data, st::vector<int> const &commonBits)    {
    for(auto &bit: commonBits) st::cout << bit;
    st::cout << "\n\n";
    for(auto i = 0; i < commonBits.size(); i++) {
        char cBit;
        if(commonBits[i] == 1) cBit = '1';
        else cBit = '0';
        for(auto j = 0; j < data.size(); j++)   {
            char dBit = data[j][i];
            if(dBit != cBit) {
                data.erase(data.begin() + j);
            }
        }
        if(data.size() == 1) break;
    }

    for(auto &line: data) {
        st::cout << line << st::endl;
    }

    st::vector<int> v(12, 0);
    for(auto i = 0; i < data[0].size(); i++)    {
        if(data[0][i] == '0') v[i] = 0;
        else    v[i] = 1;
    }
    return v;
}

int main()  {
    st::vector<st::string> data;
    readData(data);

    st::vector<int> gammaRate(12, 0);
    findMostCommonBit(data, gammaRate);
    
    st::vector<int> epsilonRate(12, 0);
    for(auto i = 0; i < gammaRate.size(); i++)   {
        epsilonRate[i] = !gammaRate[i];
    }

    int powerOutput = binaryToInteger(gammaRate) * binaryToInteger(epsilonRate);
    // st::cout << "powerOutput= " << powerOutput << st::endl;

    auto oxyGenRating = binaryToInteger(findBitInPlace(data, gammaRate));
    // auto co2ScrubRating = binaryToInteger(findBitInPlace(data, epsilonRate));
    // auto lifeSuppRating = oxyGenRating * co2ScrubRating;
    // st::cout << lifeSuppRating;

    return 0;
}