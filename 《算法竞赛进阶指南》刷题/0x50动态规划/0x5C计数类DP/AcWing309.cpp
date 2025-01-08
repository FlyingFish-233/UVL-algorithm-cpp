# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 30;

int n;
long long c, f[NR][NR][2];
bool used[NR];

int main()
{
    f[1][1][0] = f[1][1][1] = 1;
    for (int i = 2; i <= 20; i++)
        for (int j = 1; j <= i; j++) {
            for (int p = j; p <= i - 1; p++)
                f[i][j][0] += f[i - 1][p][1];
            for (int p = 1; p <= j - 1; p++)
                f[i][j][1] += f[i - 1][p][0];
        }
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%lld", &n, &c);
        int last; bool up;
        for (int i = 1; i <= n; i++) {
            if (f[n][i][1] >= c) { last = i, up = true; break; }
            else c -= f[n][i][1];
            if (f[n][i][0] >= c) { last = i, up = false; break; }
            else c -= f[n][i][0];
        }
        memset(used, false, sizeof(used));
        used[last] = true, printf("%d", last);
        for (int i = 2; i <= n; i++) {
            int rank = 0; up ^= 1;
            for (int len = 1; len <= n; len++) if (!used[len]) {
                rank++;
                if ((!up && len < last) || (up && len > last)) {
                    if (f[n - i + 1][rank][up] >= c) { last = len; break; }
                    else c -= f[n - i + 1][rank][up];
                }
            }
            used[last] = true, printf(" %d", last);
        }
        puts("");
    }
    return 0;
}