# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

const int N_MAX = 10010;

int n, m;
int a[NR];
int mid[NR]; // mid[i]表示排列中i这个数后面比i小的数的个数
bool flag[NR]; // flag[i]表示新排列中位置i是否被占用 

bool permutation()
{
	memset(mid, 0, sizeof(mid));
	memset(flag, 0, sizeof(flag));
	for (int i = 1; i <= n - 1; i++)
		for (int j = i + 1; j <= n; j++)
			mid[a[i]] += (a[i] > a[j]);
	mid[n] += m;
	for (int i = n; i >= 2 && mid[i] >= i; i--) {
		mid[i - 1] += mid[i] / i; // 第i为的进位制为i
		mid[i] %= i;
	}
	if (mid[1] > 0) return false;
	for (int i = n; i >= 1; i--) {
		int pos = n;
		for (int j = 0; pos >= 1; pos--) {
			j += !flag[pos];
			if (j > mid[i]) break;
		}
		flag[pos] = true;
		a[pos] = i;
	}
	return true;
}

int main()
{
	scanf("%d", &n);
	scanf("%d", &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	permutation();
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}
