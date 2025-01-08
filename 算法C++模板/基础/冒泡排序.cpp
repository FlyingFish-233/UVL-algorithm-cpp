// P1177 (20 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

const int NR = 100010;

int n;
int a[NR];

void bubbleSort()
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n - i; j++)
			if(a[j] > a[j + 1]) swap(a[j], a[j + 1]);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	bubbleSort();
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}
