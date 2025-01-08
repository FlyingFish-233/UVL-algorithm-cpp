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

int L, lim, rev[NR];

void fft(complex *a, int type)
{
    for (int i = 0; i < lim; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int len = 1; len < lim; len <<= 1) {
        complex w(cos(PI / len), type * sin(PI / len));
        for (int i = 0; i < lim; i += 2*len) {
            complex wk(1, 0);
            for (int j = i; j < i + len; j++, wk = wk * w) {
                complex t1 = a[j], t2 = wk * a[j + len]; // 蝴蝶效应(优化)
                a[j] = t1 + t2, a[j + len] = t1 - t2;
            }
        }
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
    lim = 1; while (lim <= n + m) lim <<= 1, L++;
    for (int i = 0; i < lim; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
    fft(a, 1), fft(b, 1);
    for (int i = 0; i < lim; i++)
        a[i] = a[i] * b[i];
    fft(a, -1);
    for (int i = 0; i <= n + m; i++)
        printf("%d ", (int) (a[i].x / lim + 0.5));
    return 0;
}
