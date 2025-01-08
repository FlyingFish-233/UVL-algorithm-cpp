// AcWing257 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 110;

int n, m;
bool know[NR][NR];
vector<int> g[NR];
int c[NR];

int tot;
vector<int> block[NR][2];

bool dfs(int x, int color)
{
    c[x] = color, block[tot][color - 1].push_back(x);
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i];
        if (c[y] == 3 - color) continue;
        if (c[y] == color || !dfs(y, 3 - color)) return false;
    }
    return true;
}

int d[NR];
bool f[NR][NR << 1], choice[NR][NR << 1];

int cnt;
bool ans[NR];

void mark(int i, int j)
{
    if (i == 0) return;
    bool t = choice[i][j];
    mark(i - 1, j + (t ? 1 : -1) * d[i]);
    for (int k = 0; k < (int) block[i][t].size(); k++)
        ans[block[i][t][k]] = true, cnt++;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1, j; i <= n; i++)
        while (scanf("%d", &j) && j) know[i][j] = true;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j && !know[i][j]) g[i].push_back(j), g[j].push_back(i);
    for (int i = 1; i <= n; i++) if (c[i] == 0) {
        ++tot;
        if (!dfs(i, 1)) return printf("No solution\n"), 0;
    }

    for (int i = 1; i <= tot; i++)
        d[i] = block[i][0].size() - block[i][1].size();
    f[0][100 + 0] = true;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= 200; j++) {
            if (j - d[i] >= 0 && j - d[i] <= 200 && f[i - 1][j - d[i]])
                f[i][j] = true, choice[i][j] = 0;
            if (j + d[i] >= 0 && j + d[i] <= 200 && f[i - 1][j + d[i]])
                f[i][j] = true, choice[i][j] = 1;
        }
    int save;
    for (int i = 0; i <= 100; i++) {
        if (f[n][100 + i]) { save = 100 + i; break; }
        if (f[n][100 - i]) { save = 100 - i; break; }
    }
    mark(n, save);

    printf("%d ", cnt);
    for (int i = 1; i <= n; i++)
        if (ans[i]) printf("%d ", i);
    puts("");

    printf("%d ", n - cnt);
    for (int i = 1; i <= n; i++)
        if (!ans[i]) printf("%d ", i);
    puts("");
    return 0;
}