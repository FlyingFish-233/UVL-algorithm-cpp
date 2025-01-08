# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <queue>

using namespace std;

const int NR = 1e5 + 10;

int n, m;
int a[NR];
vector<int> g[NR], g0[NR];

int f_min[NR], f_max[NR];
queue<int> q;
bool already[NR];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		g[x].push_back(y);
		if (z == 2) g[y].push_back(x);
		g0[y].push_back(x);
		if (z == 2) g0[x].push_back(y);
	}
	memset(f_min, 0x3f, sizeof(f_min));
	f_min[1] = a[1], q.push(1), already[1] = true;
	while (!q.empty()) {
		int x = q.front(); q.pop();
		already[x] = false;
		for (int i = 0; i < (int) g[x].size(); i++) {
			int y = g[x][i];
			if (f_min[y] <= min(f_min[x], a[y])) continue;
			f_min[y] = min(f_min[x], a[y]);
			if (!already[y]) already[y] = true, q.push(y);
		}
	}
	memset(f_max, -0x3f, sizeof(f_max));
	f_max[n] = a[n], q.push(n), already[n] = true;
	while (!q.empty()) {
		int x = q.front(); q.pop();
		already[x] = false;
		for (int i = 0; i < (int) g0[x].size(); i++) {
			int y = g0[x][i];
			if (f_max[y] >= max(f_max[x], a[y])) continue;
			f_max[y] = max(f_max[x], a[y]);
			if (!already[y]) already[y] = true, q.push(y);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans = max(ans, f_max[i] - f_min[i]);
	printf("%d\n", ans);
	return 0;
}