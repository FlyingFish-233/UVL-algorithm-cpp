# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define mid ((l + r) >> 1)

using namespace std;

const int NR = 1e5 + 10;

struct Node
{
	int ls, rs, cnt;
};

int n, m;
int len, a[NR], b[NR];
int tot, root[NR];
Node tree[NR << 5];

int build(int l, int r)
{
	int rt = ++tot;
	if (l == r) return rt;
	tree[rt].ls = build(l, mid);
	tree[rt].rs = build(mid + 1, r);
	return rt;
}

int modify(int oldrt, int l, int r, int x)
{
	int rt = ++tot;
	tree[rt] = tree[oldrt];
	tree[rt].cnt++;
	if (l == r) return rt;
	if (x <= mid) tree[rt].ls = modify(tree[rt].ls, l, mid, x);
	else tree[rt].rs = modify(tree[rt].rs, mid + 1, r, x);
	return rt;
}

int query(int rt1, int rt2, int l, int r, int k)
{
	if (l == r) return b[l];
	int tmp = tree[tree[rt2].ls].cnt - tree[tree[rt1].ls].cnt;
	if (k <= tmp) return query(tree[rt1].ls, tree[rt2].ls, l, mid, k);
	return query(tree[rt1].rs, tree[rt2].rs, mid + 1, r, k - tmp);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	memcpy(b, a, sizeof(a));
	sort(b + 1, b + n + 1);
	len = unique(b + 1, b + n + 1) - b - 1;
	root[0] = build(1, len);
	for (int i = 1; i <= n; i++)
		root[i] = modify(root[i - 1], 1, len, lower_bound(b + 1, b + len + 1, a[i]) - b);
	while (m--) {
		int l, r, k;
		scanf("%d%d%d", &l, &r, &k);
		printf("%d\n", query(root[l - 1], root[r], 1, len, k));
	}
	return 0;
}