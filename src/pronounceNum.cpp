#include"PronounceNum.h"

PronounceNum::PronounceNum()
{
	std::string dig[9] = {"ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};
	digits.assign(dig, dig+9);
	
	std::string tee[9] = {"ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN", "EIGHTEEN", "NINETEEN"};
	teens.assign(tee, tee+9);
	
	std::string ten[9] = {"TEN", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"};
	tens.assign(ten, ten+9);
	
	std::string big[] = {"", "THOUSAND", "MILLION", "BILLION", "TRILLION", "QUADRILLION", "SEXTILLION", "SEPTILLION", "OCTILLION", "NONILLION"};
	int biglen = sizeof(big)/sizeof(std::string);
	bigs.assign(big, big+biglen);
}

PronounceNum::~PronounceNum()
{
}

std::string PronounceNum::numToString(long long num)
{
	if(num == 0) return "ZERO";
	else if(num == LLONG_MIN) return "Minimum Long Long integer!";
	else if(num < 0) return "Negative" + numToString(-1*num);
	
	int count = 0;
	std::string str = "";
	
	while (num > 0)
	{
		if (num % 1000 != 0)
		{
			str = numUnder100(num % 1000) + bigs[count] + " " + str;
		}
		num /= 1000;
		count++;
	}
	return str;
}

std::string PronounceNum::numUnder100(int num)
{
	std::string str = "";
	if (num >= 100)
	{
		str += digits[num/100-1] + " HUNDRED ";
		num %= 100;
	}
	if (num >= 11 && num <= 19)
	{
		return str + teens[num - 11] + " ";
	}
	else if (num == 10 || num >= 20)
	{
		str += tens[num/10 - 1] + " ";
		num %= 10;
	}
	if (num >= 1 && num <= 9)
	{
		str += digits[num - 1] + " ";
	}
	return str;
}
