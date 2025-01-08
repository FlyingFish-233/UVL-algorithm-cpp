# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

int n, m;
int a[NR], s[NR];

int lowbit(int x)
{
	return x & (-x);
}

void modify(int x, int delta)
{
	for (int i = x; i <= n + 1; i += lowbit(i))
		s[i] += delta;
}

int getsum(int x)
{
	int ans = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		ans += s[i];
	return ans;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), modify(i, a[i] - a[i - 1]);
	while (m--) {
		char c;
		int l, r, x;
		cin >> c;
		if (c == 'C')
			scanf("%d%d%d", &l, &r, &x), modify(l, x), modify(r + 1, -x);
		if (c == 'Q')
			scanf("%d", &x), printf("%d\n", getsum(x));
	}
	return 0;
}