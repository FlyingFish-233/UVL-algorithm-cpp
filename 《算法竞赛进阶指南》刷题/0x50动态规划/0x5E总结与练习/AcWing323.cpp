# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 1500 + 10;

int n, root;
vector<int> g[NR];
bool flag[NR];
int f[NR][2];

void dfs(int x)
{
    f[x][0] = 0, f[x][1] = 1;
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i];
        dfs(y);
        f[x][0] += f[y][1];
        f[x][1] += min(f[y][0], f[y][1]);
    }
}

int main()
{
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; i++) g[i].clear();
        memset(flag, false, sizeof(flag));
        for (int i = 1, k, x; i <= n; i++) {
            scanf("%d:(%d)", &x, &k), ++x;
            for (int j = 1, y; j <= k; j++)
                scanf("%d", &y), g[x].push_back(++y), flag[y] = true;
        }
        for (int i = 1; i <= n; i++)
            if (!flag[i]) { root = i; break; }
        dfs(root);
        printf("%d\n", min(f[root][0], f[root][1]));
    }
    return 0;
}