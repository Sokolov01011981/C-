#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>

bool readFile(std::string fileName, std::string *&sRows, int &nCount)
{//считывание строк файла в массив
	std::ifstream ifs;
	std::string str;
	ifs.open(fileName);
	if (ifs.fail()) return false;
	nCount = 0;
	while (std::getline(ifs, str))
		sRows[nCount++] = str;
	ifs.close();
	return true;
}

void sortTextArray(std::string *&words, int &count)
{//сортировка строчного массива
	if (count == 0) return;
	int flag = 1;
	//строки для сортировки
	char *str1 = new char[256];
	char *str2 = new char[256];
	std::string temp;

	//сортировка
	while (flag != 0)
	{
		flag = 0;
		for (int i = 0; i < count - 1; i++){

			strcpy(str1, words[i].c_str());
			strcpy(str2, words[i + 1].c_str());
			//если есть необходимость в сортировке значений объектов
			if (strcmp(_strlwr(str1), _strlwr(str2)) > 0)
			{
				temp = words[i];
				words[i] = words[i + 1];
				words[i + 1] = temp;
				flag++;
			}
		}
	}
	//освобождение динамической памяти
	delete[]str1;
	delete[]str2;
}

void searchCountSames(std::string *a, int &N, std::string fileName)
{//поиск количества вхождений каждого слова в заданном массиве
	struct SAMES {
		int n = 0;
		std::string name;
	};
	SAMES *sames = new SAMES[N];
	int inx, count = 0;
	for (int i = 0; i < N; i++) {
		inx = -1;
		for (int j = 0; j < count; j++) {
			if (a[i] == sames[j].name) {
				inx = j;
				break;
			}
		}//for j

		if (inx == -1) {
			sames[count].name = a[i];
			sames[count++].n++;
		}
		else sames[inx].n++;
	}//for i



	//запись данных из массива в файл 
	std::ofstream ofs;//переменная для вывода данных в файл
	ofs.open(fileName);//открытие файла для записи
	//запись в файл и вывод результата на экран
	for (int i = 0; i < count; i++){
		ofs << sames[i].n << " " << sames[i].name << std::endl;
		std::cout << sames[i].n << " " << sames[i].name << std::endl;
	}
	ofs.close();//закрытие файла
}

int main()
{
	std::string *sWords = new std::string[1000];//динамический массив слов
	int size = 0;
	readFile("file.txt", sWords, size);
	//вывод содержимого файла на экран
	for (int i = 0; i < size; i++){
		std::cout << sWords[i] << std::endl;
	}
	//сортировка массива
	sortTextArray(sWords, size);
	//подсчет количества повторений и вывод результатов на экран
	std::cout << "\n\nAfter sorting...\n";
	searchCountSames(sWords, size, "file_result.txt");

	delete[]sWords;//освобождение памяти массив
	std::cout << std::endl;
	system("pause");
}