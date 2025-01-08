# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <stack>
# include <vector>

using namespace std;

const int NR = 2e4 + 10, MR = 1e5 + 10;

struct Edge
{
    int to, next;
};

int n, m;
int gsz = 1, fte[NR];
Edge g[MR << 1];

void addEdge(int x, int y)
{
    g[++gsz] = (Edge) {y, fte[x]};
    fte[x] = gsz;
}

int now, root;
int dfn[NR], low[NR];
bool cut[NR];

int tot, all, c[NR];
stack<int> s;
vector<int> dcc[NR];

void tarjan(int x, int dad)
{
    dfn[x] = low[x] = ++now, s.push(x);
    if (x == root && fte[x] == 0) { dcc[++tot].push_back(x); return; }
    int tmp = 0;
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to, z;
        if (dfn[y] != 0) { low[x] = min(low[x], dfn[y]); continue; }
        tarjan(y, x), low[x] = min(low[x], low[y]);
        if (dfn[x] <= low[y]) {
            tmp++;
            if (x != root || tmp > 1) cut[x] = true;
            dcc[++tot].push_back(x);
            do {
                z = s.top(), s.pop();
                dcc[tot].push_back(z);
            } while (z != y);
        }
    }
}

vector<int> G[NR];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y; i <= m; i++)
        scanf("%d%d", &x, &y), addEdge(x, y), addEdge(y, x);
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0) tarjan(root = i, 0);
    all = tot;
    for (int i = 1; i <= n; i++)
        if (cut[i]) c[i] = ++all;
    for (int i = 1; i <= tot; i++)
        for (int j = 0; j < (int) dcc[i].size(); j++) {
            int x = dcc[i][j];
            if (cut[x]) G[c[x]].push_back(i), G[i].push_back(c[x]);
            else c[x] = i;
        }
    for (int i = 1; i <= n; i++)
        printf("%d ", c[i]);
    puts("");
    return 0;
}