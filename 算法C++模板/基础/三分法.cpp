// P3382 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 20;
const double eps = 1e-7;

int n;
double a[NR];

double f(double x)
{
    double sum = 0;
    for (int i = n; i >= 0; i--)
        sum = sum * x + a[i];
    return sum;
}

int main()
{
    double l, r;
    scanf("%d%lf%lf", &n, &l, &r);
    for (int i = n; i >= 0; i--)
        scanf("%lf", &a[i]);
    while (r - l >= eps) {
        double lmid = (l + r) / 2;
        double rmid = (lmid + r) / 2;
        if (f(lmid) > f(rmid)) r = rmid;
        else l = lmid;
    }
    printf("%.5f\n", r);
    return 0;
}