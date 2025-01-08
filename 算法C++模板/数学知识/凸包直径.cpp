// P1452 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e4 + 10;

struct Point
{
    double x, y;
};

int n;
Point p[NR];

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

double Dis(Point a, Point b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

double getMax()
{
    if (top == 2) return Dis(st[1], st[2]);
    double ans = 0;
    for (int i = 1, j = 3; i <= top; i++) {
        while (abs(cross(st[i], st[i + 1], st[i], st[j]))
            < abs(cross(st[i], st[i + 1], st[i], st[j % top + 1])))
            j = j % top + 1;
        ans = max(ans, max(Dis(st[i], st[j]), Dis(st[i + 1], st[j])));
    }
    return ans;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &p[i].x, &p[i].y);
    Graham();
    printf("%.0f\n", getMax());
    return 0;
}