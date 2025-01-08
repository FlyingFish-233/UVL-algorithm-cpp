# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	int num0 = 0, num1 = (1ll << 31) - 1;
	for (int i = 1; i <= n; i++) {
		char c[5]; int x;
		scanf("%s%d", c, &x);
		if (c[0] == 'A') num0 &= x, num1 &= x;
		if (c[0] == 'O') num0 |= x, num1 |= x;
		if (c[0] == 'X') num0 ^= x, num1 ^= x;
	}
	int ans = 0, val = 0;
	for (int k = 30; k >= 0; k--) {
		if (num0 >> k & 1) ans |= 1 << k;
		else if ((num1 >> k & 1) && val + (1 << k) <= m)
			val += 1 << k, ans |= 1 << k;
	}
	printf("%d\n", ans);
	return 0;
}