// P1177 (60 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

const int NR = 1e5 + 10, MR= 1e8 + 10;

int n;
int a[NR];
int nest[MR];

void pigeonSort()
{
	int a_max = -2e9, a_min = 2e9;
	for (int i = 1; i <= n; i++) a_max = max(a[i], a_max), a_min = min(a[i], a_min);
	for (int i = 1; i <= n; i++) nest[a[i] - a_min]++;
	int now = 0;
	for (int i = a_min; i <= a_max; i++)
		while (nest[i - a_min]--) a[++now] = i;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	pigeonSort();
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}