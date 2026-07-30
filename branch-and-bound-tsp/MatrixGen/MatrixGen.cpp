#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void main()
{
	setlocale(LC_ALL, "RUS");
	const string path = "C:\\Users\\Bernkastel\\Desktop\\Спидозные козявки\\КодОсапрррррРРРРрРрРРР\\бляя\\Курсовая\\Курсовая\\MyFile.txt";

	ofstream fout(path, ios::out);

	if (!fout.is_open())
	{
		cout << "Файл не открыт." << endl;
	}
	else
	{
		cout << "Введите число N - оно показывает количество вершин в одном из множеств " << endl;
		int N;

		cin >> N;

		fout << N << "\n";
		cout << "Если вы хотите заполнить матрицу сами нажмите: C \n";
		cout << "Если вы хотите заполнить матрицу рандомно нажмите: N \n";
		cout << "Если вы хотите выйти нажмите: E \n";
		string choice;
		do {
			cin >> choice;
			if (choice == "C") {
				cout << "Заполнение матрицы самостоятельно:\n";
				int num;
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < N; j++) {
						cin >> num;
						fout << num << " ";
					}
					fout << "\n";
				}
				break;
			}
			else if (choice == "N") {
				cout << "Заполнение матрицы рандомно:\n";
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < N; j++) {
						fout << rand() % (50 - 1 + 1) + 1 << " ";
					}
					fout << "\n";
				}
				break;
			}
			else if (choice != "E") {
				cout << "Введен некоретный симв" << endl;
			}
		} while (choice != "E");
	}

	fout.close();
}
