# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e5 + 10;

int n;
int a[NR], b[NR];
int s[NR], ans[NR];

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
	int sum = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		sum += s[i];
	return sum;
}


int main()
{
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; i++)
			scanf("%d%d", &a[i], &b[i]);
		for (int i = 1; i <= n; i++)
			modify(i, 1);
		for (int i = n; i >= 1; i--) {
			int l = 1, r = n, t = 0;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (getsum(mid) >= a[i] + 1) r = mid - 1, t = mid;
				else l = mid + 1;
			}
			ans[t] = b[i], modify(t, -1);
		}
		for (int i = 1; i <= n; i++)
			printf("%d ", ans[i]);
		puts("");
	}
	return 0;
}