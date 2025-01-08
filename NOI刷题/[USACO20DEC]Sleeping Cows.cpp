// P7155 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 3e3 + 10;
const int PR = 1e9 + 7;

struct Array
{
    int x, t;
    bool operator < (const Array &cmp) const {
        if (x != cmp.x) return x < cmp.x;
        return t < cmp.t;
    }
};

int n;
Array a[NR << 1];
int f[NR << 1][NR][2]; // f[i][j][0/1]表示括号序列1~i,有j个'('等待匹配,是否出现了不匹配的'('
// 括号序列满足极大匹配 <=> 第一个未匹配的'('的右边没有未匹配的')'

int main()
{
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++)
        scanf("%d", &x), a[i] = (Array) {x, 0};
    for (int i = 1, x; i <= n; i++)
        scanf("%d", &x), a[i + n] = (Array) {x, 1};
    sort(a + 1, a + 2 * n + 1);
    f[0][0][0] = 1;
    for (int i = 1; i <= 2 * n; i++)
        if (a[i].t == 0)
            for (int j = 0; j <= n; j++) {
                (f[i][j + 1][0] += f[i - 1][j][0]) %= PR;
                (f[i][j][1] += f[i - 1][j][0]) %= PR;
                (f[i][j + 1][1] += f[i - 1][j][1]) %= PR;
                (f[i][j][1] += f[i - 1][j][1]) %= PR;
            }
        else
            for (int j = 0; j <= n; j++) {
                if (j >= 1) (f[i][j - 1][0] += 1ll * j * f[i - 1][j][0] % PR) %= PR;
                (f[i][j][0] += f[i - 1][j][0]) %= PR;
                if (j >= 1) (f[i][j - 1][1] += 1ll * j * f[i - 1][j][1] % PR) %= PR;
            }
    printf("%d\n", (f[2 * n][0][0] + f[2 * n][0][1]) % PR);
    return 0;
}