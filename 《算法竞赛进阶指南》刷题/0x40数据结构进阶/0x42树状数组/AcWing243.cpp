# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

int n, m;
int a[NR];
long long s[2][NR];

int lowbit(int x)
{
	return x & (-x);
}

void modify(int t, int x, long long delta)
{
	for (int i = x; i <= n + 1; i += lowbit(i))
		s[t][i] += delta;
}

long long getsum(int t, int x)
{
	long long ans = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		ans += s[t][i];
	return ans;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		modify(0, i, a[i] - a[i - 1]);
		modify(1, i, 1ll * i * (a[i] - a[i - 1]));
	}
	while (m--) {
		char c;
		int l, r, x;
		cin >> c;
		if (c == 'C') {
			scanf("%d%d%d", &l, &r, &x);
			modify(0, l, x), modify(0, r + 1, -x);
			modify(1, l, 1ll * l * x), modify(1, r + 1, 1ll * (r + 1) * (-x));
		}
		if (c == 'Q') {
			scanf("%d%d", &l, &r);
			long long t1 = l * getsum(0, l - 1) - getsum(1, l - 1);
			long long t2 = (r + 1) * getsum(0, r) - getsum(1, r);
			printf("%lld\n", t2 - t1);
		}
	}
	return 0;
}