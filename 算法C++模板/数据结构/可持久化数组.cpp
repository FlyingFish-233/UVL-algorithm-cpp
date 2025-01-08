// P3919 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define mid ((l + r) >> 1)

using namespace std;

const int NR = 1e6 + 10;

struct Node
{
    int ls, rs, val;
};

int n, m;
int a[NR];
int tot, root[NR];
Node tree[NR << 5];

int build(int l, int r)
{
    int rt = ++tot;
    if (l == r) { tree[rt].val = a[l]; return rt; }
    tree[rt].ls = build(l, mid);
    tree[rt].rs = build(mid + 1, r);
    return rt;
}

int modify(int oldrt, int l, int r, int x, int val)
{
    int rt = ++tot;
    tree[rt] = tree[oldrt];
    if (l == r) { tree[rt].val = val; return rt; }
    if (x <= mid) tree[rt].ls = modify(tree[rt].ls, l, mid, x, val);
    else tree[rt].rs = modify(tree[rt].rs, mid + 1, r, x, val);
    return rt;
}

int query(int rt, int l, int r, int x)
{
    if (l == r) return tree[rt].val;
    if (x <= mid) return query(tree[rt].ls, l, mid, x);
    return query(tree[rt].rs, mid + 1, r, x);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    root[0] = build(1, n);
    for (int i = 1; i <= m; i++) {
        int v, op, x, val;
        scanf("%d%d%d", &v, &op, &x);
        if (op == 1) scanf("%d", &val), root[i] = modify(root[v], 1, n, x, val);
        if (op == 2) printf("%d\n", query(root[v], 1, n, x)), root[i] = root[v];
    }
    return 0;
}