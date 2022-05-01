#include  "PasswordGenerator.h"

using namespace std;

GenerationSettings::GenerationSettings()
{
	this->symbolsCount = 5;

	this->minDigitsCount = 0;
	this->maxDigitsCount = 0;

	this->minUnderlinesCount = 0;
	this->maxUnderlinesCount = 0;

	this->minCapitalLettersCount = 0;
	this->maxCapitalLettersCount = 0;
}

GenerationSettings::GenerationSettings(int symbolsCount, int minDigitsCount, int maxDigitsCount, int minUnderlinesCount, int maxUnderlinesCount, int minCapitalLettersCount, int maxCapitalLettersCount)
{
	vector<int*> min = { &minDigitsCount, &minUnderlinesCount, &minCapitalLettersCount };
	vector<int*> max = { &maxDigitsCount, &maxUnderlinesCount, &maxCapitalLettersCount };

	while ((maxDigitsCount + maxUnderlinesCount + maxCapitalLettersCount) > symbolsCount)
	{
		auto smallestMaxOption = max_element(max);
		(*smallestMaxOption)--; //уменьшаем наибольший элемент, т.к. он превышает symbolsCount. ”меньшение до момента, пока суммы максимумов не сравн€ютс€ или не будут меньше symbolsCount
	}
	while ((minDigitsCount + minUnderlinesCount + minCapitalLettersCount) > symbolsCount)
	{
		auto smallestMinOption = max_element(min);
		(*smallestMinOption)--; //уменьшаем наименьший элемент, если он превышает symbolsCount.
	}
	if (minDigitsCount > maxDigitsCount) { minDigitsCount = maxDigitsCount; }
	if (minUnderlinesCount > maxUnderlinesCount) { minUnderlinesCount = maxUnderlinesCount; }
	if (minCapitalLettersCount > maxCapitalLettersCount) { minCapitalLettersCount = maxCapitalLettersCount; }

	if (minDigitsCount < 0) { minDigitsCount = 0; }
	if (minUnderlinesCount < 0) { minUnderlinesCount = 0; }
	if (minCapitalLettersCount < 0) { minCapitalLettersCount = 0; }

	if (maxDigitsCount < 0) { maxDigitsCount = 0; }
	if (maxUnderlinesCount < 0) { maxUnderlinesCount = 0; }
	if (maxCapitalLettersCount < 0) { maxCapitalLettersCount = 0; }

	if (symbolsCount < 0) { symbolsCount = 5; }

	this->symbolsCount = symbolsCount;

	this->minDigitsCount = minDigitsCount;
	this->maxDigitsCount = maxDigitsCount;

	this->minUnderlinesCount = minUnderlinesCount;
	this->maxUnderlinesCount = maxUnderlinesCount;

	this->minCapitalLettersCount = minCapitalLettersCount;
	this->maxCapitalLettersCount = maxCapitalLettersCount;
}

wstring wgenerate_password(GenerationSettings generationParameters)
{
	const int symbolsCount = generationParameters.getSymbolsCount();

	int maxUnderlinesCount = generationParameters.getMaxUnderlinesCount();
	int maxCapitalLettersCount = generationParameters.getMaxCapitalLettersCount();
	int maxDigitsCount = generationParameters.getMaxDigitsCount();

	int minUnderlinesCount = generationParameters.getMinUnderlinesCount();
	int minCapitalLettersCount = generationParameters.getMinCapitalLettersCount();
	int minDigitsCount = generationParameters.getMinDigitsCount();

	wchar_t* password = new wchar_t[generationParameters.getSymbolsCount()];

	for (int i = 0; i < symbolsCount;)
	{
		int random = 1 + rand() % (3 - 1 + 1); //случайный выбор символа

		if (random == 1 && maxUnderlinesCount > 0)
		{
			password[i] = L'_';
			maxUnderlinesCount--; minUnderlinesCount--;
			i++;
		}
		if (random == 2 && maxDigitsCount > 0)
		{
			int randomDigit = 48 + rand() % (57 - 48 + 1); //цифра
			if (password[i - 1] == randomDigit) continue;
			password[i] = randomDigit;
			maxDigitsCount--; minDigitsCount--;
			i++;
		}
		if (random == 3)
		{
			int letterChoise = 1 + rand() % (2 - 1 + 1);

			if (letterChoise == 2 && maxCapitalLettersCount > 0)
			{
				wchar_t randomLetter = 65 + rand() % (90 - 65 + 1); //больша€ буква
				password[i] = randomLetter;
				maxCapitalLettersCount--; minCapitalLettersCount--;
				i++;
			}

		}
		else
		{
			password[i] = 97 + rand() % (122 - 97 + 1); //маленька€ буква
			i++;
		}
	}
	//Ётот цикл добавл€ет несгенерированные символы (число, _, больша€ буква) за счет маленьких букв
	for (int i = 0; i < symbolsCount; i++)
	{
		int random = 1 + rand() % (3 - 1 + 1);

		if (iswalpha(password[i]) && iswlower(password[i]))
		{
			if ((random == 1 && maxUnderlinesCount > 0 || minUnderlinesCount > 0))
			{
				password[i] = '_';
				maxUnderlinesCount--; minUnderlinesCount--;
			}
			else if (random == 2 && maxDigitsCount > 0 || minDigitsCount > 0)
			{
				int randomDigit = 48 + rand() % (57 - 48 + 1); //выбор цифры по Unicode
				password[i] = randomDigit;
				maxDigitsCount--; minDigitsCount--;

			}
			else if (random == 3 && maxCapitalLettersCount > 0 || minCapitalLettersCount > 0)
			{
				wchar_t randomLetter = 65 + rand() % (90 - 65 + 1); //выбор большой буквы по Unicode
				password[i] = randomLetter;
				maxCapitalLettersCount--; minCapitalLettersCount--;
			}
		}
	}
	password[symbolsCount] = '\0';
	return wstring{ password };
}

string generate_password(GenerationSettings generationParameters)
{
	const int symbolsCount = generationParameters.getSymbolsCount();

	int maxUnderlinesCount = generationParameters.getMaxUnderlinesCount();
	int maxCapitalLettersCount = generationParameters.getMaxCapitalLettersCount();
	int maxDigitsCount = generationParameters.getMaxDigitsCount();

	int minUnderlinesCount = generationParameters.getMinUnderlinesCount();
	int minCapitalLettersCount = generationParameters.getMinCapitalLettersCount();
	int minDigitsCount = generationParameters.getMinDigitsCount();

	char* password = new char[generationParameters.getSymbolsCount()];

	for (int i = 0; i < symbolsCount;)
	{
		int random = 1 + rand() % (3 - 1 + 1); //случайный выбор символа

		if (random == 1 && maxUnderlinesCount > 0)
		{
			password[i] = L'_';
			maxUnderlinesCount--; minUnderlinesCount--;
			i++;
		}
		if (random == 2 && maxDigitsCount > 0)
		{
			int randomDigit = 48 + rand() % (57 - 48 + 1); //цифра
			if (password[i - 1] == randomDigit) continue;
			password[i] = randomDigit;
			maxDigitsCount--; minDigitsCount--;
			i++;
		}
		if (random == 3)
		{
			int letterChoise = 1 + rand() % (2 - 1 + 1);

			if (letterChoise == 2 && maxCapitalLettersCount > 0)
			{
				char randomLetter = 65 + rand() % (90 - 65 + 1); //больша€ буква
				password[i] = randomLetter;
				maxCapitalLettersCount--; minCapitalLettersCount--;
				i++;
			}

		}
		else
		{
			password[i] = 97 + rand() % (122 - 97 + 1); //маленька€ буква
			i++;
		}
	}
	//Ётот цикл добавл€ет несгенерированные символы (число, _, больша€ буква) за счет маленьких букв
	for (int i = 0; i < symbolsCount; i++)
	{
		int random = 1 + rand() % (3 - 1 + 1);

		if (isalpha(password[i]) && islower(password[i]))
		{
			if ((random == 1 && maxUnderlinesCount > 0 || minUnderlinesCount > 0))
			{
				password[i] = '_';
				maxUnderlinesCount--; minUnderlinesCount--;
			}
			else if (random == 2 && maxDigitsCount > 0 || minDigitsCount > 0)
			{
				int randomDigit = 48 + rand() % (57 - 48 + 1); //выбор цифры по ASCII
				password[i] = randomDigit;
				maxDigitsCount--; minDigitsCount--;

			}
			else if (random == 3 && maxCapitalLettersCount > 0 || minCapitalLettersCount > 0)
			{
				char randomLetter = 65 + rand() % (90 - 65 + 1); //выбор большой буквы по ASCII
				password[i] = randomLetter;
				maxCapitalLettersCount--; minCapitalLettersCount--;
			}
		}
	}
	password[symbolsCount] = '\0';
	return string();
}

