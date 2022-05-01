#pragma once
#include <string>
#include <vector>

using namespace std;

template <class T>
T max_element(vector<T>& tVector)
{
	auto max = tVector[0];
	for (int i = 0; i < tVector.size(); i++)
	{
		if (*max < *tVector[i])
		{
			max = tVector[i];
		}
	}
	return max;
}

struct GenerationSettings
{
private:
	int symbolsCount;
	int minDigitsCount;
	int maxDigitsCount;
	int minUnderlinesCount;
	int maxUnderlinesCount;
	int minCapitalLettersCount;
	int maxCapitalLettersCount;
public:
	GenerationSettings();

	GenerationSettings(int symbolsCount, int minDigitsCount, int maxDigitsCount, int minUnderlinesCount, int maxUnderlinesCount, int minCapitalLettersCount, int maxCapitalLettersCount);

	inline int getSymbolsCount() const { return symbolsCount; }

	inline int getMinDigitsCount() const { return minDigitsCount; }
	inline int getMaxDigitsCount() const { return maxDigitsCount; }

	inline int getMinUnderlinesCount() const { return minUnderlinesCount; }
	inline int getMaxUnderlinesCount() const { return maxUnderlinesCount; }

	inline int getMinCapitalLettersCount() const { return minCapitalLettersCount; }
	inline int getMaxCapitalLettersCount() const { return maxCapitalLettersCount; }
};

wstring wgenerate_password(GenerationSettings generationParameters);
string generate_password(GenerationSettings generationParameters);