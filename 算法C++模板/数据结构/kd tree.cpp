// P1429 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e5 + 10;

struct Node
{
    double x, y;
};

int n;
Node p[NR];

int ls[NR], rs[NR], d[NR];

bool cmp_x(Node n1, Node n2) { return n1.x < n2.x; }
bool cmp_y(Node n1, Node n2) { return n1.y < n2.y; }
double dis(Node n1, Node n2) { return sqrt((n1.x - n2.x) * (n1.x - n2.x) + (n1.y - n2.y) * (n1.y - n2.y)); }

double L[NR], R[NR], D[NR], U[NR];

void maintain(int o)
{
    L[o] = R[o] = p[o].x, D[o] = U[o] = p[o].y;
    if (ls[o] != 0) {
        L[o] = min(L[o], L[ls[o]]), R[o] = max(R[o], R[ls[o]]);
        D[o] = min(D[o], D[ls[o]]), U[o] = max(U[o], U[ls[o]]);
    }
    if (rs[o] != 0) {
        L[o] = min(L[o], L[rs[o]]), R[o] = max(R[o], R[rs[o]]);
        D[o] = min(D[o], D[rs[o]]), U[o] = max(U[o], U[rs[o]]);
    }
}

int build(int l, int r)
{
    if (l > r) return 0;
    int mid = (l + r) >> 1;
    double avx = 0, avy = 0, vax = 0, vay = 0;
    for (int i = l; i <= r; i++)
        avx += p[i].x, avy += p[i].y;
    avx /= r - l + 1, avy /= r - l + 1;
    for (int i = l; i <= r; i++)
        vax += (p[i].x - avx) * (p[i].x - avx), vay += (p[i].y - avy) * (p[i].y - avy);
    if (vax >= vay) d[mid] = 1, nth_element(p + l, p + mid, p + r + 1, cmp_x);
    else d[mid] = 2, nth_element(p + l, p + mid, p + r + 1, cmp_y);
    ls[mid] = build(l, mid - 1), rs[mid] = build(mid + 1, r);
    maintain(mid);
    return mid;
}

double f(int o, int z)
{
    double ans = 0;
    if (L[o] > p[z].x) ans += (L[o] - p[z].x) * (L[o] - p[z].x);
    if (R[o] < p[z].x) ans += (R[o] - p[z].x) * (R[o] - p[z].x);
    if (D[o] > p[z].y) ans += (D[o] - p[z].y) * (D[o] - p[z].y);
    if (U[o] < p[z].y) ans += (U[o] - p[z].y) * (U[o] - p[z].y);
    return sqrt(ans);
}

double ans = 1e17;

void query(int l, int r, int z)
{
    if (l > r) return;
    int mid = (l + r) >> 1;
    if (mid != z) ans = min(ans, dis(p[mid], p[z]));
    if (l == r) return;
    double dis1 = f(ls[mid], z), dis2 = f(rs[mid], z);
    if (dis1 < dis2) {
        if (dis1 < ans) query(l, mid - 1, z);
        if (dis2 < ans) query(mid + 1, r, z);
    }
    else {
        if (dis2 < ans) query(mid + 1, r, z);
        if (dis1 < ans) query(l, mid - 1, z);
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &p[i].x, &p[i].y);
    build(1, n);
    for (int i = 1; i <= n; i++) query(1, n, i);
    printf("%.4f\n", ans);
    return 0;
}