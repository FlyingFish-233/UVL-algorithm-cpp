# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 1e5 + 10;

struct Task
{
	int id, l, r, x;
};

int n, m;
int a[NR];

int len, b[NR];
int s[NR], ans[NR];

int lowbit(int x)
{
	return x & (-x);
}

void modify(int x, int delta)
{
	for (int i = x; i <= len; i += lowbit(i))
		s[i] += delta;
}

int getsum(int x)
{
	int sum = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		sum += s[i];
	return sum;
}

void dfs(int l, int r, vector<Task> t)
{
	if (l == r) {
		for (int i = 0; i < (int)t.size(); i++)
			if (t[i].x != 0) ans[t[i].id] = b[l];
		return;
	}
	int mid = (l + r) >> 1;
	vector<Task> tl, tr;
	for (int i = 0; i < (int)t.size(); i++)
		if (t[i].x == 0) {
			if (a[t[i].id] <= mid) modify(t[i].id, 1), tl.push_back(t[i]);
			else tr.push_back(t[i]);
		}
		else {
			int tmp = getsum(t[i].r) - getsum(t[i].l - 1);
			if (t[i].x <= tmp) tl.push_back(t[i]);
			else t[i].x -= tmp, tr.push_back(t[i]);
		}
	for (int i = 0; i < (int)t.size(); i++)
		if (t[i].x == 0 && a[t[i].id] <= mid) modify(t[i].id, -1);
	dfs(l, mid, tl), dfs(mid + 1, r, tr);
}

int main()
{
	vector<Task> t;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), t.push_back((Task) {i, 0, 0, 0});
	for (int i = 1, l, r, k; i <= m; i++)
		scanf("%d%d%d", &l, &r, &k), t.push_back((Task) {i, l, r, k});
	memcpy(b, a, sizeof(a));
	sort(b + 1, b + n + 1);
	len = unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; i++)
		a[i] = lower_bound(b + 1, b + len + 1, a[i]) - b;
	dfs(1, len, t);
	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
	return 0;
}