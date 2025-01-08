// P4127 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int a, b;
int t[20], mod;
long long f[20][100][100][2][2];

// 考虑到第k位, 当前数为r(取模后), 数字和为sum, lim表示已填位的数字是否都为最大, lead表示已填位的数字是否都为0
long long dfs(int k, int r, int sum, bool lim, bool lead)
{
	if (sum > mod) return 0;
	if (k == 0) return r == 0 && sum == mod;
	if (f[k][r][sum][lim][lead] != -1) return f[k][r][sum][lim][lead];
	int up = (lim) ? t[k] : 9;
	long long ans = 0;
	for (int i = 0; i <= up; i++) {
		if (lead && (i == 0)) ans += dfs(k - 1, 0, 0, false, true);
		else ans += dfs(k - 1, (r * 10 + i) % mod, sum + i, lim && (i == t[k]), false);
	}
	return f[k][r][sum][lim][lead] = ans;
}

long long solve(int x)
{
	for (t[0] = 0; x; x /= 10)
		t[++t[0]] = x % 10;
	long long ans = 0;
	for (mod = 1; mod <= t[0] * 9; mod++) {
		memset(f, -1, sizeof(f));
		ans += dfs(t[0], 0, 0, true, true);
	}
	return ans;
}

int main()
{
	scanf("%d%d", &a, &b);
	printf("%lld\n", solve(b) - solve(a - 1));
    return 0;
}