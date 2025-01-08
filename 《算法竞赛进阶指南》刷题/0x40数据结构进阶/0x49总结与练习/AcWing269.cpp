# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e5 + 10, MR = 210;

struct Node
{
	int next[2], cnt;
};

int n, m, ans;
int a[NR];

int tot, root[NR];
Node tree[NR << 5];

int sz, blk[NR];
int L[MR], R[MR];
int f[MR][MR];

int insert(int oldrt, int x, int k)
{
	int rt = ++tot, t = (x >> k) & 1;
	tree[rt] = tree[oldrt], tree[rt].cnt++;
	if (k >= 0) tree[rt].next[t] = insert(tree[rt].next[t], x, k - 1);
	return rt;
}

int query(int rt1, int rt2, int x, int k)
{
	if (k < 0) return 0;
	int t = (x >> k) & 1;
	if (tree[tree[rt2].next[!t]].cnt > tree[tree[rt1].next[!t]].cnt)
		return (1 << k) | query(tree[rt1].next[!t], tree[rt2].next[!t], x, k - 1);
	return query(tree[rt1].next[t], tree[rt2].next[t], x, k - 1);
}

int ask(int l, int r, int x)
{
	if (l == 0) return query(0, root[r], x, 31);
	return query(root[l - 1], root[r], x, 31);
}

int main()
{
	scanf("%d%d", &n, &m);
	root[0] = insert(0, 0, 31);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), root[i] = insert(root[i - 1], a[i] ^= a[i - 1], 31);
	sz = sqrt(n);
	for (int i = 1; i <= n; i++)
		blk[i] = (i - 1) / sz + 1;
	for (int i = 1; i <= blk[n]; i++)
		L[i] = (i - 1) * sz + 1, R[i] = min(i * sz, n);
	for (int i = 1; i <= blk[n]; i++)
		for (int j = i; j <= blk[n]; j++) {
			f[i][j] = f[i][j - 1];
			for (int k = L[j]; k <= R[j]; k++)
				f[i][j] = max(f[i][j], ask(L[i], R[j], a[k]));
		}
	while (m--) {
		int l, r;
		scanf("%d%d", &l, &r);
		ans %= n, l = (l + ans) % n + 1, r = (r + ans) % n + 1;
		if (l > r) swap(l, r);
		if (blk[--l] == blk[r]) {
			ans = 0;
			for (int i = l; i <= r; i++)
				ans = max(ans, ask(l, r, a[i]));
			printf("%d\n", ans);
			continue;
		}
		ans = f[blk[l] + 1][blk[r] - 1];
		for (int i = l; i <= R[blk[l]]; i++)
			ans = max(ans, ask(l, r, a[i]));
		for (int i = L[blk[r]]; i <= r; i++)
			ans = max(ans, ask(l, r, a[i]));
		printf("%d\n", ans);
	}
	return 0;
}