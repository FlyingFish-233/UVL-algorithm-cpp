// P4716 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110, MR = 1e4 + 10;
const int INF = 0x3f3f3f3f;

int n, m, root;
int u[MR], v[MR], w[MR];

int inw[NR], pre[NR];
int tot, flag[NR], c[NR];

int zhuliu(int rt)
{
    int ans = 0;
    while (true) {
        memset(inw, 0x3f, sizeof(inw));
        for (int i = 1; i <= m; i++)
            if (u[i] != v[i] && w[i] < inw[v[i]]) inw[v[i]] = w[i], pre[v[i]] = u[i];
        for (int i = 1; i <= n; i++)
            if (i != rt && inw[i] == INF) return -1;
        memset(flag, 0, sizeof(flag));
        memset(c, 0, sizeof(c)), tot = 0;
        for (int i = 1; i <= n; i++) if (i != rt) {
            int x = i; ans += inw[i];
            while (flag[x] != i && c[x] == 0 && x != rt)
                flag[x] = i, x = pre[x];
            if (c[x] == 0 && x != rt) {
                c[x] = ++tot;
                for (int j = pre[x]; j != x; j = pre[j])
                    c[j] = tot;
            }
        }
        if (tot == 0) break;
        for (int i = 1; i <= n; i++)
            if (c[i] == 0) c[i] = ++tot;
        for (int i = 1; i <= m; i++) {
            if (c[u[i]] != c[v[i]]) w[i] -= inw[v[i]];
            u[i] = c[u[i]], v[i] = c[v[i]];
        }
        rt = c[rt], n = tot;
    }
    return ans;
}

int main()
{
    scanf("%d%d%d", &n, &m, &root);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &u[i], &v[i], &w[i]);
    printf("%d\n", zhuliu(root));
    return 0;
}