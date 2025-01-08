// P2742 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

struct Point
{
    double x, y;
    bool operator < (const Point &cmp) const {
        return x < cmp.x || (x == cmp.x && y < cmp.y);
    }
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

int top;
Point st[NR];

void Andrew()
{
    sort(p + 1, p + n + 1);
    st[++top] = p[1];
    for (int i = 2; i <= n; i++) {
        while (top > 1 && cross(st[top - 1], st[top], st[top], p[i]) <= 0) top--;
        st[++top] = p[i];
    }
    int save = top;
    for (int i = n - 1; i >= 1; i--) {
        while (top > save && cross(st[top - 1], st[top], st[top], p[i]) <= 0) top--;
        st[++top] = p[i];
    }
    top--;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &p[i].x, &p[i].y);
    Andrew();
    double ans = 0;
    for (int i = 1; i <= top; i++)
        ans += dis(st[i], st[i + 1]);
    printf("%.2f\n", ans);
    return 0;
}