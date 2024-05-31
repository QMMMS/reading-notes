# 排序

> 参考：[十大经典排序算法（动图演示） ](https://www.cnblogs.com/onepixel/p/7674659.html)

对同一个顺序表使用不同的排序方法进行排序,得到的排序结果可能不同（稳定和不稳定）

对于 $n$ 个元素使用 $m$ 路做归并排序，所需趟数为 $\lceil log_mn \rceil$

将两个各有$n$个元素的有序表归并成一个有序表，最少比较$n$次，最多比较$2n-1$次。

```
1 2 3 4 5 和 6 7 8 9 10 需要比较5次
1 3 5 7 9 和 2 4 6 8 10 需要比较9次
```

## 游戏规则和遍历代码

```cpp
const int N = 10;
int VALS[N] = { 34,1,4,0,73,34,87,45,111,14 };
int vals[N];


int turnNum;
template<class T>
void PrintArray(T Data[], int n) {
	cout << "第" << ++turnNum << "趟" << " : ";
	for (int i = 0; i != n; i++) cout << Data[i] << " ";
	cout << endl;
}

//void xxSort(...){}

int main() {
	for (int i = 0; i != N; i++) cout << VALS[i] << " ";
	cout << endl << endl;

	memcpy(vals, VALS, sizeof(VALS));
	turnNum = 0;
	cout << "xx排序：" << endl;
	xxSort(...);
	cout << endl << endl;
    
    return 0;
}
```

![](./pic/sort.png)

## 直接插入排序

保持前面的序列有序，每次把当前元素插入前面的有序序列中。

```cpp
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
```

## 折半插入排序

保持前面的序列有序，每次把当前元素插入前面的有序序列中。

因为前面的序列有序，所以可以用二分。但是空位仍然需要一个一个移动，时间复杂度在数量级上没有改变。

```cpp
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
```

## 希尔排序

希尔排序保持每隔$d$个元素有序，$d$由大到小变化，当$d$为1并且排完时就排好了。

```cpp
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
```

>   以上三种排序都属于插入排序，特点是需要把位置一个一个挪出来。

## 冒泡排序

对于当前元素对，前后顺序反了就调换，再进行下一对，做$n$轮。（如果某一轮没调换可以提前结束）

```cpp
template<class T>
void BubbleSort(T Data[], int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 1; j < n - i; ++j) {
			if (Data[j] < Data[j - 1]) Swap(Data[j], Data[j - 1]);
		}
		PrintArray(Data, n);
	}
}
```

## 快速排序

快速排序使用递归分割序列，对每一个序列，使用 Partition 操作，即把比轴小的元素分到轴左边，大的分右边。再递归。*最坏*情况下，是整个序列都已经有序且完全倒序 ，此时，*快速排序*退化为冒泡排序，要*比较*n*（n-1）/2次才能完成

```cpp
template<class T>
int Partition(T Data[], int left, int right) {
	int start = left;
	T pivot = Data[left];//第一个元素为轴
	while (left <= right) {
		while (left <= right && Data[left] <= pivot)left++;//在左边找到比轴大的
		while (left <= right && Data[right] > pivot)right--;//在右边找到比轴小的
		if (left < right) {
			swap(Data[right], Data[left]);//交换左右
			left++;
			right--;
		}
	}
	swap(Data[start], Data[right]);//再与轴元素交换
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
```

>   以上两种排序都属于交换排序，特点是需要元素交换 Swap 操作
>
>   ```cpp
>   template<class T>
>   void Swap(T& a, T& b) {
>   	T t = a;
>   	a = b;
>   	b = t;
>   }
>   ```

## 直接选择排序

每次选择最小的放前面。

```cpp
template<class T>
void SelectionSort(T Data[], int n) {
	for (int i = 0; i < n - 1; ++i) {
		int k = i;
		for (int j = i + 1; j < n; ++j) if (Data[j] < Data[k])k = j;
		Swap(Data[i], Data[k]);
		PrintArray(Data, n);
	}
}
```

## 堆排序

```cpp
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
```

## 归并排序

将两个有序子数组归并为有序的完整数组

```cpp
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
```

## 基数排序

```cpp
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
```