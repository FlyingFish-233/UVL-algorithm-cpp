// P5170 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

typedef long long LL;

const LL PR = 998244353;
const LL i2 = 499122177, i6 = 166374059; // 2和6在模PR意义下的数论倒数

struct data
{
    LL f, g, h;
    data() { f = g = h = 0; }
};

data calc(LL n, LL a, LL b, LL c)
{
    data A;
    LL ac = a / c, bc = b / c;
    LL t1 = n * (n + 1) % PR * i2 % PR;
    LL t2 = n * (n + 1) % PR * (2 * n + 1) % PR * i6 % PR;
    if (a == 0) {
        A.f = bc * (n + 1) % PR;
        A.g = bc * t1 % PR;
        A.h = bc * bc % PR * (n + 1) % PR;
        return A;
    }
    if (a >= c || b >= c) {
        data B = calc(n, a % c, b % c, c);
        A.f = (t1 * ac % PR + (n + 1) * bc % PR + B.f) % PR;
        A.g = (B.g + ac * t2 % PR + bc * t1 % PR) % PR;
        A.h = (B.h + 2 * bc % PR * B.f % PR + 2 * ac % PR * B.g % PR + ac * ac % PR * t2 % PR
             + bc * bc % PR * (n + 1) % PR + ac * bc % PR * n % PR * (n + 1) % PR) % PR;
        return A;
    }
    LL m = (a * n + b) / c;
    data B = calc(m - 1, c, c - b - 1, a);
    A.f = n * m % PR - B.f;
    A.g = (m * n % PR * (n + 1) % PR - B.h - B.f) % PR * i2 % PR;
    A.h = n * m % PR * (m + 1) % PR - 2 * B.f - 2 * B.g - A.f;
    A.f = (A.f % PR + PR) % PR, A.g = (A.g % PR + PR) % PR, A.h = (A.h % PR + PR) % PR;
    return A;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        LL n, a, b, c;
        scanf("%lld%lld%lld%lld", &n, &a, &b, &c);
        data A = calc(n, a, b, c);
        printf("%lld %lld %lld\n", A.f, A.h, A.g);
    }
    return 0;
}