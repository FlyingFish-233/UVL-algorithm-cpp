// P3187 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e4 + 10;
const double eps = 1e-8;

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
    Point rotate_90() {
        return {-y, x};
    }
};

int n;
Point p[NR];

double dot(Point a1, Point a2, Point b1, Point b2)
{
    return (a2.x - a1.x) * (b2.x - b1.x) + (a2.y - a1.y) * (b2.y - b1.y);
}

double cross(Point a1, Point a2, Point b1, Point b2)
{
    return (a2.x - a1.x) * (b2.y - b1.y) - (b2.x - b1.x) * (a2.y - a1.y);
}

double dis(Point a, Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool cmp(Point a, Point b)
{
    double tmp = cross(p[1], a, p[1], b);
    if (tmp != 0) return tmp > 0;
    return dis(p[1], a) < dis(p[1], b);
}

int top;
Point st[NR];

void Graham()
{
    for (int i = 1; i <= n; i++)
        if (p[i].y < p[1].y || (p[i].y == p[1].y && p[i].x < p[1].x)) swap(p[i], p[1]);
    sort(p + 2, p + n + 1, cmp);
    st[++top] = p[1];
    for (int i = 2; i <= n; i++) {
        while (top > 1 && cross(st[top - 1], st[top], st[top], p[i]) <= 0) top--;
        st[++top] = p[i];
    }
    st[top + 1] = p[1];
}

double ans = 1e18;
Point q[5];

void getMin()
{
    for (int i = 1, j = 3, l = 2, r = 2; i <= top; i++) {
        while (abs(cross(st[i], st[i + 1], st[i], st[j]))
            < abs(cross(st[i], st[i + 1], st[i], st[j % top + 1])))
            j = j % top + 1;
        while (dot(st[i], st[i + 1], st[i], st[r]) <= dot(st[i], st[i + 1], st[i], st[r % top + 1]))
            r = r % top + 1;
        if (i == 1) l = r;
        while (dot(st[i], st[i + 1], st[i], st[l]) >= dot(st[i], st[i + 1], st[i], st[l % top + 1]))
            l = l % top + 1;
        double w2 = dis(st[i], st[i + 1]);
        double w1 = dot(st[i], st[l], st[i + 1], st[i]) / w2;
        double w3 = dot(st[i + 1], st[r], st[i], st[i + 1]) / w2;
        double h = abs(cross(st[i], st[i + 1], st[i], st[j])) / w2;
        if (ans <= (w1 + w2 + w3) * h) continue;
        ans = (w1 + w2 + w3) * h;
        Point tmp = (st[i + 1] - st[i]).rotate_90();
        q[1] = st[i] + (st[i] - st[i + 1]) * (w1/w2);
        q[2] = q[1] + (st[i + 1] - st[i]) * ((w1 + w2 + w3)/w2);
        q[3] = q[2] + tmp * (h/dis(tmp, {0,0}));
        q[4] = q[3] - (st[i + 1] - st[i]) * ((w1 + w2 + w3)/w2);
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &p[i].x, &p[i].y);
    Graham(), getMin();
    printf("%.5f\n", ans);
    int tmp = 1;
    for (int i = 2; i <= 4; i++)
        if (q[i].y < q[tmp].y || (q[i].y == q[tmp].y && q[i].x < q[tmp].x)) tmp = i;
    for (int i = 1; i <= 4; i++) {
        if (fabs(q[tmp].x) < eps) q[tmp].x = 0;
        if (fabs(q[tmp].y) < eps) q[tmp].y = 0;
        printf("%.5f %.5f\n", q[tmp].x, q[tmp].y), tmp = tmp % 4 + 1;
    }
    return 0;
}