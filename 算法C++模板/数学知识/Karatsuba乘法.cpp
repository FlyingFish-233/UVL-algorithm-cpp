// P1303 (100 pts)
# include <cstdio>
# include <cstring>
# include <algorithm>
# include <cmath>

using namespace std;

const int NR = 4e3 + 10;

// a = x1 * 10^m + y1, b = x2 * 10^m + y2
// z2 = x1 * x2, z0 = y1 * y2;
// z1 = x1 * y2 + x2 * y1 = (x1 + y1) * (y1 + y2) - z2 - z0
// a * b = z2 * 10^2m + z1 * 10^m + z0
int *karatsuba(int n, int *a, int *b)
{
    if (n <= 32) {
        int *s = new int[2 * n + 10]();
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                s[i + j] += a[i] * b[j];
        return s;
    }
    int m = n / 2 + 1;
    int *z2 = karatsuba(n - m, a + m, b + m), *z0 = karatsuba(m - 1, a, b);
    for (int i = 0; i <= n - m; i++) a[i] += a[i + m]; // m - 1 >= n - m
    for (int i = 0; i <= n - m; i++) b[i] += b[i + m]; // 这里只能循环到n-m,因为当i+m>n时,a[i+m]可能不是0
    int *z1 = karatsuba(m - 1, a, b);
    for (int i = 0; i <= n - m; i++) a[i] -= a[i + m];
    for (int i = 0; i <= n - m; i++) b[i] -= b[i + m];
    for (int i = 0; i <= 2 * (n - m); i++) z1[i] -= z2[i];
    for (int i = 0; i <= 2 * (m - 1); i++) z1[i] -= z0[i];

    int *s = new int[2 * n + 10]();
    for (int i = 0; i <= 2 * (n - m); i++) s[i + 2 * m] += z2[i];
    for (int i = 0; i <= 2 * (m - 1); i++) s[i + m] += z1[i];
    for (int i = 0; i <= 2 * (m - 1); i++) s[i] += z0[i];
    delete[] z0; delete[] z1; delete[] z2;
    return s;
}

int len1, len2;
char s1[NR], s2[NR];
int a[NR], b[NR];

int main()
{
    scanf("%s%s", s1, s2);
    len1 = strlen(s1), len2 = strlen(s2);
    for (int i = 0; i < len1; i++) a[len1 - i - 1] = s1[i] - '0';
    for (int i = 0; i < len2; i++) b[len2 - i - 1] = s2[i] - '0';
    int *s = karatsuba(max(len1, len2) - 1, a, b);
    int len = len1 + len2;
    for (int i = 0; i <= len - 1; i++)
        s[i + 1] += s[i] / 10, s[i] %= 10;
    while (s[len - 1] == 0 && len > 1) len--;
    for (int i = len - 1; i >= 0; i--)
        printf("%d", s[i]);
    puts("");
	return 0;
}
