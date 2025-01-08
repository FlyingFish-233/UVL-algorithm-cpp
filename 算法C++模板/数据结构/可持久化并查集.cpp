// P3402 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define mid ((l + r) >> 1)

using namespace std;

const int NR = 1e5 + 10;

struct Node
{
    int ls, rs, fa, dep;
};

int n, m;
int tot, root[NR];
Node tree[NR << 5];

int build(int l, int r)
{
    int rt = ++tot;
    if (l == r) { tree[rt].fa = l, tree[rt].dep = 1; return rt; }
    tree[rt].ls = build(l, mid);
    tree[rt].rs = build(mid + 1, r);
    return rt;
}

int modify_father(int oldrt, int l, int r, int x, int fa)
{
    int rt = ++tot;
    tree[rt] = tree[oldrt];
    if (l == r) { tree[rt].fa = fa; return rt; }
    if (x <= mid) tree[rt].ls = modify_father(tree[rt].ls, l, mid, x, fa);
    else tree[rt].rs = modify_father(tree[rt].rs, mid + 1, r, x, fa);
    return rt;
}

int modify_depth(int oldrt, int l, int r, int x)
{
    int rt = ++tot;
    tree[rt] = tree[oldrt];
    if (l == r) { tree[rt].dep++; return rt; }
    if (x <= mid) tree[rt].ls = modify_depth(tree[rt].ls, l, mid, x);
    else tree[rt].rs = modify_depth(tree[rt].rs, mid + 1, r, x);
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
	rt = modify_father(rt, 1, n, a.fa, b.fa);
	if (a.dep == b.dep) rt = modify_depth(rt, 1, n, b.fa);
}

int main()
{
	scanf("%d%d", &n, &m);
	root[0] = build(1, n);
	for (int i = 1; i <= m; i++) {
		int type, x, y;
		scanf("%d", &type);
		root[i] = root[i - 1];
		if (type == 1) scanf("%d%d", &x, &y), merge(root[i], x, y);
		if (type == 2) scanf("%d", &x), root[i] = root[x];
		if (type == 3) {
			scanf("%d%d", &x, &y);
			Node a = find(root[i], x), b = find(root[i], y);
			printf("%d\n", a.fa == b.fa);
		}
	}
    return 0;
}