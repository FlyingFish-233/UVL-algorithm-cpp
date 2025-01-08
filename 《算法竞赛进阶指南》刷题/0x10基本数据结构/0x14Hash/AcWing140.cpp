# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

typedef unsigned long long LL;

const int NR = 3e5 + 10, PR = 131;

int n;
char s[NR];
LL f[NR], p[NR];

void init()
{
	f[0] = 0;
	for (int i = 1; i <= n; i++)
		f[i] = f[i - 1] * PR + s[i] - 'a';
	p[0] = 1;
	for (int i = 1; i <= n; i++)
		p[i] = p[i - 1] * PR;
}

LL getHash(int l, int r)
{
	return f[r] - f[l - 1] * p[r - l + 1];
}

int maxfront(int x, int y)
{
	int l = 0, r = n - max(x, y) + 1, ans = 0;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (getHash(x, x + mid - 1) == getHash(y, y + mid - 1)) l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	return ans;
}

struct Array
{
	int x;

	bool operator < (const Array &cmp) {
		int len = maxfront(x, cmp.x);
		return s[x + len] < s[cmp.x + len];
	}
};

Array sa[NR];
int height[NR];

int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	init();
	for (int i = 1; i <= n; i++)
		sa[i].x = i;
	sort(sa + 1, sa + n + 1);
	for (int i = 2; i <= n; i++)
		height[i] = maxfront(sa[i].x, sa[i - 1].x);
	for (int i = 1; i <= n; i++)
		printf("%d ", sa[i].x - 1);
	puts("");
	for (int i = 1; i <= n; i++)
		printf("%d ", height[i]);
	puts("");
	return 0;
}