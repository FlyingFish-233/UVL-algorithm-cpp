# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define ls (rt << 1)
# define rs (rt << 1 | 1)
# define mid ((l + r) >> 1)

using namespace std;

const int NR = 2e4 + 10;

struct ScanLine
{
	int x, y1, y2, d;
	bool operator < (const ScanLine &cmp) const {
		if (x != cmp.x) return x < cmp.x;
		return d > cmp.d;
	}
};

int n;
ScanLine sl[NR];
int len[NR << 3], cnt[NR << 3];

void pushUp(int rt, int l, int r)
{
	if (cnt[rt] > 0) len[rt] = r - l + 1;
	else len[rt] = len[ls] + len[rs];
}

void modify(int rt, int l, int r, int l0, int r0, int d)
{
	if (r < l0 || r0 < l) return;
	if (l0 <= l && r <= r0) {
		cnt[rt] += d;
		pushUp(rt, l, r);
		return;
	}
	if (l0 <= mid) modify(ls, l, mid, l0, r0, d);
	if (mid < r0) modify(rs, mid + 1, r, l0, r0, d);
	pushUp(rt, l, r);
}

int solve()
{
	sort(sl + 1, sl + 2 * n + 1);
	memset(len, 0, sizeof(len));
	memset(cnt, 0, sizeof(cnt));
	int ans = 0;
	for (int i = 1; i <= 2 * n; i++) {
		int tmp = len[1];
		modify(1, 0, 2e4, sl[i].y1, sl[i].y2 - 1, sl[i].d);
		ans += abs(len[1] - tmp);
	}
	return ans;
}

int main()
{
	int x1[NR], y1[NR], x2[NR], y2[NR];
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d%d", &x1[i], &y1[i], &x2[i], &y2[i]);
		x1[i] += 1e4, y1[i] += 1e4, x2[i] += 1e4, y2[i] += 1e4;
	}
	for (int i = 1; i <= n; i++) {
		sl[i] = (ScanLine) {x1[i], y1[i], y2[i], 1};
		sl[i + n] = (ScanLine) {x2[i], y1[i], y2[i], -1};
	}
	int save = solve();
	for (int i = 1; i <= n; i++) {
		sl[i] = (ScanLine) {y1[i], x1[i], x2[i], 1};
		sl[i + n] = (ScanLine) {y2[i], x1[i], x2[i], -1};
	}
	printf("%d\n", save + solve());
	return 0;
}