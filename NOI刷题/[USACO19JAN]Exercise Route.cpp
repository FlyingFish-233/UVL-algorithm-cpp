// P5203 (100 pts)
// Lemma: 符合题意的路线<=>一对点在树上的路径与另一对点在树上的路径有重边
// Question: 求树上有几对路径有重边
// Solution: 将每条路径拆成两条链，分别统计每个链上的有几个其他链的起点，然后去重
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <map>

using namespace std;

const int NR = 2e5 + 10;

struct Edge
{
	int to, next;
};

int n, m;
vector<int> g[NR];
int dep[NR], fa[NR][30];

void build(int x, int dad)
{
	dep[x] = dep[fa[x][0] = dad] + 1;
	for (int i = 1; (1 << i) <= dep[x]; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (int i = 0; i < (int) g[x].size(); i++)
		if (g[x][i] != dad) build(g[x][i], x);
}

int lca(int x, int y)
{
	if (dep[x] > dep[y]) swap(x, y);
	for (int i = 20; i >= 0; i--)
		if (dep[fa[y][i]] >= dep[x]) y = fa[y][i];
	if (x == y) return x;
	for (int i = 20; i >= 0; i--)
		if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

int u[NR], v[NR];
map<pair<int,int>, int> mp;
int cnt[NR], sum[NR];

int getTop(int y, int x)
{
	if (y == x) return -1;
	for (int i = 20; i >= 0; i--)
		if (dep[fa[y][i]] > dep[x]) y = fa[y][i];
	return y;
}

void dfs(int x, int dad)
{
	sum[x] = sum[dad] + cnt[x];
	for (int i = 0; i < (int) g[x].size(); i++)
		if (g[x][i] != dad) dfs(g[x][i], x);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1, x, y; i <= n - 1; i++)
		scanf("%d%d", &x, &y), g[x].push_back(y), g[y].push_back(x);
	dep[0] = 1, build(1, 0);
	long long ans = 0;
	for (int i = 1; i <= m - (n-1); i++) {
		scanf("%d%d", &u[i], &v[i]);
		int z = lca(u[i], v[i]);
		int topx = getTop(u[i], z), topy = getTop(v[i], z);
		if (topx != -1) cnt[topx]++, ans -= cnt[topx]; // z-topx上有n条链，对答案贡献应为C(n,2)，而实际算的是n^2
		if (topy != -1) cnt[topy]++, ans -= cnt[topy];
		if (topx != -1 && topy != -1) {
			if (topx > topy) swap(topx, topy);
			ans -= mp[make_pair(topx, topy)]; // 过topx-z-topy的路径由于有两条链，被计算了两次
			mp[make_pair(topx, topy)]++;
		}
	}
	dfs(1, 0);
	for (int i = 1; i <= m - (n-1); i++)
		ans += sum[u[i]] + sum[v[i]] - 2 * sum[lca(u[i], v[i])];
	printf("%lld\n", ans);
	return 0;
}