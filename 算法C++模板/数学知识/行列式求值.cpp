// P7112 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 610;

int n, p;
int mat[NR][NR];

int det()
{
    int ans = 1; bool flag = false;
    for (int i = 1; i <= n; i++) {
        int row = i;
        for (int j = i + 1; j <= n; j++)
            if (mat[j][i] > mat[row][i]) row = j;
        if (mat[row][i] == 0) return 0;
        if (i != row) swap(mat[row], mat[i]), flag ^= 1;
        for (int j = i + 1; j <= n; j++) {
            if (mat[j][i] > mat[i][i]) swap(mat[i], mat[j]), flag ^= 1;
            while (mat[j][i]) {
                int rate = mat[i][i] / mat[j][i];
                for (int k = i; k <= n; k++)
                    mat[i][k] = (mat[i][k] - 1ll * mat[j][k] * rate % p + p) % p;
                swap(mat[i], mat[j]), flag ^= 1;
            }
        }
        ans = 1ll * ans * mat[i][i] % p;
    }
    if (flag) ans = (p - ans) % p;
    return ans;
}

int main()
{
    scanf("%d%d", &n, &p);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &mat[i][j]), mat[i][j] %= p;
    printf("%d\n", det());
    return 0;
}