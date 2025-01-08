# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e8 + 10;
const int test_time = 10;

int n;
bool flag[NR];

int qpow(int a, int b, int mod)
{
    int sum = 1;
    for (int i = b; i; i >>= 1, a = 1ll * a * a % mod)
        if (i & 1) sum = 1ll * sum * a % mod;
    return sum;
}

bool millerRabin(int x)
{
    if (x <= 2 || x % 2 == 0) return x == 2;
    int a = x - 1, b = 0;
    while (a % 2 == 0) a /= 2, b++; // x - 1 = a * 2^b
    for (int i = 1; i <= test_time; i++) {
        int y = qpow(rand() % (x - 2) + 2, a, x), j;
        if (y == 1) continue;
        for (j = 0; j < b && y != x - 1; j++)
            y = 1ll * y * y % x;
        if (j == b) return false;
    }
    return true;
}

int main()
{
    scanf("%d", &n);
    memset(flag, true, sizeof(flag));
    flag[1] = false;
    for (int i = 2; i <= n; i++)
        if (flag[i]) {
            for (int j = i; i * j <= n; j++)
                flag[i * j] = false;
        }
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        cnt += flag[i] ^ millerRabin(i);
    printf("%d\n", cnt); // 1~n中测试错误的数据数量
    return 0;
}