# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e3 + 10;

int T, MaxP, W;
int AP[NR], BP[NR], AS[NR], BS[NR];
int f[NR][NR], save[NR], q[NR];

int v(int k, int w)
{
    return save[k] + k * w;
}

int main()
{
    scanf("%d%d%d", &T, &MaxP, &W);
    for (int i = 1; i <= T; i++)
        scanf("%d%d%d%d", &AP[i], &BP[i], &AS[i], &BS[i]);
    memset(f, -0x3f, sizeof(f)), f[0][0] = 0;
    memset(save, -0x3f, sizeof(save)), save[0] = 0;
    for (int i = 1; i <= T; i++) {
        int l = 1, r = 0;
        for (int j = 0; j <= MaxP; j++) {
            while (l <= r && q[l] < j - AS[i]) l++;
            while (l <= r && v(q[r], AP[i]) <= v(j, AP[i])) r--;
            q[++r] = j;
            f[i][j] = max(f[i][j], v(q[l], AP[i]) - j * AP[i]);
        }
        l = 1, r = 0;
        for (int j = MaxP; j >= 0; j--) {
            while (l <= r && q[l] > j + BS[i]) l++;
            while (l <= r && v(q[r], BP[i]) <= v(j, BP[i])) r--;
            q[++r] = j;
            f[i][j] = max(f[i][j], v(q[l], BP[i]) - j * BP[i]);
        }
        for (int j = 0; j <= MaxP; j++)
            f[i][j] = max(f[i][j], f[i - 1][j]);
        if (i > W) {
            for (int j = 0; j <= MaxP; j++)
                save[j] = max(save[j], f[i - W][j]);
        }
    }
    int ans = 0;
    for (int j = 0; j <= MaxP; j++)
        ans = max(ans, f[T][j]);
    printf("%d\n", ans);
    return 0;
}