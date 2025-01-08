// P5491 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int w, p;

struct Num
{
    int x, y;

    Num() { x = y = 0; }
    Num(int x0, int y0) { x = x0, y = y0; }

    Num operator * (const Num &A) const {
        return Num((1ll * x * A.x % p + 1ll * y * A.y % p * w % p) % p, 
                (1ll * x * A.y % p + 1ll * y * A.x % p) % p);
    }
};

Num qpow(Num a, int b) {
    Num ans = Num(1, 0);
    for (int i = b; i; i >>= 1, a = a * a)
        if (i & 1) ans = ans * a;
    return ans;
}

int qpow(int a, int b) {
    int ans = 1;
    for (int i = b; i; i >>= 1, a = 1ll * a * a % p)
        if (i & 1) ans = 1ll * ans * a % p;
    return ans;
}

int cipolla(int n)
{
    n %= p;
    if (p == 2 || n == 0) return n;
    if (qpow(n, (p - 1) / 2) == p - 1) return -1;
    int a;
    while (true) {
        a = rand() % p;
        w = (1ll * a * a % p - n + p) % p;
        if (qpow(w, (p - 1) / 2) == p - 1) break;
    }
    return qpow(Num(a, 1), (p + 1) / 2).x;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d%d", &n, &p);
        int ans1 = cipolla(n), ans2 = p - ans1;
        if (ans1 == -1) { printf("Hola!\n"); continue; }
        if (ans1 > ans2) swap(ans1, ans2);
        if (ans1 == 0 || ans1 == ans2) printf("%d\n", ans1);
        else printf("%d %d\n", ans1, ans2);
    }
    return 0;
}