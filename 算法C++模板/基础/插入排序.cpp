// P1177 (60 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

const int NR = 100010;

int n;
int a[NR];

void insertionSort()
{
	for (int i = 1; i <= n; i++)
		for (int j = i - 1; j >= 1 && a[j] > a[j + 1]; j--)
			swap(a[j], a[j + 1]);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	insertionSort();
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}
