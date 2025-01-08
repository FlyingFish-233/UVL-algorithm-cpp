# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <stack>

using namespace std;

const int NR = 110;

int n;
vector<int> g[NR];
int now, dfn[NR], low[NR];
bool ins[NR];
stack<int> s;

int tot, c[NR];
int in[NR], out[NR];

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
    while (s.top() != x)
        c[s.top()] = tot, ins[s.top()] = false, s.pop();
    ins[x] = false, s.pop();
}

int main()
{
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++)
        while (scanf("%d", &x) && x)
            g[i].push_back(x);
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0) tarjan(i);
    for (int x = 1; x <= n; x++)
        for (int i = 0; i < (int) g[x].size(); i++) {
            int y = g[x][i];
            if (c[x] != c[y]) out[c[x]]++, in[c[y]]++;
        }
    int cnt1 = 0, cnt2 = 0;
    for (int i = 1; i <= tot; i++)
        cnt1 += (in[i] == 0), cnt2 += (out[i] == 0);
    printf("%d\n", cnt1);
    printf("%d\n", (tot == 1) ? 0 : max(cnt1, cnt2));
    return 0;
}