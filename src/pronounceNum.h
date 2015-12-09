#ifndef _PronounceNum_
#define _PronounceNum_

#include<string>
#include<vector>

class PronounceNum
{
public:
	PronounceNum();
	~PronounceNum();
	
	std::vector<std::string> digits;
	std::vector<std::string> teens;
	std::vector<std::string> tens;
	std::vector<std::string> bigs;
	
	std::string numToString(long long num);
    std::string numUnder100(int num);
};

#endif
