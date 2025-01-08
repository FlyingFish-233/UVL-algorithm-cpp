# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

int n;
int a[NR], s[NR];
int t[NR];

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
	for (int i = 2; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++)
		modify(i, 1);
	for (int i = n; i >= 1; i--) {
		int l = 1, r = n;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (getsum(mid) > a[i]) r = mid - 1, t[i] = mid;
			else l = mid + 1;
		}
		modify(t[i], -1);
	}
	for (int i = 1; i <= n; i++)
		printf("%d\n", t[i]);
	return 0;
}