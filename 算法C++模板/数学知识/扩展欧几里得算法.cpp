// P3811 (80 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int n, p;

void exgcd(int a, int b, int &x, int &y)
{
	if (b == 0) x = 1, y = 0;
	else exgcd(b, a % b, y, x), y -= a / b * x;
}

int main()
{
	scanf("%d%d", &n, &p);
	for (int i = 1; i <= n; i++) {
		int x, y;
		exgcd(i, p, x, y);
		printf("%d\n", (x + p) % p);
	}
    return 0;
}