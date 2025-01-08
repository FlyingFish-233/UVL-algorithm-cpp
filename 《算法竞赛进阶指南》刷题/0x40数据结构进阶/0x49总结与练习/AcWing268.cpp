# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 3e5 + 10;

struct Task
{
	int id, x;
};

int n, m, k;
int L[NR], R[NR], D[NR], ans[NR];
vector<int> v[NR];
long long s[NR];

inline int lowbit(int x)
{
	return x & (-x);
}

inline void modify(int x, int delta)
{
	for (register int i = x; i <= m; i += lowbit(i))
		s[i] += delta;
}

inline long long getsum(int x)
{
	long long sum = 0;
	for (register int i = x; i > 0; i -= lowbit(i))
		sum += s[i];
	return sum;
}

inline void update(int l, int r, int d)
{
	if (l <= r) modify(l, d), modify(r + 1, -d);
	else modify(1, d), modify(r + 1, -d), modify(l, d);
}

inline void dfs(int l, int r, vector<Task> t)
{
	if (l == r) {
		for (register int i = 0; i < (int) t.size(); i++)
			ans[t[i].id] = l;
		return;
	}
	int mid = (l + r) >> 1;
	vector<Task> tl, tr;
	for (register int i = l; i <= mid; i++)
		update(L[i], R[i], D[i]);
	for (register int i = 0; i < (int) t.size(); i++) {
		long long sum = 0;
		for (register int j = 0; j < (int) v[t[i].id].size() && sum <= t[i].x; j++)
			sum += getsum(v[t[i].id][j]);
		if (t[i].x <= sum) tl.push_back(t[i]);
		else t[i].x -= sum, tr.push_back(t[i]);
	}
	for (register int i = l; i <= mid; i++)
		update(L[i], R[i], -D[i]);
	dfs(l, mid, tl), dfs(mid + 1, r, tr);
}

int main()
{
	vector<Task> t;
	scanf("%d%d", &n, &m);
	for (register int i = 1, x; i <= m; i++)
		scanf("%d", &x), v[x].push_back(i);
	for (register int i = 1, x; i <= n; i++)
		scanf("%d", &x), t.push_back((Task) {i, x});
	scanf("%d", &k);
	for (register int i = 1; i <= k; i++)
		scanf("%d%d%d", &L[i], &R[i], &D[i]);
	dfs(1, k + 1, t);
	for (register int i = 1; i <= n; i++)
		if (ans[i] > k) printf("NIE\n");
		else printf("%d\n", ans[i]);
	return 0;
}