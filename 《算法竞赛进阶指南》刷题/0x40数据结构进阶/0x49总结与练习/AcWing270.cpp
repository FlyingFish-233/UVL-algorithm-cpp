# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define mid ((l + r) >> 1)

using namespace std;

const int NR = 2e5 + 10;

struct Node
{
	int ls, rs, fa, dep;
};

int n, m, ans;
int tot, root[NR];
Node tree[NR << 5];

int build(int l, int r)
{
	int rt = ++tot;
	if (l == r) { tree[rt].fa = l; return rt; }
	tree[rt].ls = build(l, mid);
	tree[rt].rs = build(mid + 1, r);
	return rt;
}

int modify(int oldrt, int l, int r, int x, int father)
{
	int rt = ++tot; tree[rt] = tree[oldrt];
	if (l == r) { tree[rt].fa = father; return rt; }
	if (x <= mid) tree[rt].ls = modify(tree[rt].ls, l, mid, x, father);
	else tree[rt].rs = modify(tree[rt].rs, mid + 1, r, x, father);
	return rt;
}


int adddep(int oldrt, int l, int r, int x)
{
	int rt = ++tot; tree[rt] = tree[oldrt];
	if (l == r) { tree[rt].dep++; return rt; }
	if (x <= mid) tree[rt].ls = adddep(tree[rt].ls, l, mid, x);
	else tree[rt].rs = adddep(tree[rt].rs, mid + 1, r, x);
	return rt;
}

Node query(int rt, int l, int r, int x)
{
	if (l == r) return tree[rt];
	if (x <= mid) return query(tree[rt].ls, l, mid, x);
	return query(tree[rt].rs, mid + 1, r, x);
}

Node find(int rt, int x)
{
	Node tmp = query(rt, 1, n, x);
	if (tmp.fa == x) return tmp;
	return find(rt, tmp.fa);
}

void merge(int &rt, int x, int y)
{
	Node a = find(rt, x), b = find(rt, y);
	if (a.dep > b.dep) swap(a, b);
	rt = modify(rt, 1, n, a.fa, b.fa);
	if (a.dep == b.dep) rt = adddep(rt, 1, n, b.fa);
}

int main()
{
	scanf("%d%d", &n, &m);
	root[0] = build(1, n);
	for (int i = 1; i <= m; i++) {
		int op, x, y;
		scanf("%d%d", &op, &x);
		if (op != 2) scanf("%d", &y);
		x ^= ans, y ^= ans;
		root[i] = root[i - 1];
		if (op == 1) merge(root[i], x, y);
		if (op == 2) root[i] = root[x];
		if (op == 3) printf("%d\n", ans = (find(root[i], x).fa == find(root[i], y).fa));
	}
	return 0;
}