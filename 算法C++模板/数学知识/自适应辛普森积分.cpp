// P4525 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define mid ((l + r) / 2)

using namespace std;

double a, b, c, d;

double f(double x)
{
    return (c * x + d) / (a * x + b);
}

double simpson(double l, double r)
{
    return (r - l) * (f(l) + f(r) + 4 * f(mid)) / 6;
}

double dfs(double l, double r, double eps, double t)
{
    double tl = simpson(l, mid), tr = simpson(mid, r);
    if (abs(tl + tr - t) < 15 * eps) return tl + tr + (tl + tr - t) / 15;
    return dfs(l, mid, eps / 2, tl) + dfs(mid, r, eps / 2, tr);
}

int main()
{
    double l, r;
    scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &l, &r);
    printf("%.6f\n", dfs(l, r, 1e-6, simpson(l, r)));
    return 0;
}