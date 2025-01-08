// P4783 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 410;
const int mod = 1e9 + 7;

int n;
int mat[NR][NR << 1];

void exgcd(int a, int b, int &x, int &y)
{
    if (b == 0) x = 1, y = 0;
    else exgcd(b, a % b, y, x), y -= a / b * x;
}

int inv(int a)
{
    int x, y;
    exgcd(a, mod, x, y);
    return (x + mod) % mod;
}

bool Gause()
{
    for (int i = 1; i <= n; i++)
        mat[i][i + n] = 1;
    for (int i = 1; i <= n; i++) {
        int row = i;
        for (int j = i + 1; j <= n; j++)
            if (mat[j][i] > mat[row][i]) row = j;
        if (mat[row][i] == 0) return false;
        swap(mat[row], mat[i]);
        int t = inv(mat[i][i]);
        for (int j = 1; j <= n; j++) if (i != j) {
            int rate = 1ll * mat[j][i] * t % mod;
            for (int k = i; k <= (n << 1); k++)
                mat[j][k] = (mat[j][k] - 1ll * mat[i][k] * rate % mod + mod) % mod;
        }
        for (int j = 1; j <= (n << 1); j++)
            mat[i][j] = 1ll * mat[i][j] * t % mod;
    }
    return true;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &mat[i][j]);
    if (!Gause()) return printf("No Solution\n"), 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            printf("%d ", mat[i][j + n]);
        puts("");
    }
    return 0;
}