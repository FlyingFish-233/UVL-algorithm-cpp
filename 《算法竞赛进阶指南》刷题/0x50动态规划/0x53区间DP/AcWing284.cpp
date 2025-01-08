# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 310, mod = 1e9;

char s[NR];
int f[NR][NR];

int dfs(int l, int r)
{
	if (l > r || s[l] != s[r]) return 0;
	if (l == r) return 1;
	if (f[l][r] != -1) return f[l][r];
	int ans = 0;
	for (int i = l + 2; i <= r; i++)
		if (s[l] == s[i]) (ans += 1ll * dfs(l + 1, i - 1) * dfs(i, r) % mod) %= mod;
	return f[l][r] = ans;
}

int main()
{
	scanf("%s", s + 1);
	int len = strlen(s + 1);
	memset(f, -1, sizeof(f));
	printf("%d\n", dfs(1, len));
	return 0;
}