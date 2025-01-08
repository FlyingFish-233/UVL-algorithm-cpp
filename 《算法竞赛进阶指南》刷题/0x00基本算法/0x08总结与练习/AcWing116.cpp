# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

# define lowbit(x) (x & (-x))

using namespace std;

const int lim = (1 << 16) - 1;

int row[5], cul[5];

int count(int x)
{
	int ans = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		ans++;
	return ans;
}

bool check(int now, int sta)
{
	for (int i = 0; i <= 15; i++)
		if (sta >> i & 1) now ^= row[i / 4], now ^= cul[i % 4], now ^= 1 << i;
	return now == lim;
}

int main()
{
	for (int i = 0; i <= 3; i++)
		for (int j = 0; j <= 3; j++)
			row[i] |= 1 << (i * 4 + j), cul[j] |= 1 << (i * 4 + j);
	int now = 0;
	for (int i = 0; i <= 15; i++) {
		char c;
		cin >> c;
		if (c == '-') now |= 1 << i;
	}
	int ans = lim;
	for (int sta = 0; sta <= lim; sta++)
		if (check(now, sta) && count(sta) < count(ans)) ans = sta;
	printf("%d\n", count(ans));
	for (int i = 0; i <= 15; i++)
		if (ans >> i & 1) printf("%d %d\n", i / 4 + 1, i % 4 + 1);
	return 0;
}