// P1903 (100 pts)
# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 140000 + 10, MR = 1e6 + 10;

int sz, blk[NR];

struct Question
{
	int id, l, r, t;
	bool operator < (const Question &cmp) const {
		if (blk[l] != blk[cmp.l]) return blk[l] < blk[cmp.l];
		if (blk[r] != blk[cmp.r]) return blk[r] < blk[cmp.r];
		return t < cmp.t;
	}
};

int n, m;
int a[NR];
int qsz, csz;
Question q[NR];
struct Change { int x, pre, nw; } c[NR];
// q[i]表示第id次询问, 询问[l,r]区间的答案, 且上一次修改操作为t
// c[i]表示第i次修改, 把a[x]由pre改为了nw
int now, cnt[MR], ans[NR];

void add(int x)
{
	cnt[x]++;
	if (cnt[x] == 1) now++;
}

void del(int x)
{
	cnt[x]--;
	if (cnt[x] == 0) now--;
}

int main()
{
	scanf("%d%d", &n, &m);
	sz = pow(n, 2./3);
	for (int i = 1; i <= n; i++)
		blk[i] = (i - 1) / sz + 1;
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++) {
		char op; int x, y;
		cin >> op >> x >> y;
		if (op == 'Q') q[++qsz] = (Question) {qsz, x, y, csz};
		if (op == 'R') c[++csz] = (Change) {x, a[x], y}, a[x] = y;
	}
	for (int i = csz; i >= 1; i--)
		a[c[i].x] = c[i].pre;
	sort(q + 1, q + qsz + 1);
	for (int i = 1, l = 1, r = 0, t = 0; i <= qsz; i++) {
		while (r < q[i].r) add(a[++r]);
		while (l > q[i].l) add(a[--l]);
		while (r > q[i].r) del(a[r--]);
		while (l < q[i].l) del(a[l++]);
		while (t < q[i].t) {
			int x = c[++t].x;
			if (l <= x && x <= r) del(a[x]);
			a[x] = c[t].nw;
			if (l <= x && x <= r) add(a[x]);
		}
		while (t > q[i].t) {
			int x = c[t].x;
			if (l <= x && x <= r) del(a[x]);
			a[x] = c[t--].pre;
			if (l <= x && x <= r) add(a[x]);
		}
		ans[q[i].id] = now;
	}
	for (int i = 1; i <= qsz; i++)
		printf("%d\n", ans[i]);
	return 0;
}