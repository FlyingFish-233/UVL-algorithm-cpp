# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <stack>

using namespace std;

const int NR = 2e3 + 10;

struct Wedding
{
    int l, r, d;
};

int n;
Wedding a[NR];

bool check(int l1, int r1, int l2, int r2)
{
    if (l1 > l2) swap(l1, l2), swap(r1, r2);
    return r1 > l2;
}

vector<int> g[NR];

void addEdge(int x, int y)
{
    g[x].push_back(y);
}

int now, dfn[NR], low[NR];
bool ins[NR];
stack<int> s;

int tot, c[NR];

void tarjan(int x)
{
    dfn[x] = low[x] = ++now;
    ins[x] = true, s.push(x);
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i];
        if (dfn[y] == 0) tarjan(y), low[x] = min(low[x], low[y]);
        else if (ins[y]) low[x] = min(low[x], dfn[y]);
    }
    if (dfn[x] != low[x]) return;
    c[x] = ++tot;
    while (s.top() != x) {
        int y = s.top();
        c[y] = tot;
        ins[y] = false, s.pop();
    }
    ins[x] = false, s.pop();
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int h1, m1, h2, m2, d;
        scanf("%d:%d %d:%d %d", &h1, &m1, &h2, &m2, &d);
        a[i] = (Wedding) {h1 * 60 + m1, h2 * 60 + m2, d};
    }
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) {
            if (check(a[i].l, a[i].l + a[i].d, a[j].l, a[j].l + a[j].d)) addEdge(i, j + n), addEdge(j, i + n);
            if (check(a[i].l, a[i].l + a[i].d, a[j].r - a[j].d, a[j].r)) addEdge(i, j), addEdge(j + n, i + n);
            if (check(a[i].r - a[i].d, a[i].r, a[j].l, a[j].l + a[j].d)) addEdge(i + n, j + n), addEdge(j, i);
            if (check(a[i].r - a[i].d, a[i].r, a[j].r - a[j].d, a[j].r)) addEdge(i + n, j), addEdge(j + n, i);
        }
    for (int i = 1; i <= 2 * n; i++)
        if (dfn[i] == 0) tarjan(i);
    for (int i = 1; i <= n; i++)
        if (c[i] == c[i + n]) return printf("NO\n"), 0;
    printf("YES\n");
    for (int i = 1; i <= n; i++) {
        int L, R;
        if (c[i] < c[i + n]) L = a[i].l, R = a[i].l + a[i].d;
        else L = a[i].r - a[i].d, R = a[i].r;
        printf("%02d:%02d %02d:%02d\n", L / 60, L % 60, R / 60, R % 60);
    }
    return 0;
}