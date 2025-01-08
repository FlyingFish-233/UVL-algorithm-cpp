// P3372 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

int n, m;
long long a[NR], tag[NR], sum[NR];
int sz, blk[NR], L[NR], R[NR];

void pushdown(int x)
{
	if (tag[x] == 0) return;
	for (int i = L[x]; i <= R[x]; i++)
		a[i] += tag[x];
	tag[x] = 0;
}

void init()
{
	sz = sqrt(n);
	for (int i = 1; i <= n; i++)
		blk[i] = (i - 1) / sz + 1;
	for (int i = 1; i <= blk[n]; i++)
		L[i] = (i - 1) * sz + 1, R[i] = min(n, i * sz);
	for (int i = 1; i <= n; i++)
		sum[blk[i]] += a[i];
}

void modify(int l, int r, int delta)
{
	if (blk[l] == blk[r]) {
		pushdown(blk[l]);
		for (int i = l; i <= r; i++)
			a[i] += delta;
		sum[blk[l]] += (r - l + 1) * delta;
		return;
	}
	pushdown(blk[l]);
	for (int i = l; i <= R[blk[l]]; i++)
		a[i] += delta;
	sum[blk[l]] += (R[blk[l]] - l + 1) * delta;
	pushdown(blk[r]);
	for (int i = L[blk[r]]; i <= r; i++)
		a[i] += delta;
	sum[blk[r]] += (r - L[blk[r]] + 1) * delta;
	for (int i = blk[l] + 1; i <= blk[r] - 1; i++)
		tag[i] += delta, sum[i] += (R[i] - L[i] + 1) * delta;
}

long long getsum(int l, int r)
{
	long long ans = 0;
	if (blk[l] == blk[r]) {
		pushdown(blk[l]);
		for (int i = l; i <= r; i++)
			ans += a[i];
		return ans;
	}
	pushdown(blk[l]);
	for (int i = l; i <= R[blk[l]]; i++)
		ans += a[i];
	pushdown(blk[r]);
	for (int i = L[blk[r]]; i <= r; i++)
		ans += a[i];
	for (int i = blk[l] + 1; i <= blk[r] - 1; i++)
		ans += sum[i];
	return ans;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	init();
	while (m--) {
		int op, l, r, d;
		scanf("%d%d%d", &op, &l, &r);
		if (op == 1) scanf("%d", &d), modify(l, r, d);
		if (op == 2) printf("%lld\n", getsum(l, r));
	}
	return 0;
}