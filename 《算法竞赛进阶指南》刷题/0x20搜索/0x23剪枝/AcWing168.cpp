# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 100;

int n, m, ans = 2e9;
int s_min[NR], v_min[NR];

void dfs(int x, int s, int v, int r0, int h0)
{
	if (s + s_min[x] >= ans) return;
	if (v + v_min[x] > n) return;
	if (v + 1ll * r0 * r0 * h0 * x < n) return;
	if (x == 0) { 
		if (v == n) ans = s;
		return;
	}
	for (int r = r0; r >= x; r--) {
		if (x == m) s = r * r;
		for (int h = h0; h >= x; h--)
			dfs(x - 1, s + 2 * r * h, v + r * r * h, r - 1, h - 1);
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		s_min[i] = s_min[i - 1] + 2 * i * i;
		v_min[i] = v_min[i - 1] + i * i * i;
	}
	dfs(m, 0, 0, sqrt(n), n);
	if (ans == 2e9) printf("0\n");
	else printf("%d\n", ans);
	return 0;
}