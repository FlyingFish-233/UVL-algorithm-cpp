// AcWing296 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define ls (rt << 1)
# define rs (rt << 1 | 1)
# define mid ((l + r) >> 1)

using namespace std;

const int NR = 1e5 + 10;
const int INF = 0x3f3f3f3f;

struct Array
{
    int l, r, w;
    bool operator < (const Array &cmp) const {
        return r < cmp.r;
    }
};

int n, S, T;
Array a[NR];
int f[NR], tree[NR << 2];

void pushUp(int rt)
{
    tree[rt] = min(tree[ls], tree[rs]);
}

void build(int rt, int l, int r)
{
    if (l == r) { tree[rt] = f[l]; return; }
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushUp(rt);
}

void modify(int rt, int l, int r, int x, int val)
{
    if (l == r) { tree[rt] = val; return; }
    if (x <= mid) modify(ls, l, mid, x, val);
    else modify(rs, mid + 1, r, x, val);
    pushUp(rt);
}

int query(int rt, int l, int r, int l0, int r0)
{
    if (l0 <= l && r <= r0) return tree[rt];
    int ans = INF;
    if (l0 <= mid) ans = min(ans, query(ls, l, mid, l0, r0));
    if (mid < r0) ans = min(ans, query(rs, mid + 1, r, l0, r0));
    return ans;
}

// f[b[i]] = min(f[x]) + c[i] 其中a[i]-1 <= x <= b[i]-1
int main()
{
    scanf("%d%d%d", &n, &S, &T), S += 2, T += 2;
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].w), a[i].l += 2, a[i].r += 2;
    sort(a + 1, a + n + 1);
    memset(f, 0x3f, sizeof(f));
    f[S - 1] = 0, build(1, 1, T);
    for (int i = 1; i <= n; i++) {
        f[a[i].r] = min(f[a[i].r], query(1, 1, T, a[i].l - 1, a[i].r - 1) + a[i].w);
        modify(1, 1, T, a[i].r, f[a[i].r]);
    }
    printf("%d\n", (f[T] == INF) ? -1 : f[T]);
    return 0;
}