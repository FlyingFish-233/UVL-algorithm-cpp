# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 110;

int n, m;
int deg[NR];
vector< pair<int, int> > g[NR];
double mat[NR][NR];

void Gauss()
{
    for (int i = 1; i <= n; i++) {
        int row = i;
        for (int j = i + 1; j <= n; j++)
            if (fabs(mat[j][i]) > fabs(mat[row][i])) row = j;
        if (fabs(mat[row][i]) < 1e-8) return;
        swap(mat[row], mat[i]);
        for (int j = 1; j <= n; j++) if (j != i) {
            double rate = mat[j][i] / mat[i][i];
            for (int k = i; k <= n + 1; k++)
                mat[j][k] -= rate * mat[i][k];
        }
    }
    for (int i = 1; i <= n; i++)
        mat[i][n + 1] /= mat[i][i];
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y, w; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &w);
        if (x == y) g[x].push_back({y, w}), deg[x]++;
        else g[x].push_back({y, w}), g[y].push_back({x, w}), deg[x]++, deg[y]++;
    }
    double ans = 0;
    for (int k = 30; k >= 0; k--) {
        memset(mat, 0, sizeof(mat));
        for (int x = 1; x < n; x++) {
            mat[x][x] = -deg[x];
            for (int i = 0; i < (int) g[x].size(); i++) {
                int y = g[x][i].first, w = g[x][i].second;
                if (w >> k & 1) mat[x][y] -= 1, mat[x][n + 1] -= 1;
                else mat[x][y] += 1;
            }
        }
        mat[n][n] = 1, Gauss();
        ans += (1 << k) * mat[1][n + 1];
    }
    printf("%.3f\n", ans);
    return 0;
}