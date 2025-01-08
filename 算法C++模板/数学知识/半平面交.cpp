// P4196 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e3 + 10;
const double eps = 1e-7;

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
};

double cross(Point a, Point b)
{
    return a.x * b.y - b.x * a.y;
}

Point its(Point a, Point v1, Point b, Point v2)
{
    return a + v1 * (cross(b - a, v2) / cross(v1, v2));
}

struct Edge
{
    Point u, v; double angle;
    Edge() {}
    Edge(Point u0, Point v0) { u = u0, v = v0, angle = atan2((v - u).y, (v - u).x); }
    bool operator < (const Edge &cmp) const {
        if (fabs(angle - cmp.angle) <= eps) return cross(cmp.v - cmp.u, u - cmp.u) > 0;
        return angle < cmp.angle;
    }
};

int n;
Edge g[NR];

int tot;
Edge q[NR];
Point ans_p[NR];

void half_planes()
{
    sort(g + 1, g + n + 1);
    int l = 1, r = 0; q[++r] = g[1];
    for (int i = 2; i <= n; i++) if (fabs(g[i].angle - g[i - 1].angle) > eps) {
        while (r - l >= 1 && cross(g[i].v-g[i].u, its(q[r].u, q[r].v-q[r].u, q[r-1].u, q[r-1].v-q[r-1].u) - g[i].u) < 0) r--;
        while (r - l >= 1 && cross(g[i].v-g[i].u, its(q[l].u, q[l].v-q[l].u, q[l+1].u, q[l+1].v-q[l+1].u) - g[i].u) < 0) l++;
        q[++r] = g[i];
    }
    while (r - l >= 1 && cross(g[l].v-g[l].u, its(q[r].u, q[r].v-q[r].u, q[r-1].u, q[r-1].v-q[r-1].u) - g[l].u) < 0) r--;
    tot = r - l + 1;
    for (int i = l; i < r; i++)
        ans_p[i - l + 1] = its(q[i].u, q[i].v-q[i].u, q[i+1].u, q[i+1].v-q[i+1].u);
    if (r - l >= 1) ans_p[tot] = its(q[r].u, q[r].v-q[r].u, q[l].u, q[l].v-q[l].u);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        Point p[100]; int m;
        scanf("%d", &m);
        for (int i = 1; i <= m; i++)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        for (int i = 1; i <= m; i++)
            g[++n] = Edge(p[i], p[i % m + 1]);
    }
    half_planes();
    double ans = 0;
    for (int i = 1; i <= tot; i++)
        ans += cross(ans_p[i], ans_p[i % tot + 1]) / 2;
    printf("%.3f\n", ans);
    return 0;
}