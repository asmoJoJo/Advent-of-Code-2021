#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <math.h>
namespace st = std;

#define FILE_PATH "./data.txt"

void readData(st::list<st::string> &data) {
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

void findMostCommonBit(st::list<st::string> &data, st::vector<int> &rate)  {
    auto it = data.begin();
    for(it; it != data.end(); ++it) {
        auto binary = *it;
        for(auto j = 0; j < binary.length(); ++j)    {
            auto bit = binary[j];
            if(bit == '1')  rate[j] += 1;
            else    rate[j] -= 1;
        }
    }
    for(auto i = 0; i < rate.size(); i++) {
        if(rate[i] > 0) rate[i] = 1;
        else    rate[i] = 0;
    }
}

int binaryToInteger(st::vector<int> const &binary) {
    auto sum = 0;
    auto exp = binary.size() - 1;
    for(auto i = 0; i < binary.size(); i++) {
        sum += binary[i] * pow(2, exp);
        --exp;
    }
    return sum;
}

int binaryToInteger(st::string const &binary) {
    auto sum = 0;
    auto exp = binary.size() - 1;
    for(auto i = 0; i < binary.size(); i++) {
        auto bit = (int)binary[i] - 48;                 // 48 = OFFSET for converting char to corresponding int
        sum += bit * pow(2, exp);
        --exp;
    }
    return sum;
}

st::string findMostSimilarNumber(st::list<st::string> data, st::vector<int> const &commonBits)    {
    for(auto i = 0; i < commonBits.size(); i++) {
        char cBit;
        if(commonBits[i] == 1) cBit = '1';
        else cBit = '0';
        auto it = data.begin();
        for(it; it != data.end(); ++it) {
            auto binary = *it;
            auto dBit = binary[i];
            if(dBit != cBit) {
                it = data.erase(it);
                --it;
            }
        }
        if(data.size() == 1) break;
    }
    return *data.begin();
}

int main()  {
    st::list<st::string> data;
    readData(data);

    st::vector<int> gammaRate(12, 0);
    findMostCommonBit(data, gammaRate);
    
    st::vector<int> epsilonRate(12, 0);
    for(auto i = 0; i < gammaRate.size(); i++)   {
        epsilonRate[i] = !gammaRate[i];
    }

    // int powerOutput = binaryToInteger(gammaRate) * binaryToInteger(epsilonRate);         //  uncomment to find out
    // st::cout << "powerOutput= " << powerOutput << st::endl;                              //  answer to part 1

    auto oxyGenRating = binaryToInteger(findMostSimilarNumber(data, gammaRate));
    auto co2ScrubRating = binaryToInteger(findMostSimilarNumber(data, epsilonRate));

    auto lifeSuppRating = oxyGenRating * co2ScrubRating;
    st::cout << lifeSuppRating;

    return 0;
}