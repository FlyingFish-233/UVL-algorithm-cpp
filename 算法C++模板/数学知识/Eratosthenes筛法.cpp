# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e8 + 10;

int n, m;
bool flag[NR];
int p[NR];

int main()
{
    scanf("%d", &n);
    memset(flag, true, sizeof(flag));
    flag[1] = false;
    for (int i = 2; i <= n; i++)
        if (flag[i]) {
            p[++m] = i;
            for (int j = i; i * j <= n; j++)
                flag[i * j] = false;
        }
    for (int i = 1; i <= m; i++)
        printf("%d ", p[i]);
    puts("");
    return 0;
}