// POJ1328 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1000 + 10;

struct Node
{
    double l, r;

    bool operator < (const Node &cmp) const {
        return r < cmp.r;
    }
};

int n, d;
Node a[NR];

int main()
{
    int T = 0;
    while (scanf("%d%d", &n, &d) && !(n == 0 && d == 0)) {
        bool flag = true;
        for (int i = 1; i <= n; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            if (y > d) flag = false;
            double tmp = sqrt(d * d - y * y);
            a[i] = (Node) {x - tmp, x + tmp};
        }
        if (!flag) { printf("Case %d: %d\n", ++T, -1); continue; }
        sort(a + 1, a + n + 1);
        int ans = 1;
        double now = a[1].r;
        for (int i = 2; i <= n; i++)
            if (now < a[i].l) ans++, now = a[i].r;
        printf("Case %d: %d\n", ++T, ans);
    }
    return 0;
}