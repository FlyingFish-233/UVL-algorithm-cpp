// P3803 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 4e6 + 10;
const double PI = 3.141592653589793;

struct complex
{
    double x, y;
    complex(double x0 = 0, double y0 = 0) { x = x0, y = y0; }
    complex operator + (const complex &A) const { return complex(x + A.x, y + A.y); }
    complex operator - (const complex &A) const { return complex(x - A.x, y - A.y); }
    complex operator * (const complex &A) const { return complex(x*A.x - y*A.y, x*A.y + y*A.x); }
};

void fft(int lim, complex *a, int type)
{
    if (lim == 1) return;
    complex a1[lim >> 1], a2[lim >> 1];
    for (int i = 0; i < lim; i += 2)
        a1[i >> 1] = a[i], a2[i >> 1] = a[i + 1];
    fft(lim >> 1, a1, type), fft(lim >> 1, a2, type);
    complex w(cos(2 * PI / lim), type * sin(2 * PI / lim)), wk(1, 0);
    for (int i = 0; i < (lim >> 1); i++, wk = wk * w) {
        complex t = wk * a2[i]; // 蝴蝶效应(优化)
        a[i] = a1[i] + t;
        a[i + (lim >> 1)] = a1[i] - t;
    }
}

int n, m;
complex a[NR], b[NR];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i++)
        scanf("%lf", &a[i].x);
    for (int i = 0; i <= m; i++)
        scanf("%lf", &b[i].x);
    int lim = 1; while (lim <= n + m) lim <<= 1;
    fft(lim, a, 1), fft(lim, b, 1);
    for (int i = 0; i < lim; i++)
        a[i] = a[i] * b[i];
    fft(lim, a, -1);
    for (int i = 0; i <= n + m; i++) 
        printf("%d ", (int) (a[i].x / lim + 0.5));
    return 0;
}