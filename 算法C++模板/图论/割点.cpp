// P3388 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 1e5 + 10;

int n, m;
vector<int> g[NR];

int now, root;
int dfn[NR], low[NR];
bool cut[NR];

// x为割点 <=> 存在y使dfn[x]<=low[y](x=root时需要两个y)
void tarjan(int x)
{
    dfn[x] = low[x] = ++now;
    int tmp = 0;
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i];
        if (dfn[y] != 0) { low[x] = min(low[x], dfn[y]); continue; }
        tarjan(y), low[x] = min(low[x], low[y]);
        if (dfn[x] <= low[y]) {
            tmp++;
            if (x != root || tmp > 1) cut[x] = true;
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y; i <= m; i++)
        scanf("%d%d", &x, &y), g[x].push_back(y), g[y].push_back(x);
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0) tarjan(root = i);
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (cut[i]) cnt++;
    printf("%d\n", cnt);
    for (int i = 1; i <= n; i++)
        if (cut[i]) printf("%d ", i);
    puts("");
    return 0;
}