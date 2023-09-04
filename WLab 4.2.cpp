#include <windows.h> 
#include <iostream> 

using namespace std;

int n;
int** Arr;
int sum = 0;

DWORD WINAPI ThreadWorker(LPVOID arg) {
	int j = *((int*)arg);
	int subsum = 0;
	for (int i = 0; i < n; i++) {
		subsum += Arr[j][i];
	}
	sum += subsum;
	cout << "Сумма элементов "<<j+1<<"-ой строки: " << subsum << endl;
	return 0;
}

int main()
{
	setlocale(0, "russian");
	cout << "Введите размерность матрицы [n*n]: ";
	cin >> n;
	cout << endl;
	Arr = new int* [n];
	for (int i = 0; i < n; i++) {
		Arr[i] = new int[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			Arr[i][j] = rand() % 33;
			cout << Arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	HANDLE* hThread = new HANDLE[n];
	for (int i = 0; i < n; i++) {
		int* N = new int(i);
		hThread[i] = CreateThread(NULL, 0, ThreadWorker, N, 0, NULL);
		Sleep(50);
	}

	WaitForMultipleObjects(n, hThread, TRUE, INFINITE);
	cout << endl;
	cout << "Сумма всех элементов матрицы: " << sum << endl;
	return 0;
}