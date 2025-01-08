// POJ2976 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e3 + 10;
const double eps = 1e-5;

int n, k;
int a[NR], b[NR];
double t[NR];

bool check(double mid)
{
    for (int i = 1; i <= n; i++)
        t[i] = b[i] * mid - a[i];
    sort(t + 1, t + n + 1);
    double sum = 0;
    for (int i = 1; i <= n - k; i++)
        sum += t[i];
    return sum >= 0;
}

int main()
{
    while (scanf("%d%d", &n, &k) && !(n == 0 && k == 0)) {
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        for (int i = 1; i <= n; i++)
            scanf("%d", &b[i]);
        double l = 0, r = 1, ans = 1;
        while (r - l > eps) {
            double mid = (l + r) / 2;
            if (check(mid)) ans = r = mid;
            else l = mid;
        }
        printf("%.0f\n", 100 * ans);
    }
    return 0;
}