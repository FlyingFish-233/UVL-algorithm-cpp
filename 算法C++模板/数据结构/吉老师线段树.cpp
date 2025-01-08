// P6242 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

# define ls (rt << 1)
# define rs (rt << 1 | 1)
# define mid ((l + r) >> 1)

const int NR = 5e5 + 10;
const int INF = 1e9;

struct Node
{
    long long sum;
    int l, r, maxa, se, cnt, maxb;
    // maxa为最大值,se为次大值,cnt为最大值出现次数,maxb为历史最大值
    int taga1, taga2, tagb1, tagb2;
    // taga1为最大值应加上的值,taga2为非最大值应加上的值
    // tagb1为历史上(结点标记的生存周期内)所有taga1中的最大值,tagb2为历史上所有taga2的最大值
};

int n, m;
int a[NR];
Node tree[NR << 2];

void pushUp(int rt)
{
    tree[rt].sum = tree[ls].sum + tree[rs].sum;
    tree[rt].maxa = max(tree[ls].maxa, tree[rs].maxa);
    tree[rt].maxb = max(tree[ls].maxb, tree[rs].maxb);
    if (tree[ls].maxa > tree[rs].maxa) {
        tree[rt].se = max(tree[ls].se, tree[rs].maxa);
        tree[rt].cnt = tree[ls].cnt;
    }
    else if (tree[ls].maxa < tree[rs].maxa) {
        tree[rt].se = max(tree[ls].maxa, tree[rs].se);
        tree[rt].cnt = tree[rs].cnt;
    }
    else {
        tree[rt].se = max(tree[ls].se, tree[rs].se);
        tree[rt].cnt = tree[ls].cnt + tree[rs].cnt;
    }
}

void build(int rt, int l, int r)
{
    tree[rt].l = l, tree[rt].r = r;
    if (l == r) {
        tree[rt].sum = tree[rt].maxa = tree[rt].maxb = a[l];
        tree[rt].se = -INF, tree[rt].cnt = 1;
        return;
    }
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushUp(rt);
}

void update(int rt, int adda1, int adda2, int addb1, int addb2)
{
    tree[rt].sum += 1ll * adda1 * tree[rt].cnt + 1ll * adda2 * (tree[rt].r - tree[rt].l + 1 - tree[rt].cnt);
    tree[rt].maxb = max(tree[rt].maxb, tree[rt].maxa + addb1);
    tree[rt].maxa += adda1;
    if (tree[rt].se != -INF) tree[rt].se += adda2;
    tree[rt].tagb1 = max(tree[rt].tagb1, tree[rt].taga1 + addb1) , tree[rt].taga1 += adda1;
    tree[rt].tagb2 = max(tree[rt].tagb2, tree[rt].taga2 + addb2) , tree[rt].taga2 += adda2;
}

void pushDown(int rt)
{
    int save = max(tree[ls].maxa, tree[rs].maxa);
    if (tree[ls].maxa == save) update(ls, tree[rt].taga1, tree[rt].taga2, tree[rt].tagb1, tree[rt].tagb2);
    else update(ls, tree[rt].taga2, tree[rt].taga2, tree[rt].tagb2, tree[rt].tagb2);
    if (tree[rs].maxa == save) update(rs, tree[rt].taga1, tree[rt].taga2, tree[rt].tagb1, tree[rt].tagb2);
    else update(rs, tree[rt].taga2, tree[rt].taga2, tree[rt].tagb2, tree[rt].tagb2);
    tree[rt].taga1 = tree[rt].taga2 = tree[rt].tagb1 = tree[rt].tagb2 = 0;
}

void modify_add(int rt, int l, int r, int l0, int r0, int k)
{
    if (l0 <= l && r <= r0) return update(rt, k, k, k, k);
    pushDown(rt);
    if (l0 <= mid) modify_add(ls, l, mid, l0, r0, k);
    if (mid < r0) modify_add(rs, mid + 1, r, l0, r0, k);
    pushUp(rt);
}

void modify_min(int rt, int l, int r, int l0, int r0, int k)
{
    if (k >= tree[rt].maxa) return;
    if (l0 <= l && r <= r0 && k > tree[rt].se) return update(rt, k - tree[rt].maxa, 0, k - tree[rt].maxa, 0);
    pushDown(rt);
    if (l0 <= mid) modify_min(ls, l, mid, l0, r0, k);
    if (mid < r0) modify_min(rs, mid + 1, r, l0, r0, k);
    pushUp(rt);
}

long long query_sum(int rt, int l, int r, int l0, int r0)
{
    if (l0 <= l && r <= r0) return tree[rt].sum;
    pushDown(rt);
    long long sum = 0;
    if (l0 <= mid) sum += query_sum(ls, l, mid, l0, r0);
    if (mid < r0) sum += query_sum(rs, mid + 1, r, l0, r0);
    pushUp(rt);
    return sum;
}

int query_maxa(int rt, int l, int r, int l0, int r0)
{
    if (l0 <= l && r <= r0) return tree[rt].maxa;
    pushDown(rt);
    int maxa = -INF;
    if (l0 <= mid) maxa = max(maxa, query_maxa(ls, l, mid, l0, r0));
    if (mid < r0) maxa = max(maxa, query_maxa(rs, mid + 1, r, l0, r0));
    pushUp(rt);
    return maxa;
}

int query_maxb(int rt, int l, int r, int l0, int r0)
{
    if (l0 <= l && r <= r0) return tree[rt].maxb;
    pushDown(rt);
    int maxb = -INF;
    if (l0 <= mid) maxb = max(maxb, query_maxb(ls, l, mid, l0, r0));
    if (mid < r0) maxb = max(maxb, query_maxb(rs, mid + 1, r, l0, r0));
    pushUp(rt);
    return maxb;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    build(1, 1, n);
    while (m--) {
        int op, l, r, k;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) scanf("%d", &k), modify_add(1, 1, n, l, r, k);
        if (op == 2) scanf("%d", &k), modify_min(1, 1, n, l, r, k);
        if (op == 3) printf("%lld\n", query_sum(1, 1, n, l, r));
        if (op == 4) printf("%d\n", query_maxa(1, 1, n, l, r));
        if (op == 5) printf("%d\n", query_maxb(1, 1, n, l, r));
    }
    return 0;
}