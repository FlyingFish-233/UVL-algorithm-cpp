// POJ2376 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 25000 + 10;

struct Array
{
    int l, r;
    bool operator < (const Array &cmp) const {
        if (l != cmp.l) return l < cmp.l;
        return r > cmp.r;
    }
};

int n, m;
Array a[NR];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a[i].l, &a[i].r);
    sort(a + 1, a + n + 1);
    int i = 1, ans = 0, now = 0;
    while (now < m) {
        int save = now;
        while (i <= n && a[i].l <= now + 1) save = max(save, a[i++].r);
        if (now == save) { ans = -1; break; }
        now = save, ans++;
    }
    printf("%d\n", ans);
    return 0;
}