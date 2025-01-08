// P3385 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e3 + 10, MR = 6e3 + 10;

int n, m;
int u[MR], v[MR], w[MR];
int dis[NR];

bool bellman_ford(int s)
{
    bool flag = false;
    for (int i = 1; i <= m; i++)
        if (u[i] == s) { flag = true; break; }
    if (!flag) return true;

    memset(dis, 0x3f, sizeof(dis)), dis[s] = 0;
    for (int i = 1; i <= n - 1; i++) {
        flag = false;
        for (int j = 1; j <= m; j++)
            if (dis[v[j]] > dis[u[j]] + w[j])
                dis[v[j]] = dis[u[j]] + w[j], flag = true;
        if (!flag) return true;
    }
    return false;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1, save = m; i <= save; i++) {
            scanf("%d%d%d", &u[i], &v[i], &w[i]);
            if (w[i] >= 0) u[++m] = v[i], v[m] = u[i], w[m] = w[i];
        }
        if (!bellman_ford(1)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}