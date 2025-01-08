// P1706 (100 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

const int NR = 20;

int n;
int a[NR];
bool flag[NR]; // flag[i]表示i这个数字是否在排列中出现

bool permutation()
{
	a[n]++;
	for (int i = n; i >= 1 && a[i] > n; i--)
		a[i] -= n, a[i - 1]++;
	if (a[0] > 0) return false;
	memset(flag, 0, sizeof(flag));
	for (int i = 1; i <= n; i++)
		flag[a[i]] = true;
	bool run_next = false;
	for (int i = 1; i <= n; i++)
		if (!flag[i]) {
			run_next = true;
			break;
		}
	if (!run_next) return true;
	return permutation();
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		a[i] = i;
	do {
		for (int i = 1; i <= n; i++)
			printf("%5d", a[i]);
		printf("\n");
	} while (permutation());
	return 0;
}
