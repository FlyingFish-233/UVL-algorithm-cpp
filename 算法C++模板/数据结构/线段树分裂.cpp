// P5494 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define mid ((l + r) >> 1)

using namespace std;

const int NR = 2e5 + 10;

struct Node
{
    int ls, rs;
    long long sum;
};

int n, tot;
int all = 1, root[NR];
Node tree[NR << 4];
int top, st[NR << 4];

int newNode()
{
    return (top > 0) ? st[top--] : ++tot;
}

void del(int rt)
{
    st[++top] = rt;
    tree[rt].ls = tree[rt].rs = tree[rt].sum = 0;
}

void modify(int &rt, int l, int r, int x, int delta)
{
    if (rt == 0) rt = newNode();
    tree[rt].sum += delta;
    if (l == r) return;
    if (x <= mid) modify(tree[rt].ls, l, mid, x, delta);
    else modify(tree[rt].rs, mid + 1, r, x, delta);
}

int merge(int x, int y, int l, int r)
{
    if (x == 0 || y == 0) return x + y;
    tree[x].sum += tree[y].sum;
    if (l == r) return x;
    int rt = x;
    tree[rt].ls = merge(tree[x].ls, tree[y].ls, l, mid);
    tree[rt].rs = merge(tree[x].rs, tree[y].rs, mid + 1, r);
    del(y);
    return rt;
}

void split(int x, int &y, long long k)
{
    if (x == 0) return;
    y = newNode();
    long long save = tree[tree[x].ls].sum;
    if (k > save) split(tree[x].rs, tree[y].rs, k - save);
    else swap(tree[x].rs, tree[y].rs), split(tree[x].ls, tree[y].ls, k);
    tree[y].sum = tree[x].sum - k, tree[x].sum = k;
}

long long query(int rt, int l, int r, int l0, int r0)
{
    if (rt == 0) return 0;
    if (l0 <= l && r <= r0) return tree[rt].sum;
    long long ans = 0;
    if (l0 <= mid) ans += query(tree[rt].ls, l, mid, l0, r0);
    if (mid < r0) ans += query(tree[rt].rs, mid + 1, r, l0, r0);
    return ans;
}

int kth(int rt, int l, int r, int k)
{
    if (tree[rt].sum < k) return -1;
    if (l == r) return l;
    long long save = tree[tree[rt].ls].sum;
    if (k <= save) return kth(tree[rt].ls, l, mid, k);
    return kth(tree[rt].rs, mid + 1, r, k - save);
}

int main()
{
    int T;
    scanf("%d%d", &n, &T);
    for (int i = 1, x; i <= n; i++)
        scanf("%d", &x), modify(root[1], 1, n, i, x);
    while (T--) {
        int op, x, y, z;
        scanf("%d", &op);
        if (op == 0) {
            scanf("%d%d%d", &x, &y, &z);
            long long l = query(root[x], 1, n, 1, y - 1), r = query(root[x], 1, n, 1, z);
            int save = 0;
            split(root[x], save, r);
            split(root[x], root[++all], l);
            root[x] = merge(root[x], save, 1, n);
        }
        if (op == 1) scanf("%d%d", &x, &y), root[x] = merge(root[x], root[y], 1, n);
        if (op == 2) scanf("%d%d%d", &x, &y, &z), modify(root[x], 1, n, z, y);
        if (op == 3) scanf("%d%d%d", &x, &y, &z), printf("%lld\n", query(root[x], 1, n, y, z));
        if (op == 4) scanf("%d%d", &x, &y), printf("%d\n", kth(root[x], 1, n, y));
    }
    return 0;
}