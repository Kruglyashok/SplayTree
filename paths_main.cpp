#include <iostream>

#include <algorithm>

using namespace std;

int a[10][10], n, m;

int fact(int n) {

	return (n == 0) || (n == 1) ? 1 : n * fact(n - 1);
}

void printMatr()
{
	cout << "\nmatrix:\n";
	for (auto i{ 0U }; i < n; ++i)
	{
		for (auto j{ 0U }; j < m; ++j)
		{
			cout << a[i][j] << "\t";
		}
		cout << endl;
	}
}

void swap(int* arr, int i, int j)
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}
bool nextSet(int* arr, int num)
{
	int j = num - 2;
	while (j != -1 && arr[j] >= arr[j + 1]) j--;
	if (j == -1)
		return false;
	int k = num - 1;
	while (arr[j] >= arr[k]) k--;
	swap(arr, j, k);
	int l = j + 1, r = num - 1;
	while (l < r)
		swap(arr, l++, r--);
	return true;
}
void Print(int* arr, int num)
{
	static int pNum = 1;
	cout.width(3);
	cout << pNum++ << ": ";
	for (int i = 0; i < num; i++)
		cout << arr[i] << " ";
	cout << endl;
}


int main()
{

	cin >> n >> m;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> a[i][j];
		}
	}
	printMatr();

	//create array of all possible paths, where 1 - move right, 0 - move up
	//we need n-1 0s, m-1 1s
	int* permutations = new int[m - 1 + n - 1];
	for (auto i{ 0U }; i < m - 1 + n - 1; ++i)
	{
		permutations[i] = 0;
	}

	for (auto i{ m - 1 + n - 1 - 1 }; i > (m - 1 + n - 1 - 1) - (m - 1); --i)
	{
		permutations[i] = 1;
	}
	for (auto i{ 0U }; i < m - 1 + n - 1; i++)
	{
		cout << permutations[i] << "\t";
	}
	cout << endl;

	cout << "permutations with repeats: " << fact(m - 1 + n - 1) / (fact(m - 1) * fact(n - 1)) << endl;

	int num = m - 1 + n - 1;

	bool move{ true };
	int minSum = INT32_MAX, curSum = 0;
	int idx{ n - 1 }, jdx{ 0U };
	while (move)
	{
		Print(permutations, num);
		idx = n - 1;
		jdx = 0;
		curSum = 0;
		for (auto i{ 0U }; i < num; ++i)
		{
			if (permutations[i] == 0)
			{
				idx--;
				curSum += a[idx][jdx];
			}
			else
			{
				jdx++;
				curSum += a[idx][jdx];
			}
		}
		if (minSum > curSum)
		{
			minSum = curSum;
		}
		move = nextSet(permutations, num);
	}
	//if (n == 1 && m == 1) cout << "\nminSum = " << a[0][0] << endl;
	//else cout << "\nminSum = " << minSum << endl;

	//for (int i = n; i > 0; i--) a[i - 1][0] += a[i][0];

	//for (int i = 1; i < m; i++) a[n - 1][i] += a[n - 1][i - 1];

	//for (int i = n - 2; i >= 0; i--)

	//	for (int j = 1; j < m; j++) {

	//		a[i][j] += min(a[i][j - 1], a[i + 1][j]);

	//	}

	//cout << "\nmin found :"<<a[0][m - 1] - a[n - 1][0];
	return 0;
}