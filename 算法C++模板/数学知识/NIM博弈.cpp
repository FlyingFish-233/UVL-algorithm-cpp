# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, ans = 0;
        scanf("%d", &n);
        for (int i = 1, x; i <= n; i++)
            scanf("%d", &x), ans ^= x;
        if (ans != 0) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}