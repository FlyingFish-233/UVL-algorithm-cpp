// P3372 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define ls (rt << 1)
# define rs (rt << 1 | 1)
# define mid ((l + r) >> 1)

using namespace std;

const int NR = 1e5 + 10;

int n, m;
long long a[NR];
long long sum[NR << 2], tag[NR << 2];

void pushDown(int rt, int l, int r)
{
	if (tag[rt] == 0) return;
	sum[ls] += (mid - l + 1) * tag[rt], tag[ls] += tag[rt];
	sum[rs] += (r - mid) * tag[rt], tag[rs] += tag[rt];
	tag[rt] = 0;
}

void pushUp(int rt)
{
	sum[rt] = sum[ls] + sum[rs];
}

void build(int rt, int l, int r)
{
	if (l == r) { sum[rt] = a[l]; return; }
	build(ls, l, mid);
	build(rs, mid + 1, r);
	pushUp(rt);
}

void modify(int rt, int l, int r, int l0, int r0, long long delta)
{
	if (l0 <= l && r <= r0) { sum[rt] += (r - l + 1) * delta, tag[rt] += delta; return; }
	pushDown(rt, l, r);
	if (l0 <= mid) modify(ls, l, mid, l0, r0, delta);
	if (mid < r0) modify(rs, mid + 1, r, l0, r0, delta);
	pushUp(rt);
}

long long getsum(int rt, int l, int r, int l0, int r0)
{
	if (l0 <= l && r <= r0) return sum[rt];
	pushDown(rt, l, r);
	long long ans = 0;
	if (l0 <= mid) ans += getsum(ls, l, mid, l0, r0);
	if (mid < r0) ans += getsum(rs, mid + 1, r, l0, r0);
	pushUp(rt);
	return ans;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	build(1, 1, n);
	while (m--) {
		int op, x, y; long long k;
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1) scanf("%lld", &k), modify(1, 1, n, x, y, k);
		if (op == 2) printf("%lld\n", getsum(1, 1, n, x, y));
	}
	return 0;
}