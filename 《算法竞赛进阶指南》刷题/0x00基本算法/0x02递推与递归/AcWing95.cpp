# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int lim = (1 << 5) - 1;

int a[10], b[10];

void change(int x, int y)
{
	if (x > 1) b[x - 1] ^= 1 << y;
	if (y > 0) b[x] ^= 1 << (y - 1);
	b[x] ^= 1 << y;
	if (y < 4) b[x] ^= 1 << (y + 1);
	if (x < 5) b[x + 1] ^= 1 << y;
}

int solve(int sta)
{
	memcpy(b, a, sizeof(b));
	int ans = 0;
	for (int i = 0; i <= 4; i++)
		if (sta >> i & 1) change(1, i), ans++;
	for (int x = 1; x <= 4; x++)
		for (int i = 0; i <= 4; i++)
			if (!(b[x] >> i & 1)) change(x + 1, i), ans++;
	if (b[5] == lim) return ans;
	return 1e9;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		memset(a, 0, sizeof(a));
		for (int i = 1; i <= 5; i++) {
			char c[10];
			scanf("%s", c);
			for (int j = 0; j <= 4; j++)
				if (c[j] == '1') a[i] |= 1 << j;
		}
		int ans = 1e9;
		for (int i = 0; i <= lim; i++)
			ans = min(ans, solve(i));
		if (ans <= 6) printf("%d\n", ans);
		else printf("%d\n", -1);
	}
	return 0;
}