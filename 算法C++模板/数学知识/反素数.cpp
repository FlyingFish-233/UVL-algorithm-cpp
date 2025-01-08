// P1463 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int p[20] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

int n, ans, val;

// 考虑p[x], 当前的数为num, 当前约数个数为cnt, p[x-1]的指数为lim
void dfs(int x, int num, int cnt, int lim)
{
	if (x > 10) {
		if (val < cnt || (val == cnt && num < ans)) val = cnt, ans = num;
		return;
	}
	for (long long i = 0, w = 1; num * w <= n && i <= lim; i++, w *= p[x])
		dfs(x + 1, num * w, cnt * (1 + i), i);
}

int main()
{
	scanf("%d", &n);
	dfs(1, 1, 1, 2e9);
	printf("%d\n", ans);
	return 0;
}