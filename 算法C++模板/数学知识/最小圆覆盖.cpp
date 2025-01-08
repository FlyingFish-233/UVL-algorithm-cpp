// P1742 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;
const double eps = 1e-10;

struct Point
{
    double x, y;
    Point operator + (const Point &p) const {
        return {x + p.x, y + p.y};
    }
    Point operator - (const Point &p) const {
        return {x - p.x, y - p.y};
    }
    Point operator * (const double &k) const {
        return {k * x, k * y};
    }
    Point operator / (const double &k) const {
        return {x / k, y / k};
    }
    Point rotate_90() {
        return {-y, x};
    }
};

double cross(Point a, Point b)
{
    return a.x * b.y - b.x * a.y;
}

double dis(Point a, Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool in_circle(Point o, double r, Point a)
{
    return dis(a, o) <= r + eps;
}

Point get_intersection(Point a, Point v1, Point b, Point v2)
{
    return a + v1 * (cross(b - a, v2) / cross(v1, v2));
}

Point get_circumcenter(Point a, Point b, Point c)
{
    return get_intersection((a + b) / 2, (b - a).rotate_90(), (b + c) / 2, (c - b).rotate_90());
}

int n;
Point p[NR];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &p[i].x, &p[i].y);
    random_shuffle(p + 1, p + n + 1);
    Point ansp = p[1]; double ansr = 0;
    for (int i = 2; i <= n; i++) if (!in_circle(ansp, ansr, p[i])) {
        ansp = p[i], ansr = 0;
        for (int j = 1; j <= i - 1; j++) if (!in_circle(ansp, ansr, p[j])) {
            ansp = (p[i] + p[j]) / 2, ansr = dis(p[i], p[j]) / 2;
            for (int k = 1; k <= j - 1; k++) if (!in_circle(ansp, ansr, p[k]))
                ansp = get_circumcenter(p[i], p[j], p[k]), ansr = dis(p[i], ansp);
        }
    }
    printf("%.10f\n", ansr);
    printf("%.10f %.10f\n", ansp.x, ansp.y);
    return 0;
}