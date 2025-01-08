// P1494 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e4 + 10;

int sz, blk[NR];

struct Question
{
	int id, l, r;
	bool operator < (const Question &cmp) const {
		if (blk[l] != blk[cmp.l]) return blk[l] < blk[cmp.l];
		if (blk[l] & 1) return r < cmp.r;
		return r > cmp.r;
	}
};

int n, m;
int a[NR];
Question q[NR];

int cnt[NR];
long long now;
long long ans1[NR], ans2[NR];

void add(int x)
{
	now -= 1ll * cnt[x] * (cnt[x] - 1);
	cnt[x]++;
	now += 1ll * cnt[x] * (cnt[x] - 1);
}

void del(int x)
{
	now -= 1ll * cnt[x] * (cnt[x] - 1);
	cnt[x]--;
	now += 1ll * cnt[x] * (cnt[x] - 1);
}

long long gcd(long long x, long long y)
{
	return (y == 0) ? x : gcd(y, x % y);
}

int main()
{
	scanf("%d%d", &n, &m);
	sz = sqrt(n);
	for (int i = 1; i <= n; i++)
		blk[i] = (i - 1) / sz + 1;
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++)
		scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
	sort(q + 1, q + m + 1);
	for (int i = 1, l = 1, r = 0; i <= m; i++) {
		while (r < q[i].r) add(a[++r]);
		while (l > q[i].l) add(a[--l]);
		while (r > q[i].r) del(a[r--]);
		while (l < q[i].l) del(a[l++]);
		long long x = now, y = 1ll * (q[i].r - q[i].l + 1) * (q[i].r - q[i].l);
		if (q[i].l == q[i].r) ans1[q[i].id] = 0, ans2[q[i].id] = 1;
		else ans1[q[i].id] = x / gcd(x, y), ans2[q[i].id] = y / gcd(x, y);
	}
	for (int i = 1; i <= m; i++)
		printf("%lld/%lld\n", ans1[i], ans2[i]);
	return 0;
}