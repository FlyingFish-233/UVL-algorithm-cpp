# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 1000 + 10;

int n, root;
int a[NR], fa[NR], s[NR];
vector<int> q[NR];

int main()
{
	scanf("%d%d", &n, &root);
	for (int i = 0; i <= n; i++)
		q[i].push_back(i);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), s[i] = a[i];
	for (int i = 1, x, y; i <= n - 1; i++)
		scanf("%d%d", &x, &y), fa[y] = x;

	for (int cnt = 1; cnt < n; cnt++) {
		int x = 0;
		for (int i = 1; i <= n; i++)
			if (i != root && s[i] * q[x].size() > s[x] * q[i].size()) x = i;
		int y = fa[x];
		for (int i = 1; i <= n; i++)
			if (fa[i] == x) fa[i] = y;
		s[y] += s[x];
		fa[x] = s[x] = 0;
		for (int i = 0; i < (int) q[x].size(); i++)
			q[y].push_back(q[x][i]);
		while (!q[x].empty()) q[x].pop_back();
	}
	int ans = 0;
	for (int i = 0; i < (int) q[root].size(); i++)
		ans += (i + 1) * a[q[root][i]];
	printf("%d\n", ans);
	return 0;
}