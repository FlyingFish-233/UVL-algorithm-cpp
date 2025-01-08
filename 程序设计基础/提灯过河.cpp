# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <iostream>
 
using namespace std;

const int NR = 10;

int n, m;
int a[NR];
// n个人夜晚过河，只有一盏灯，窄桥一次过2个人，问过河的最少时间

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    int ans = 0;
    while (n >= 4) // n-1和n可以由1,2一起送，也可以由1单独送
        ans += min(a[1] + 2 * a[2] + a[n], 2 * a[1] + a[n - 1] + a[n]), n -= 2;
    if (n == 3) ans += a[1] + a[2] + a[3];
    if (n == 2) ans += a[2];
    if (n == 1) ans += a[1];
    printf("%d\n", ans);
    return 0;
}