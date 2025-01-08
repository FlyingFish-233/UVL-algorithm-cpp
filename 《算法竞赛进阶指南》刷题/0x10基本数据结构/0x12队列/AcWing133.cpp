# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1e5 + 10;

int n, m, d, u, v, t;
int a[NR], delta;
queue<int> q[3];

int get()
{
	int x = 0, y = 0, z = 0;
	if (!q[0].empty()) x = q[0].front() + delta;
	if (!q[1].empty()) y = q[1].front() + delta;
	if (!q[2].empty()) z = q[2].front() + delta;
	if (x >= y && x >= z) { q[0].pop(); return x; }
	if (y >= x && y >= z) { q[1].pop(); return y; }
	if (z >= x && z >= y) { q[2].pop(); return z; }
}

int main()
{
	scanf("%d%d%d%d%d%d", &n, &m, &d, &u, &v, &t);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	for (int i = n; i >= 1; i--)
		q[0].push(a[i]);
	for (int i = 1; i <= m; i++) {
		int x = get();
		delta += d;
		q[1].push(1ll * x * u / v - delta);
		q[2].push(x - 1ll * x * u / v - delta);
		if (i % t == 0) printf("%d ", x);
	}
	puts("");
	for (int i = 1; !q[0].empty() || !q[1].empty() || !q[2].empty(); i++) {
		int x = get();
		if (i % t == 0) printf("%d ", x);
	}
	puts("");
	return 0;
}