// P3386 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 510;

int n, m, e;
vector<int> g[NR];

bool vis[NR];
int opp[NR];

// 二分图的一组匹配是最大匹配 <=> 图中不存在增广路
bool find(int x)
{
    if (vis[x]) return false;
    vis[x] = true;
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i];
        if (opp[y] == 0 || find(opp[y]))
            { opp[y] = x; return true; }
    }
    return false;
}

/*
二分图最大匹配的模型有两个要素: 
(0要素)节点能分成独立的两个集合, 每个集合内部有0条边
(1要素)每个节点只能与1条匹配边相连
*/
int main()
{
    scanf("%d%d%d", &n, &m, &e);
    for (int i = 1, x, y; i <= e; i++)
        scanf("%d%d", &x, &y), g[x].push_back(y);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        memset(vis, false, sizeof(vis));
        ans += find(i);
    }
    printf("%d\n", ans);
    return 0;
}