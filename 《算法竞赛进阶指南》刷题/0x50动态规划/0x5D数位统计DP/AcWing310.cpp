# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int n, m;
long long f[21][4];

int main()
{
    f[0][0] = 1;
    for (int i = 1; i <= 20; i++) {
        for (int j = 0; j <= 3; j++) {
            if (j >= 1) f[i][j] += f[i - 1][j - 1];
            if (j <= 2) f[i][0] += 9 * f[i - 1][j];
        }
        f[i][3] += 10 * f[i - 1][3];
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (m = 3; f[m][3] < n; m++);
        for (int i = m, k = 0; i >= 1; i--)
            for (int j = 0; j <= 9; j++) {
                long long cnt = f[i - 1][3];
                if (j == 6 || k == 3)
                    for (int l = max(3 - k - (j == 6), 0); l <= 2; l++)
                        cnt += f[i - 1][l];
                if (n <= cnt) {
                    if (k < 3) k = (j == 6) ? k + 1 : 0;
                    printf("%d", j);
                    break;
                }
                else n -= cnt;
            }
        puts("");
    }
    return 0;
}