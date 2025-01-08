# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <stack>

using namespace std;

const int NR = 4e3 + 10;

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
    for (int i = 1, k; i <= n; i++) {
        scanf("%d", &k);
        for (int j = 1, x; j <= k; j++)
            scanf("%d", &x), g[i].push_back(x + n);
    }
    for (int i = 1, x; i <= n; i++)
        scanf("%d", &x), g[x + n].push_back(i);
    for (int i = 1; i <= 2 * n; i++)
        if (dfn[i] == 0) tarjan(i);
    vector<int> ans;
    for (int x = 1; x <= n; x++) {
        ans.clear();
        for (int i = 0; i < (int) g[x].size(); i++) {
            int y = g[x][i] - n;
            if (c[x] == c[y]) ans.push_back(y);
        }
        sort(ans.begin(), ans.end());
        printf("%d ", ans.size());
        for (int i = 0; i < (int) ans.size(); i++)
            printf("%d ", ans[i]);
        puts("");
    }
    return 0;
}