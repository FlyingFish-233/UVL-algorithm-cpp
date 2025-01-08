// P2617 (100 pts)
# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 1e5 + 10;

struct Task
{
	int type, id, x, y, k;
	// type=0时, 若y=1则将a[id]由0修改为x, 若y=-1则将a[id]由x修改为0
	// type=1时, 表示第id次询问为[l,r]中第k小数
};

int n, m, cnt;
int a[NR], s[NR];
int ans[NR];

int lowbit(int x)
{
	return x & (-x);
}

void modify(int x, int delta)
{
	for (int i = x; i <= n; i += lowbit(i))
		s[i] += delta;
}

int getsum(int x)
{
	int sum = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		sum += s[i];
	return sum;
}

void dfs(int l, int r, vector <Task> &t)
{
	if (t.size() == 0) return;
	if (l == r) {
		for (int i = 0; i < (int) t.size(); i++)
			if (t[i].type == 1) ans[t[i].id] = l;
		return;
	}
	int mid = (l + r) >> 1;
	vector <Task> tl, tr;
	for (int i = 0; i < (int) t.size(); i++) {
		if (t[i].type == 0) {
			if (t[i].x <= mid) modify(t[i].id, t[i].y), tl.push_back(t[i]);
			else tr.push_back(t[i]);
		}
		else {
			int tmp = getsum(t[i].y) - getsum(t[i].x - 1);
			if (tmp >= t[i].k) tl.push_back(t[i]);
			else t[i].k -= tmp, tr.push_back(t[i]);
		}
	}
	for (int i = 0; i < (int) t.size(); i++)
		if (t[i].type == 0 && t[i].x <= mid) modify(t[i].id, -t[i].y);
	dfs(l, mid, tl), dfs(mid + 1, r, tr);
}

int main()
{
	vector <Task> t;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		t.push_back((Task) {0, i, a[i], 1});
	}
	for (int i = 1; i <= m; i++) {
		char type;
		cin >> type;
		if (type == 'Q') {
			int l, r, k;
			scanf("%d%d%d", &l, &r, &k);
			t.push_back((Task) {1, ++cnt, l, r, k});
		}
		if (type == 'C') {
			int x, val;
			scanf("%d%d", &x, &val);
			t.push_back((Task) {0, x, a[x], -1});
			t.push_back((Task) {0, x, val, 1});
			a[x] = val;
		}
	}
	dfs(0, 1e9, t);
	for (int i = 1; i <= cnt; i++)
		printf("%d\n", ans[i]);
    return 0;
}