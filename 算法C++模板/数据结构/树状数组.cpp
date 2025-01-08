// P3374 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 5e5 + 10;

int n, m;
int s[NR];
// s[i] = a[i - 2^k + 1] + a[i - 2^k + 2] + ... + a[i] 其中k为i在二进制下末尾0的个数

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
	for (int i = 1, x; i <= n; i++)
		scanf("%d", &x), modify(i, x);
	while (m--) {
		int op, x, y;
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1) modify(x, y);
		if (op == 2) printf("%d\n", getsum(y) - getsum(x - 1));
	}
    return 0;
}