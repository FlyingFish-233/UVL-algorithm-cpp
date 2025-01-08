// P1177 (60 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

const int NR = 1e5 + 10, MR = 1e8 + 10;

int n;
int a[NR], b[NR];
int cnt[MR];

void countSort()
{
	int a_max = -2e9, a_min = 2e9;
	for (int i = 1; i <= n; i++) a_min = min(a_min, a[i]), a_max = max(a_max, a[i]);
	for (int i = 1; i <= n; i++) cnt[a[i] - a_min]++;
	for (int i = 1; i <= a_max - a_min; i++) cnt[i] += cnt[i - 1];
	for (int i = n; i >= 1; i--) b[cnt[a[i] - a_min]--] = a[i];
	memcpy(a, b, sizeof(b));
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	countSort();
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}
