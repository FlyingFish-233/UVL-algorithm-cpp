// P5443 (O2 -> 100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 1e5 + 10;

struct Edge
{
    int id, u, v, w;
    bool operator < (const Edge &cmp) const {
        return w > cmp.w;
    }
};

struct Ope
{
    int t, x, w;
    bool operator < (const Ope &cmp) const {
        return w > cmp.w;
    }
};

int n, m, q;
Edge g[NR];

int fa[NR], sz[NR];
int top, st[NR][2];

int find(int x)
{
    if (fa[x] == x) return x;
    return find(fa[x]);
}

void merge(int x, int y)
{
    x = find(x), y = find(y);
    if (x == y) return;
    if (sz[x] > sz[y]) swap(x, y);
    fa[x] = y, sz[y] += sz[x];
    st[++top][0] = x, st[top][1] = y;
}

void cancel()
{
    fa[st[top][0]] = st[top][0];
    sz[st[top][1]] -= sz[st[top][0]];
    top--;
}

vector<Ope> M, Q;
int rk[NR], change_w[NR];
int ans[NR];

void solve()
{
    sort(g + 1, g + m + 1);
    for (int i = 1; i <= m; i++)
        rk[g[i].id] = i;
    for (int i = 0; i < (int) M.size(); i++)
        change_w[M[i].x] = -1;
    top = 0;
    for (int i = 1; i <= n; i++)
        fa[i] = i, sz[i] = 1;
    sort(Q.begin(), Q.end());
    for (int i = 0, j = 0; i < (int) Q.size(); i++) {
        while (j + 1 <= m && g[j + 1].w >= Q[i].w) {
            j++;
            if (change_w[g[j].id] == 0) merge(g[j].u, g[j].v);
        }
        int save = top;
        for (int k = 0; k < (int) M.size(); k++)
            change_w[M[k].x] = g[rk[M[k].x]].w;
        for (int k = 0; k < (int) M.size() && M[k].t < Q[i].t; k++)
            change_w[M[k].x] = M[k].w;
        for (int k = 0; k < (int) M.size(); k++)
            if (change_w[M[k].x] >= Q[i].w) merge(g[rk[M[k].x]].u, g[rk[M[k].x]].v);
        ans[Q[i].t] = sz[find(Q[i].x)];
        while (top != save) cancel();
    }
    for (int i = 0; i < (int) M.size(); i++)
        change_w[M[i].x] = 0, g[rk[M[i].x]].w = M[i].w;
    M.clear(), Q.clear();
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &g[i].u, &g[i].v, &g[i].w), g[i].id = i;
    scanf("%d", &q);
    int SZ = sqrt(q);
    for (int i = 1; i <= q; i++) {
        int op, x, w;
        scanf("%d%d%d", &op, &x, &w);
        if (op == 1) M.push_back((Ope) {i, x, w});
        if (op == 2) Q.push_back((Ope) {i, x, w});
        if (i % SZ == 0) solve();
    }
    if (q % SZ > 0) solve();
    for (int i = 1; i <= q; i++)
        if (ans[i] > 0) printf("%d\n", ans[i]);
    return 0;
}