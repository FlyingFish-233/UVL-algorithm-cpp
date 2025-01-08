// P1177 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

int n;
int a[NR], b[NR];
int cnt[10];

void radixSort()
{
	int T = 10, ten = 1;
	while (T--) {
		memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= n; i++) cnt[a[i] / ten % 10]++;
		for (int i = 1; i <= 9; i++) cnt[i] += cnt[i - 1];
		for (int i = n; i >= 1; i--) b[cnt[a[i] / ten % 10]--] = a[i];
		memcpy(a, b, sizeof(b)), ten *= 10;
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	radixSort();
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}
