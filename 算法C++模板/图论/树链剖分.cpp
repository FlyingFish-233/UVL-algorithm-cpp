// P3384 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define ls (rt << 1)
# define rs (rt << 1 | 1)
# define mid ((l + r) >> 1)

using namespace std;

const int NR = 1e5 + 10;

int n, T, root, mod;
long long w[NR];

struct Edge
{
    int to, next;
};

int gsz = 1, fte[NR];
Edge g[NR << 1];

void addEdge(int x, int y)
{
    g[++gsz] = (Edge) {y, fte[x]}, fte[x] = gsz;
    g[++gsz] = (Edge) {x, fte[y]}, fte[y] = gsz;
}

int son[NR], sz[NR], dep[NR], fa[NR];
int now, dfn[NR], rk[NR], top[NR];

void dfs1(int x, int dad)
{
    dep[x] = dep[fa[x] = dad] + 1, son[x] = -1, sz[x] = 1;
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if (y == dad) continue;
        dfs1(y, x), sz[x] += sz[y];
        if (son[x] == -1 || sz[y] > sz[son[x]]) son[x] = y;
    }
}

void dfs2(int x, int t)
{
    dfn[x] = ++now, rk[now] = x, top[x] = t;
    if (son[x] == -1) return;
    dfs2(son[x], t);
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if (y != son[x] && y != fa[x]) dfs2(y, y);
    }
}

long long sum[NR << 2], tag[NR << 2];

void pushDown(int rt, int l, int r)
{
    if (tag[rt] == 0) return;
    (sum[ls] += (mid - l + 1) * tag[rt] % mod) %= mod, (tag[ls] += tag[rt]) %= mod;
    (sum[rs] += (r - mid) * tag[rt] % mod) %= mod, (tag[rs] += tag[rt]) %= mod;
    tag[rt] = 0;
}

void pushUp(int rt)
{
    sum[rt] = (sum[ls] + sum[rs]) % mod;
}

void build(int rt, int l, int r)
{
    if (l == r) { sum[rt] = w[rk[l]] % mod; return; }
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushUp(rt);
}

void modify(int rt, int l, int r, int l0, int r0, long long delta)
{
    if (l0 <= l && r <= r0) { (sum[rt] += (r - l + 1) * delta % mod) %= mod, (tag[rt] += delta) %= mod; return; }
    pushDown(rt, l, r);
    if (l0 <= mid) modify(ls, l, mid, l0, r0, delta);
    if (mid < r0) modify(rs, mid + 1, r, l0, r0, delta);
    pushUp(rt);
}

long long getsum(int rt, int l, int r, int l0, int r0)
{
    if (l0 <= l && r <= r0) return (sum[rt] + mod) % mod;
    pushDown(rt, l, r);
    long long ans = 0;
    if (l0 <= mid) (ans += getsum(ls, l, mid, l0, r0)) %= mod;
    if (mid < r0) (ans += getsum(rs, mid + 1, r, l0, r0)) %= mod;
    pushUp(rt);
    return ans;
}

void modify_path(int x, int y, long long delta)
{
    while (top[x] != top[y]) {
        if (dep[top[x]] > dep[top[y]]) swap(x, y);
        modify(1, 1, n, dfn[top[y]], dfn[y], delta);
        y = fa[top[y]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    modify(1, 1, n, dfn[x], dfn[y], delta);
}

long long query_path(int x, int y)
{
    long long ans = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] > dep[top[y]]) swap(x, y);
        (ans += getsum(1, 1, n, dfn[top[y]], dfn[y])) %= mod;
        y = fa[top[y]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    (ans += getsum(1, 1, n, dfn[x], dfn[y])) %= mod;
    return ans;
}

int main()
{
    scanf("%d%d%d%d", &n, &T, &root, &mod);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &w[i]);
    for (int i = 1, x, y; i <= n - 1; i++)
        scanf("%d%d", &x, &y), addEdge(x, y);
    dfs1(root, 0), dfs2(root, root), build(1, 1, n);
    while (T--) {
        int op, x, y; long long z;
        scanf("%d%d", &op, &x);
        if (op == 1) scanf("%d%lld", &y, &z), modify_path(x, y, z);
        if (op == 2) scanf("%d", &y), printf("%lld\n", query_path(x, y));
        if (op == 3) scanf("%lld", &z), modify(1, 1, n, dfn[x], dfn[x] + sz[x] - 1, z);
        if (op == 4) printf("%lld\n", getsum(1, 1, n, dfn[x], dfn[x] + sz[x] - 1));
    }
    return 0;
}