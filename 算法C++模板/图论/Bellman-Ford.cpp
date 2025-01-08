// P3371 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <climits>

using namespace std;

const int NR = 1e4 + 10, MR = 5e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m, s0;
int u[MR], v[MR], w[MR];
int dis[NR];

void bellman_ford(int s)
{
    memset(dis, 0x3f, sizeof(dis)), dis[s] = 0;
    for (int i = 1; i <= n - 1; i++) {
        bool flag = false;
        for (int j = 1; j <= m; j++)
            if (dis[v[j]] > dis[u[j]] + w[j])
                dis[v[j]] = dis[u[j]] + w[j], flag = true;
        if (!flag) break;
    }
}

int main()
{
    scanf("%d%d%d", &n, &m, &s0);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &u[i], &v[i], &w[i]);
    bellman_ford(s0);
    for (int i = 1; i <= n; i++)
        printf("%d ", (dis[i] == INF) ? INT_MAX : dis[i]);
    puts("");
    return 0;
}