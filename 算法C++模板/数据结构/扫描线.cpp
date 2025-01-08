// P5490 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

# define ls (rt << 1)
# define rs (rt << 1 | 1)
# define mid ((l + r) >> 1)

const int NR = 2e5 + 10;

struct ScanLine
{
	int x, y1, y2, d;

	bool operator < (const ScanLine &cmp) const {
		if (x != cmp.x) return x < cmp.x;
		return d > cmp.d;
	}
};

int n, m;
int p[NR];
ScanLine sl[NR];

int sum[NR << 2], len[NR << 2];

int id(int x)
{
	return lower_bound(p + 1, p + m + 1, x) - p;
}

// 线段树的叶子结点i表示的是(i,i+1)这条边
void pushUp(int rt, int l, int r)
{
	if (sum[rt] > 0) len[rt] = p[r + 1] - p[l];
	else if (l == r) len[rt] = 0;
	else len[rt] = len[ls] + len[rs];
}

void modify(int rt, int l, int r, int l0, int r0, int delta)
{
	if (l0 <= l && r <= r0) {
		sum[rt] += delta;
		pushUp(rt, l, r);
		return;
	}
	if (l0 <= mid) modify(ls, l, mid, l0, r0, delta);
	if (r0 > mid) modify(rs, mid + 1, r, l0, r0, delta);
	pushUp(rt, l, r);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		p[i] = y1, p[i + n] = y2;
		sl[i] = (ScanLine) {x1, y1, y2, 1};
		sl[i + n] = (ScanLine) {x2, y1, y2, -1};
	}
	sort(p + 1, p + 2 * n + 1);
	m = unique(p + 1, p + 2 * n + 1) - p - 1;
	sort(sl + 1, sl + 2 * n + 1);
	long long ans = 0;
	for (int i = 1; i < 2 * n; i++) {
		modify(1, 1, m - 1, id(sl[i].y1), id(sl[i].y2) - 1, sl[i].d);
		ans += 1ll * len[1] * (sl[i + 1].x - sl[i].x);
	}
	printf("%lld\n", ans);
	return 0;
}