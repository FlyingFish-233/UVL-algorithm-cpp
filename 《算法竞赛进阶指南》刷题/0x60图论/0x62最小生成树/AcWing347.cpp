# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <map>
# include <vector>

using namespace std;

const int NR = 1000;

int n, m, k;
int u[NR], v[NR];
map<string, int> mp;
pair<int, int> pr[NR];

int fa[NR];

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
	fa[find(x)] = find(y);
}

struct Edge
{
	int to, next, w;
};

int gsz = 1, fte[NR];
Edge g[NR];
bool used[NR];
int tot, color[NR];

int save[NR], tmp[NR];

void addEdge(int x, int y, int w)
{
	g[++gsz] = (Edge) {y, fte[x], w}, fte[x] = gsz;
	g[++gsz] = (Edge) {x, fte[y], w}, fte[y] = gsz;
}

int w_max, that_edge;

bool dfs(int x, int fa)
{
	if (x == 1) return true;
	for (int i = fte[x]; i; i = g[i].next) {
		int y = g[i].to;
		if (y != fa && used[i >> 1] && dfs(y, x)) {
			if (w_max < g[i].w) w_max = g[i].w, that_edge = i >> 1;
			return true;
		}
	}
	return false;
}

int main()
{
	scanf("%d", &m);
	mp["Park"] = ++n;
	for (int i = 1; i <= m; i++) {
		string s1, s2; int w;
		cin >> s1 >> s2 >> w;
		if (mp.count(s1) == 0) mp[s1] = ++n;
		if (mp.count(s2) == 0) mp[s2] = ++n;
		addEdge(u[i] = mp[s1], v[i] = mp[s2], w), pr[i] = {w, i};
	}
	scanf("%d", &k);

	for (int i = 1; i <= n; i++) fa[i] = i;
	sort(pr + 1, pr + m + 1);
	int ans = 0;
	for (int i = 1; i <= m; i++) {
		int x = u[pr[i].second], y = v[pr[i].second];
		if (x != 1 && y != 1 && find(x) != find(y))
			used[pr[i].second] = true, merge(x, y), ans += pr[i].first;
	}
	for (int i = 2; i <= n; i++) {
		if (save[find(i)] == 0) save[find(i)] = ++tot;
		color[i] = save[find(i)];
	}
	memset(save, 0x3f, sizeof(save));
	for (int i = fte[1]; i; i = g[i].next) if (save[color[g[i].to]] > g[i].w)
		tmp[color[g[i].to]] = i >> 1, save[color[g[i].to]] = g[i].w;
	for (int i = 1; i <= tot; i++)
		used[tmp[i]] = true, ans += g[tmp[i] << 1].w;
	while (--k >= tot) {
		int d_max = 0, insert_edge = 0, delete_edge = 0;
		for (int i = fte[1]; i; i = g[i].next) if (!used[i >> 1]) {
			int x = g[i].to;
			w_max = 0, dfs(x, 0);
			if (d_max < w_max - g[i].w)
				d_max = w_max - g[i].w, insert_edge = i >> 1, delete_edge = that_edge;
		}
		if (d_max == 0) break;
		ans -= d_max, used[insert_edge] = true, used[delete_edge] = false;
	}
	printf("Total miles driven: %d\n", ans);
	return 0;
}