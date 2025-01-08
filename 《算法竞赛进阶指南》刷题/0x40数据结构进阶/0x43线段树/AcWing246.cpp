# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

# define ls (rt << 1)
# define rs (rt << 1 | 1)
# define mid ((l + r) >> 1)

using namespace std;

const int NR = 5e5 + 10;

int n, m;
long long a[NR], s[NR];
long long tree[NR << 2];

int lowbit(int x)
{
	return x & (-x);
}

void change(int x, long long delta)
{
	for (int i = x; i <= n + 1; i += lowbit(i))
		s[i] += delta;
}

long long getsum(int x)
{
	long long ans = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		ans += s[i];
	return ans;
}

long long gcd(long long x, long long y)
{
	return (y == 0) ? x : gcd(y, x % y);
}

void build(int rt, int l, int r)
{
	if (l == r) { tree[rt] = a[l] - a[l - 1]; return; }
	build(ls, l, mid);
	build(rs, mid + 1, r);
	tree[rt] = gcd(tree[ls], tree[rs]);
}

void modify(int rt, int l, int r, int x, long long delta)
{
	if (l == r) { tree[rt] += delta; return; }
	if (x <= mid) modify(ls, l, mid, x, delta);
	else modify(rs, mid + 1, r, x, delta);
	tree[rt] = gcd(tree[ls], tree[rs]);
}

long long query(int rt, int l, int r, int l0, int r0)
{
	if (l0 <= l && r <= r0) return tree[rt];
	long long ans = 0;
	if (l0 <= mid) ans = gcd(ans, query(ls, l, mid, l0, r0));
	if (mid < r0) ans = gcd(ans, query(rs, mid + 1, r, l0, r0));
	return abs(ans);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]), change(i, a[i] - a[i - 1]);
	build(1, 1, n + 1);
	while (m--) {
		char c; int l, r; long long d;
		cin >> c;
		if (c == 'C') {
			scanf("%d%d%lld", &l, &r, &d);
			change(l, d), change(r + 1, -d);
			modify(1, 1, n + 1, l, d), modify(1, 1, n + 1, r + 1, -d);
		}
		if (c == 'Q') {
			scanf("%d%d", &l, &r);
			printf("%lld\n", gcd(getsum(l), query(1, 1, n + 1, l + 1, r)));
		}
	}
	return 0;
}