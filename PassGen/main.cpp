#include <iostream>
#include <string>
#include "PasswordGenerator.h"

using namespace std;

int main()
{
    srand(time(NULL));
	int c = 200;
	GenerationSettings g(200, 200000, 200000, 200000, 200000, 200000, 200000);
    while (c)
    {
		
		wstring someStr = wgenerate_password(g);
		wcout << someStr << " " << "digitsMax: " << g.getMaxDigitsCount() << " digitsMin " << g.getMinDigitsCount() << " underMax " << g.getMaxUnderlinesCount() << " underMin " << g.getMinUnderlinesCount()
			<< " capitalMax " << g.getMaxCapitalLettersCount() << " capitalMin " << g.getMinCapitalLettersCount() << endl;
		c--;
    }
}
