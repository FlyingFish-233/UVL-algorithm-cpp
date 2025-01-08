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

bool fermat(int x)
{
    if (x <= 2) return x == 2;
    for (int i = 1; i <= test_time; i++)
        if (qpow(rand() % (x - 2) + 2, x - 1, x) != 1) return false;
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
        cnt += flag[i] ^ fermat(i);
    printf("%d\n", cnt); // 1~n中测试错误的数据数量
    return 0;
}