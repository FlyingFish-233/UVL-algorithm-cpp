// P3368 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e5 + 10;

int n, m;
int s[NR];

int lowbit(int x)
{
	return x & (-x);
}

void modify(int x, int delta)
{
	for (int i = x; i <= n; i += lowbit(i))
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
	for (int i = 1, x, y = 0; i <= n; i++, y = x)
		scanf("%d", &x), modify(i, x - y);
	while (m--) {
		int op, x, y, k;
		scanf("%d%d", &op, &x);
		if (op == 1) scanf("%d%d", &y, &k), modify(x, k), modify(y + 1, -k);
		if (op == 2) printf("%d\n", getsum(x));
	}
    return 0;
}