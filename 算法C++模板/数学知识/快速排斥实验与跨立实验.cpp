// POJ1410 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const double eps = 1e-8;

struct Point
{
    double x, y;
};

double cross(Point a1, Point a2, Point b1, Point b2)
{
    return (a2.x - a1.x) * (b2.y - b1.y) - (a2.y - a1.y) * (b2.x - b1.x);
}

bool check(Point a1, Point a2, Point b1, Point b2)
{
    if (min(a1.x, a2.x) > max(b1.x, b2.x) || min(b1.x, b2.x) > max(a1.x, a2.x)
        || min(a1.y, a2.y) > max(b1.y, b2.y) || min(b1.y, b2.y) > max(a1.y, a2.y))
        return false;
    return cross(a1, a2, a1, b1) * cross(a1, a2, a1, b2) <= eps
        && cross(b1, b2, b1, a1) * cross(b1, b2, b1, a2) <= eps;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        Point a, b; double l, r, u, d;
        scanf("%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y);
        scanf("%lf%lf%lf%lf", &l, &u, &r, &d);
        if (l > r) swap(l, r);
        if (u < d) swap(u, d);

        if (check(a, b, {l, u}, {l, d}) || check(a, b, {r, u}, {r, d})
            || check(a, b, {l, u}, {r, u}) || check(a, b, {l, d}, {r, d})
            || (l <= a.x && a.x <= r && d <= a.y && a.y <= u)
            || (l <= b.x && b.x <= r && d <= b.y && b.y <= u))
            printf("T\n");
        else printf("F\n");
    }
    return 0;
}