// P1177 (100 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

const int NR = 100010;

int n;
int a[NR];

void down(int x, int len)
{
	for (int dad = x, son = x << 1; son <= len; dad = son, son <<= 1) {
		if (son + 1 <= len && a[son] < a[son + 1]) son++;
		if (a[dad] < a[son]) swap(a[dad], a[son]);
		else break;
	}
}

void heapSort()
{
	for (int i = n / 2; i >= 1; i--)
		down(i, n);
	for (int i = n; i >= 2; i--)
		swap(a[i], a[1]), down(1, i - 1);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	heapSort();
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}
