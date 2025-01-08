# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 3e5 + 10;

int n, s;
long long sumt[NR], sumc[NR];
double f[NR];
int l = 1, r = 0, q[NR];

int binary_search(int k)
{
    if (l == r) return q[l];
    int L = l, R = r;
    while (L < R) {
        int mid = (L + R) >> 1;
        if (f[q[mid + 1]] - f[q[mid]] <= k * (sumc[q[mid + 1]] - sumc[q[mid]])) L = mid + 1;
        else R = mid;
    }
    return q[L];
}

int main()
{
    scanf("%d%d", &n, &s);
    for (int i = 1, t, c; i <= n; i++) {
        scanf("%d%d", &t, &c);
        sumt[i] = sumt[i - 1] + t;
        sumc[i] = sumc[i - 1] + c;
    }
    q[++r] = 0;
    for (int i = 1; i <= n; i++) {
        int x = binary_search(s + sumt[i]);
        f[i] = f[x] - (s + sumt[i]) * sumc[x] + sumt[i] * sumc[i] + s * sumc[n];
        while (l < r && (f[q[r]] - f[q[r - 1]]) * (sumc[i] - sumc[q[r]])
            >= (sumc[q[r]] - sumc[q[r - 1]]) * (f[i] - f[q[r]])) r--;
        q[++r] = i;
    }
    printf("%.0lf\n", f[n]);
    return 0;
}