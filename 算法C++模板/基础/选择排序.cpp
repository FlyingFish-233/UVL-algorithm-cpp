// P1177 (20 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

const int NR = 100010;

int n;
int a[NR];

void selectSort()
{
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			if (a[i] > a[j]) swap(a[i], a[j]);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	selectSort();
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}
