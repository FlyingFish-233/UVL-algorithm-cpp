// AcWing219 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 210;

int n, m;
int sg[NR][NR];

// SG(x) = mex({SG(y1), SG(y2), ... , SG(yk)})
// SG(G) = SG(G1) ^ SG(G2) ^ ... ^ SG(Gm), SG(Gi) = SG(si)
int SG(int x, int y)
{
    if (sg[x][y] != -1) return sg[x][y];
    bool flag[NR];
    memset(flag, false, sizeof(flag));
    for (int i = 2; i <= x - 2; i++)
        flag[SG(i, y) ^ SG(x - i, y)] = true;
    for (int i = 2; i <= y - 2; i++)
        flag[(SG(x, i) ^ SG(x, y - i))] = true;
    int res = 0;
    while (flag[res]) res++;
    return sg[x][y] = res;
}

int main()
{
    memset(sg, -1, sizeof(sg));
    sg[2][2] = sg[2][3] = sg[3][2] = sg[3][3] = 0;
    while (scanf("%d%d", &n, &m) != EOF) {
        if (n == 1 && m == 1) { printf("LOSE\n"); continue; }
        if (n == 1 || m == 1) { printf("WIN\n"); continue; }
        if (SG(n, m) > 0) printf("WIN\n");
        else printf("LOSE\n");
    }
    return 0;
}