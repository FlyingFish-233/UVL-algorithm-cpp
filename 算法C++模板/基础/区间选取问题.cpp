// P1803 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e6 + 10;

struct Array
{
    int l, r;
    bool operator < (const Array &cmp) const {
        return r < cmp.r;
    }
};

int n;
Array a[NR];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a[i].l, &a[i].r);
    sort(a + 1, a + n + 1);
    int ans = 1, now = a[1].r;
    for (int i = 2; i <= n; i++)
        if (a[i].l >= now) now = a[i].r, ans++;
    printf("%d\n", ans);
    return 0;
}