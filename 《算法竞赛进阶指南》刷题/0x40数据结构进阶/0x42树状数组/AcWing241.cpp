# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e5 + 10;

int n;
int a[NR], s[NR];
int t1[NR], t2[NR];

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
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++)
		t1[i] = getsum(a[i] - 1), modify(a[i], 1);
	memset(s, 0, sizeof(s));
	for (int i = n; i >= 1; i--)
		t2[i] = getsum(a[i] - 1), modify(a[i], 1);
	long long ans1 = 0, ans2 = 0;
	for (int i = 1; i <= n; i++) {
		ans1 += 1ll * (i - 1 - t1[i]) * (n - i - t2[i]);
		ans2 += 1ll * t1[i] * t2[i];
	}
	printf("%lld %lld\n", ans1, ans2);
	return 0;
}