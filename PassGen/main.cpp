#include <iostream>
#include <string>
#include "PasswordGenerator.h"

using namespace std;

bool DebugFunc(wstring psw, int minDigitsCount, int maxDigitsCount, int minUnderlinesCount, int maxUnderlinesCount, int minCapitalLettersCount, int maxCapitalLettersCount)
{
	int digs = 0, unders = 0, caps = 0;
	for (int i = 0; i < psw.size(); i++)
	{
		if(iswalpha(psw[i]) && iswupper(psw[i]))
		{
			caps++;
		}
		if(iswdigit(psw[i]))
		{
			digs++;
		}
		if(psw[i] == '_')
		{
			unders++;
		}
	}
	wcout << digs << " " << unders << " " << caps << endl;
	bool res = ((digs <= maxDigitsCount && digs >= minDigitsCount) && (unders <= maxUnderlinesCount && unders >= minUnderlinesCount) && (caps <= maxCapitalLettersCount && caps >= minCapitalLettersCount));
	return res;
}

int main()
{
    srand(time(NULL));
	int c = 200;
	int co = 0;
	GenerationSettings g(200, 200000, 200000, 200000, 200000, 200000, 200000);
    while (c)
    {
		
		wstring someStr = wgenerate_password(g);
		bool gt;
		if(gt = DebugFunc(someStr, g.getMinDigitsCount(), g.getMaxDigitsCount(), g.getMinUnderlinesCount(),
			g.getMaxUnderlinesCount(), g.getMinCapitalLettersCount(), g.getMaxCapitalLettersCount()))
		{
			co++;
		}
		wcout << someStr << " " << gt << " " << "digitsMax: " << g.getMaxDigitsCount() << " digitsMin " << g.getMinDigitsCount() << " underMax " << g.getMaxUnderlinesCount() << " underMin " << g.getMinUnderlinesCount()
			<< " capitalMax " << g.getMaxCapitalLettersCount() << " capitalMin " << g.getMinCapitalLettersCount() << endl;
		c--;
    }
	wcout << co << endl;
}