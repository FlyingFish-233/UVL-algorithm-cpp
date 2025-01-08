# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <stack>
# include <queue>

using namespace std;

const int NR = 2e3 + 10;

int n, m;
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
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int a, b, c; char str[5];
        scanf("%d%d%d%s", &a, &b, &c, &str), a++, b++;
        if (str[0] == 'A' && c == 0) addEdge(a + n, b), addEdge(b + n, a);
        if (str[0] == 'A' && c == 1) addEdge(a, a + n), addEdge(b, b + n);
        if (str[0] == 'O' && c == 0) addEdge(a + n, a), addEdge(b + n, b);
        if (str[0] == 'O' && c == 1) addEdge(a, b + n), addEdge(b, a + n);
        if (str[0] == 'X' && c == 0) addEdge(a, b), addEdge(b, a), addEdge(a + n, b + n), addEdge(b + n, a + n);
        if (str[0] == 'X' && c == 1) addEdge(a, b + n), addEdge(b, a + n), addEdge(a + n, b), addEdge(b + n, a);
    }
    for (int i = 1; i <= 2 * n; i++)
        if (dfn[i] == 0) tarjan(i);
    for (int i = 1; i <= n; i++)
        if (c[i] == c[i + n]) return printf("NO\n"), 0;
    printf("YES\n");
    return 0;
}