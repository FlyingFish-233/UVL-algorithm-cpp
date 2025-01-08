// P1856 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define ls (rt << 1)
# define rs (rt << 1 | 1)
# define mid ((l + r) >> 1)

using namespace std;

const int NR = 5e3 + 10, MR = 2e4 + 10;

struct Matrix
{
	int x1, y1, x2, y2;

	void read()
	{
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		x1 += 1e4, y1 += 1e4, x2 += 1e4, y2 += 1e4;
	}
};

struct ScanLine
{
	int x, y1, y2, d;

	bool operator < (const ScanLine &cmp) const
	{
		if (x != cmp.x) return x < cmp.x;
		return d > cmp.d;
	}
};

int n;
Matrix mat[NR];
ScanLine sl[NR << 1];
int sum[MR << 2], len[MR << 2];

void pushUp(int rt, int l, int r)
{
    if (sum[rt] > 0) len[rt] = r - l + 1;
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

int work()
{
	sort(sl + 1, sl + 2 * n + 1);
	int ans = 0;
	memset(sum, 0, sizeof(sum));
	memset(len, 0, sizeof(len));
	for (int i = 1; i <= 2 * n; i++) {
		int save = len[1];
		modify(1, 1, 2e4, sl[i].y1, sl[i].y2 - 1, sl[i].d);
		ans += abs(len[1] - save);
	}
	return ans;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		mat[i].read();
	for (int i = 1; i <= n; i++) {
		sl[i] = (ScanLine) {mat[i].x1, mat[i].y1, mat[i].y2, 1};
		sl[i + n] = (ScanLine) {mat[i].x2, mat[i].y1, mat[i].y2, -1};
	}
	int ans = work();
	for (int i = 1; i <= n; i++) {
		sl[i] = (ScanLine) {mat[i].y1, mat[i].x1, mat[i].x2, 1};
		sl[i + n] = (ScanLine) {mat[i].y2, mat[i].x1, mat[i].x2, -1};
	}
	printf("%d\n", ans + work());
	return 0;
}