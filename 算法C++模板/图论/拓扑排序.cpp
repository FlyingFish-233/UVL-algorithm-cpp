// AcWing164 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>
# include <vector>
# include <bitset>

using namespace std;

const int NR = 3e4 + 10;

int n, m, in[NR];
vector<int> g[NR];
queue<int> q;
bitset<NR> sta[NR];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1, x, y; i <= m; i++) {
		scanf("%d%d", &x, &y);
		g[y].push_back(x), in[x]++;
	}
	for (int i = 1; i <= n; i++)
		sta[i][i] = 1;
	for (int i = 1; i <= n; i++)
		if (in[i] == 0) q.push(i);
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int i = 0; i < (int) g[x].size(); i++) {
			int y = g[x][i];
			sta[y] |= sta[x];
			if (--in[y] == 0) q.push(y);
		}
	}
	for (int i = 1; i <= n; i++)
		printf("%d\n", sta[i].count());
	return 0;
}