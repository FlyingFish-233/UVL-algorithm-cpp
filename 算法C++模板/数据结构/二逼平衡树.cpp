// P3380 (O2 -> 100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e4 + 10;
const int INF = 2147483647;

int read()
{
    char c = getchar(); int num = 0; int flag = 1;
    for ( ; c < '0' || c > '9'; c = getchar())
        if (c == '-') flag = -1;
    for ( ; c >= '0' && c <= '9'; c = getchar())
        num = num * 10 + c - '0';
    return flag * num;
}

struct Node
{
    int ls, rs, val, rnd, sz;
};

int tot;
Node node[2000010];

struct InTree
{
    int root;

    int newNode(int val)
    {
        node[++tot].val = val;
        node[tot].rnd = rand();
        node[tot].sz = 1;
        return tot;
    }

    void pushUp(int rt)
    {
        node[rt].sz = node[node[rt].ls].sz + 1 + node[node[rt].rs].sz;
    }

    int merge(int x, int y)
    {
        if (x == 0 || y == 0) return x + y;
        int rt = 0;
        if (node[x].rnd > node[y].rnd) node[rt = x].rs = merge(node[x].rs, y);
        else node[rt = y].ls = merge(x, node[y].ls);
        pushUp(rt);
        return rt;
    }

    void split_rank(int rt, int &x, int &y, int k)
    {
        if (rt == 0) { x = y = 0; return; }
        int tmp = node[node[rt].ls].sz + 1;
        if (k < tmp) split_rank(node[y = rt].ls, x, node[rt].ls, k);
        else split_rank(node[x = rt].rs, node[rt].rs, y, k - tmp);
        pushUp(rt);
    }

    void split_val(int rt, int &x, int &y, int k)
    {
        if (rt == 0) { x = y = 0; return; }
        if (k <= node[rt].val) split_val(node[y = rt].ls, x, node[rt].ls, k);
        else split_val(node[x = rt].rs, node[rt].rs, y, k);
        pushUp(rt);
    }

    void insert(int x)
    {
        int a, b;
        split_val(root, a, b, x);
        root = merge(merge(a, newNode(x)), b);
    }

    void del(int x)
    {
        int a, b, c;
        split_val(root, a, b, x);
        split_rank(b, b, c, 1);
        root = merge(a, c);
    }

    int getRank(int x)
    {
        int a, b;
        split_val(root, a, b, x);
        int ans = node[a].sz + 1;
        root = merge(a, b);
        return ans;
    }

    int getVal(int x)
    {
        int a, b, c;
        split_rank(root, a, b, x - 1);
        split_rank(b, b, c, 1);
        int ans = node[b].val;
        root = merge(merge(a, b), c);
        return ans;
    }

    int getPrev(int x)
    {
        int a, b, c;
        split_val(root, a, c, x);
        split_rank(a, a, b, node[a].sz - 1);
        int ans = (b == 0) ? -INF : node[b].val;
        root = merge(merge(a, b), c);
        return ans;
    }

    int getNext(int x)
    {
        int a, b, c;
        split_val(root, a, b, x + 1);
        split_rank(b, b, c, 1);
        int ans = (b == 0) ? INF : node[b].val;
        root = merge(merge(a, b), c);
        return ans;
    }
};

int n, m;
int a[NR];

struct OutTree
{
    # define lson (rt << 1)
    # define rson (rt << 1 | 1)
    # define mid ((l + r) >> 1)
    InTree tree[NR << 2];

    void build(int rt, int l, int r)
    {
        for (int i = l; i <= r; i++)
            tree[rt].insert(a[i]);
        if (l == r) return;
        build(lson, l, mid);
        build(rson, mid + 1, r);
    }

    void modify(int rt, int l, int r, int x, int val)
    {
        tree[rt].del(a[x]), tree[rt].insert(val);
        if (l == r) return;
        if (x <= mid) modify(lson, l, mid, x, val);
        else modify(rson, mid + 1, r, x, val);
    }

    int getRank(int rt, int l, int r, int l0, int r0, int val)
    {
        if (l0 <= l && r <= r0) return tree[rt].getRank(val);
        int ans = 0;
        if (l0 <= mid) ans += getRank(lson, l, mid, l0, r0, val) - 1;
        if (mid < r0) ans += getRank(rson, mid + 1, r, l0, r0, val) - 1;
        return ans + 1;
    }

    int getVal(int l0, int r0, int k)
    {
        int l = 0, r = 1e8, ans = 0;
        while (l <= r) {
            if (getRank(1, 1, n, l0, r0, mid) <= k)
                ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        return ans;
    }

    int getPrev(int rt, int l, int r, int l0, int r0, int val)
    {
        if (l0 <= l && r <= r0) return tree[rt].getPrev(val);
        int ans = -INF;
        if (l0 <= mid) ans = max(ans, getPrev(lson, l, mid, l0, r0, val));
        if (mid < r0) ans = max(ans, getPrev(rson, mid + 1, r, l0, r0, val));
        return ans;
    }

    int getNext(int rt, int l, int r, int l0, int r0, int val)
    {
        if (l0 <= l && r <= r0) return tree[rt].getNext(val);
        int ans = INF;
        if (l0 <= mid) ans = min(ans, getNext(lson, l, mid, l0, r0, val));
        if (mid < r0) ans = min(ans, getNext(rson, mid + 1, r, l0, r0, val));
        return ans;
    }
};

OutTree ST;

int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    ST.build(1, 1, n);
    while (m--) {
        int op = read(), l = read(), r = read();
        if (op == 1) printf("%d\n", ST.getRank(1, 1, n, l, r, read()));
        if (op == 2) printf("%d\n", ST.getVal(l, r, read()));
        if (op == 3) ST.modify(1, 1, n, l, r), a[l] = r;
        if (op == 4) printf("%d\n", ST.getPrev(1, 1, n, l, r, read()));
        if (op == 5) printf("%d\n", ST.getNext(1, 1, n, l, r, read()));
    }
    return 0;
}