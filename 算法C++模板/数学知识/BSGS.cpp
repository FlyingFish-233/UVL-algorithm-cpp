// P3846 (100 pts)
# include <cstdio>
# include <cmath>
# include <cstring>
# include <algorithm>
# include <map>

using namespace std;

int bsgs(int a, int b, int p)
{
	a %= p, b %= p;
	if (b == 1 || p == 1) return 0; // 0^0 = 1, 0^1 = 0
	if (a == 0) return (b == 0) ? 1 : -1;
	map<int, int> hash;
	int t = sqrt(p) + 1, A = 1; // x = i * t - j (0<=i<=t, 0<=j<t)
	for (int j = 0; j <= t - 1; j++, A = 1ll * A * a % p)
		hash[1ll * b * A % p] = j; // A = a^j
	a = A, A = 1;
	for (int i = 0; i <= t; i++, A = 1ll * A * a % p) {
		int j = (hash.count(A) == 0) ? -1 : hash[A]; // A = (a^t)^i
		if (j >= 0 && i * t - j >= 0) return i * t - j;
	}
	return -1;
}

int main()
{
	int a, b, p;
	scanf("%d%d%d", &p, &a, &b);
	int ans = bsgs(a, b, p);
	if (ans == -1) printf("no solution\n");
	else printf("%d\n", ans);
 	return 0;
}

