# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const double eps = 1e-15;

double sqrt_newton(double n)
{
    if (n <= 0) return 0;
    double x = 1;
    while (true) {
        double nx = (x + n / x) / 2;
        if (abs(nx - x) < eps) break;
        x = nx;
    }
    return x;
}

/*
// 求解最大的x满足x^2 <= n
int sqrt_newton(int n) {
    if (n <= 0) return 0;
    int x = 1;
    bool flag = false;
    while (true) {
        int nx = (x + n / x) / 2;
        if (x == nx || (nx > x && flag)) break; // 上一次x减小, 这一次x增加时退出循环
        flag = nx < x;
        x = nx;
    }
    return x;
}
*/

int main()
{
    double n;
    scanf("%lf", &n);
    printf("%f\n", sqrt_newton(n));
    return 0;
}