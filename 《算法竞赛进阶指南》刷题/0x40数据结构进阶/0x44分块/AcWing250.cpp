# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 250000 + 10;

struct Stone
{
	double d;
	int m, p, r;
};

bool cmp_m(Stone x, Stone y)
{
	return x.m < y.m;
}

bool cmp_d(Stone x, Stone y)
{
	return x.d < y.d;
}

int n;
Stone a[NR];
queue< pair<int, int> > q;

int sz, blk[NR], L[NR], R[NR], m_max[NR];
bool flag[NR];

int main()
{
	int x0, y0, p0, r0;
	scanf("%d%d%d%d%d", &x0, &y0, &p0, &r0, &n);
	for (int i = 1; i <= n; i++) {
		int x, y;
		scanf("%d%d%d%d%d", &x, &y, &a[i].m, &a[i].p, &a[i].r);
		a[i].d = sqrt(1.0 * (x - x0) * (x - x0) + 1.0 * (y - y0) * (y - y0));
	}
	sz = sqrt(n);
	for (int i = 1; i <= n; i++)
		blk[i] = (i - 1) / sz + 1;
	for (int i = 1; i <= blk[n]; i++)
		L[i] = (i - 1) * sz + 1, R[i] = min(n, i * sz);
	sort(a + 1, a + n + 1, cmp_m);
	for (int i = 1; i <= blk[n]; i++)
		m_max[i] = a[R[i]].m, sort(a + L[i], a + R[i] + 1, cmp_d);
	q.push({p0, r0});
	int ans = 0;
	while (!q.empty()) {
		int p = q.front().first, r = q.front().second; q.pop(), ans++;
		int k = upper_bound(m_max + 1, m_max + blk[n] + 1, p) - m_max;
		for (int i = 1; i <= k - 1; i++)
			for ( ; L[i] <= R[i] && a[L[i]].d <= r; L[i]++)
				if (!flag[L[i]]) flag[L[i]] = true, q.push({a[L[i]].p, a[L[i]].r});
		if (k > blk[n]) continue;
		for (int i = L[k]; i <= R[k]; i++)
			if (!flag[i] && a[i].d <= r && a[i].m <= p)
				flag[i] = true, q.push({a[i].p, a[i].r});
	}
	printf("%d\n", ans - 1);
	return 0;
}