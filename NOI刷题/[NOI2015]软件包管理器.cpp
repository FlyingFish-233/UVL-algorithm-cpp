// P2146 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define ls (rt << 1)
# define rs (rt << 1 | 1)
# define mid ((l + r) >> 1)

using namespace std;

const int NR = 1e5 + 10;

int n;

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

int sum[NR << 2], tag[NR << 2];

void pushDown(int rt, int l, int r)
{
    if (tag[rt] == 0) return;
    sum[ls] = (tag[rt] == 1) ? (mid - l + 1) : 0, tag[ls] = tag[rt];
    sum[rs] = (tag[rt] == 1) ? (r - mid) : 0, tag[rs] = tag[rt];
    tag[rt] = 0;
}

void pushUp(int rt)
{
    sum[rt] = sum[ls] + sum[rs];
}

void modify(int rt, int l, int r, int l0, int r0, int v)
{
    if (l0 <= l && r <= r0) { sum[rt] = (v == 1) ? (r - l + 1) : 0, tag[rt] = v; return; }
    pushDown(rt, l, r);
    if (l0 <= mid) modify(ls, l, mid, l0, r0, v);
    if (mid < r0) modify(rs, mid + 1, r, l0, r0, v);
    pushUp(rt);
}

int getsum(int rt, int l, int r, int l0, int r0)
{
    if (l0 <= l && r <= r0) return sum[rt];
    pushDown(rt, l, r);
    int ans = 0;
    if (l0 <= mid) ans += getsum(ls, l, mid, l0, r0);
    if (mid < r0) ans += getsum(rs, mid + 1, r, l0, r0);
    pushUp(rt);
    return ans;
}

void modify_path(int x, int y, int v)
{
    while (top[x] != top[y]) {
        if (dep[top[x]] > dep[top[y]]) swap(x, y);
        modify(1, 1, n, dfn[top[y]], dfn[y], v);
        y = fa[top[y]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    modify(1, 1, n, dfn[x], dfn[y], v);
}

int query_path(int x, int y)
{
    int ans = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] > dep[top[y]]) swap(x, y);
        ans += getsum(1, 1, n, dfn[top[y]], dfn[y]);
        y = fa[top[y]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    ans += getsum(1, 1, n, dfn[x], dfn[y]);
    return ans;
}

int main()
{
    scanf("%d", &n);
    for (int i = 2, x; i <= n; i++)
        scanf("%d", &x), addEdge(++x, i);
    dfs1(1, 0), dfs2(1, 1);

    int T;
    scanf("%d", &T);
    while (T--) {
        char op[10]; int x;
        scanf("%s%d", op, &x), ++x;
        if (op[0] == 'i') {
            printf("%d\n", dep[x] - query_path(1, x));
            modify_path(1, x, 1);
        }
        if (op[0] == 'u') {
            printf("%d\n", getsum(1, 1, n, dfn[x], dfn[x] + sz[x] - 1));
            modify(1, 1, n, dfn[x], dfn[x] + sz[x] - 1, -1);
        }
    }
    return 0;
}