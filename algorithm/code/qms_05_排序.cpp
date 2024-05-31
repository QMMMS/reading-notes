#include<iostream>
#include<cstring>
#include<queue>
using namespace std;


const int N = 10;
int VALS[N] = { 34,1,4,0,73,34,87,45,111,14 };
int vals[N];
int turnNum;


template<class T>
void PrintArray(T Data[], int n) {
	cout << "µÚ" << ++turnNum << "ÌË" << " : ";
	for (int i = 0; i != n; i++) cout << Data[i] << " ";
	cout << endl;
}

template<class T>
void InsertSort(T Data[], int n) {
	for (int p = 1; p < n; ++p) {
		T temp = Data[p];
		int i = p - 1;
		while (i >= 0 && Data[i] > temp) {
			Data[i + 1] = Data[i];
			i--;
		}
		Data[i + 1] = temp;
		PrintArray(Data, n);
	}
}

template<class T>
void BinaryInsertSort(T Data[], int n) {
	for (int p = 1; p < n; ++p) {
		T temp = Data[p];
		int left = 0, right = p - 1;
		while (left <= right) {
			int mid = (left + right) / 2;
			if (Data[mid] > temp)right = mid - 1;
			else left = mid + 1;
		}
		for (int i = p - 1; i >= left; i--)Data[i + 1] = Data[i];
		Data[left] = temp;
		PrintArray(Data, n);
	}
}

template<class T>
void ShellSort(T Data[], int n) {
	int d = n / 2;
	while (d >= 1) {
		for (int k = 0; k < d; ++k) {
			for (int i = k + d; i < n; i += d) {
				T temp = Data[i];
				int j = i - d;
				while (j >= k && Data[j] > temp) {
					Data[j + d] = Data[j];
					j -= d;
				}
				Data[j + d] = temp;
			}
		}
		d = d / 2;
		PrintArray(Data, n);
	}
}

template<class T>
void Swap(T& a, T& b) {
	T t = a;
	a = b;
	b = t;
}

template<class T>
void BubbleSort(T Data[], int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 1; j < n - i; ++j) {
			if (Data[j] < Data[j - 1]) Swap(Data[j], Data[j - 1]);
		}
		PrintArray(Data, n);
	}
}

template<class T>
void SiftDown(T Data[], int i, int n) {
	while (2 * i + 1 < n) {
		int maxChild = 2 * i + 1;
		if (2 * i + 2 < n && Data[2 * i + 2] > Data[2 * i + 1]) maxChild = 2 * i + 2;
		if (Data[maxChild] > Data[i]) {
			Swap(Data[maxChild], Data[i]);
			i = maxChild;
		}
		else return;
	}
}

template<class T>
void HeapSort(T Data[], int n) {
	for (int i = n - 1; i >= 0; i--) SiftDown(Data, i, n);
	for (int i = n - 1; i > 0; i--) {
		Swap(Data[0], Data[i]);
		SiftDown(Data, 0, i);
		PrintArray(Data, n);
	}
}

template<class T>
void SelectionSort(T Data[], int n) {
	for (int i = 0; i < n - 1; ++i) {
		int k = i;
		for (int j = i + 1; j < n; ++j) if (Data[j] < Data[k])k = j;
		Swap(Data[i], Data[k]);
		PrintArray(Data, n);
	}
}

template<class T>
int Partition(T Data[], int left, int right) {
	int start = left;
	T pivot = Data[left];
	while (left <= right) {
		while (left <= right && Data[left] <= pivot)left++;
		while (left <= right && Data[right] > pivot)right--;
		if (left < right) {
			swap(Data[right], Data[left]);
			left++;
			right--;
		}
	}
	swap(Data[start], Data[right]);
	return right;
}

template<class T>
void QuickSort(T Data[], int left, int right) {
	if (left < right) {
		int p = Partition(Data, left, right);
		cout << "Partition " << left << " " << right << " ";
		PrintArray(Data, N);
		QuickSort(Data, left, p - 1);
		QuickSort(Data, p + 1, right);
	}
}

template<class T>
void Merge(T Data[], T Temp[], int start, int mid, int end) {
	for (int i = start; i <= end; ++i)Temp[i] = Data[i];
	int i = start, j = mid + 1, k = start;
	while (i <= mid && j <= end) {
		if (Temp[i] <= Temp[j])Data[k++] = Temp[i++];
		else Data[k++] = Temp[j++];
	}
	while (i <= mid)Data[k++] = Temp[i++];
	while (j <= end)Data[k++] = Temp[j++];
}


template<class T>
void MergeSort(T Data[], T Temp[], int start, int end) {
	if (start < end) {
		int mid = (start + end) / 2;
		MergeSort(Data, Temp, start, mid);
		MergeSort(Data, Temp, mid + 1, end);
		Merge(Data, Temp, start, mid, end);
		cout << "Merge " << start << " " << mid << " " << end << " ";
		PrintArray(Data, N);
	}
}

const int RADIX = 10;
template<class T>
void Distribute(T Data[], queue<T> queues[], int n, int ith) {
	for (int i = 0; i < n; ++i) {
		T v = Data[i];
		int j = ith - 1;
		while (j--)v /= RADIX;
		v %= RADIX;
		queues[v].push(Data[i]);
	}
}

template<class T>
void Collect(T Data[], queue<T> queues[]) {
	int index = 0;
	for (int i = 0; i < RADIX; ++i) {
		while (!queues[i].empty()) {
			Data[index++] = queues[i].front();
			queues[i].pop();
		}
	}
}

template<class T>
void RadixSort(T Data[], int n, int keys) {
	queue<T> queues[RADIX];
	for (int i = 0; i < keys; i++)	{
		Distribute(Data, queues, n, i + 1);
		Collect(Data, queues);
		PrintArray(Data, n);
	}
}

int main() {
	for (int i = 0; i != N; i++) cout << VALS[i] << " ";
	cout << endl << endl;

	memcpy(vals, VALS, sizeof(VALS));
	turnNum = 0;
	cout << "Ö±½Ó²åÈëÅÅÐò£º" << endl;
	InsertSort(vals, N);
	cout << endl << endl;

	memcpy(vals, VALS, sizeof(VALS));
	turnNum = 0;
	cout << "ÕÛ°ë²åÈëÅÅÐò£º" << endl;
	BinaryInsertSort(vals, N);
	cout << endl << endl;

	memcpy(vals, VALS, sizeof(VALS));
	turnNum = 0;
	cout << "Ï£¶ûÅÅÐò£º" << endl;
	ShellSort(vals, N);
	cout << endl << endl;

	memcpy(vals, VALS, sizeof(VALS));
	turnNum = 0;
	cout << "Ã°ÅÝÅÅÐò£º" << endl;
	BubbleSort(vals, N);
	cout << endl << endl;

	memcpy(vals, VALS, sizeof(VALS));
	turnNum = 0;
	cout << "¶ÑÅÅÐò£º" << endl;
	HeapSort(vals, N);
	cout << endl << endl;

	memcpy(vals, VALS, sizeof(VALS));
	turnNum = 0;
	cout << "Ö±½ÓÑ¡ÔñÅÅÐò£º" << endl;
	SelectionSort(vals, N);
	cout << endl << endl;

	memcpy(vals, VALS, sizeof(VALS));
	turnNum = 0;
	cout << "¿ìËÙÅÅÐò£º" << endl;
	QuickSort(vals, 0, N - 1);
	cout << endl << endl;

	memcpy(vals, VALS, sizeof(VALS));
	turnNum = 0;
	int TEMP[N];
	cout << "¹é²¢ÅÅÐò£º" << endl;
	MergeSort(vals, TEMP, 0, N - 1);
	cout << endl << endl;

	memcpy(vals, VALS, sizeof(VALS));
	turnNum = 0;
	cout << "»ùÊýÅÅÐò£º" << endl;
	RadixSort(vals, N, 3);
	cout << endl << endl;

	return 0;
}