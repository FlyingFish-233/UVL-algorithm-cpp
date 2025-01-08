# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e5 + 10, Base = 1e9;

int n, cnt;
int pri[NR], box[NR];
int len = 1;
long long num[NR] = {0, 1};

void solve(int x, int delta)
{
	for (int i = 1; x != 1; i++)
		while (x % pri[i] == 0)
			box[i] += delta, x /= pri[i];
}

void mult(int x)
{
	for (int i = 1; i <= len; i++)
		num[i] *= x;
	for (int i = 1; i <= len; i++) {
		num[i + 1] += num[i] / Base;
		num[i] %= Base;
		if (num[i + 1]) len = max(len, i + 1);
	}
}

void divs(int x)
{
	long long now = 0;
	for (int i = len; i >= 1; i--) {
		now = now * Base + num[i];
		num[i] = now / x;
		now %= x;
	}
	while (num[len] == 0 && len > 1) len--;
}

int main()
{
	scanf("%d", &n);
	for (int i = 2; i <= n * 2; i++) {
		bool flag = true;
		for (int j = 1; j <= cnt && 1ll * pri[j] * pri[j] <= i; j++)
			if (i % pri[j] == 0) { flag = false; break; }
		if (flag) pri[++cnt] = i;
	}
	for (int i = n + 1; i <= n * 2; i++)
		solve(i, 1);
	for (int i = 1; i <= n; i++)
		solve(i, -1);
	for (int i = 1; i <= cnt; i++)
		for (int j = 1; j <= box[i]; j++)
			mult(pri[i]);
	divs(n + 1);
	printf("%lld", num[len]);
	for (int i = len - 1; i >= 1; i--)
		printf("%09lld", num[i]);
	puts("");
	return 0;
}