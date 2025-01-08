# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 20, MR = (1 << 11) + 10;

int n, m, lim;
bool flag[MR];
long long f[NR][MR];

bool check(int sta)
{
	int now = 0;
	for (int i = 0; i < m; i++) {
		if (sta >> i & 1) {
			if (now & 1) return false;
			now = 0;
		}
		else now++;
	}
	return !(now & 1);
}

long long dfs(int x, int pre)
{
	if (x > n) return pre == 0;
	if (f[x][pre] != -1) return f[x][pre];
	long long ans = 0;
	for (int sta = (lim - pre); sta > 0; sta = (sta - 1) & (lim - pre))
		if (flag[sta | pre]) ans += dfs(x + 1, sta);
	if (flag[pre]) ans += dfs(x + 1, 0);
	return f[x][pre] = ans;
}

int main()
{
	while (scanf("%d%d", &n, &m) && !(n == 0 && m == 0)) {
		lim = (1 << m) - 1;
		for (int sta = 0; sta <= lim; sta++)
			flag[sta] = check(sta);
		memset(f, -1, sizeof(f));
		printf("%lld\n", dfs(1, 0));
	}
	return 0;
}