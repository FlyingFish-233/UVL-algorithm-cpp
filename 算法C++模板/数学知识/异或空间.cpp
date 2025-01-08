// P3812 (100 pts)
# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 100;

int n;
long long mat[NR];

int Gause()
{
    for (int i = 1; i <= n; i++) {
        int row = i;
        for (int j = i + 1; j <= n; j++)
            if (mat[j] > mat[row]) row = j;
        if (mat[row] == 0) return i - 1;
        swap(mat[i], mat[row]);
        for (int k = 50; k >= 0; k--) 
            if (mat[i] >> k & 1) {
                for (int j = 1; j <= n; j++)
                    if (i != j && mat[j] >> k & 1) mat[j] ^= mat[i];
                break;
            }
    }
    return n;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &mat[i]);
    int t = Gause(); long long ans = 0;
    for (int i = 1; i <= t; i++)
        ans ^= mat[i];
    printf("%lld\n", ans);
    return 0;
}