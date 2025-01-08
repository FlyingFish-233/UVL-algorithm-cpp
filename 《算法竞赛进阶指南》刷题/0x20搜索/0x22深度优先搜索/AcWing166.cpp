# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 100, MR = (1 << 9) + 10;

char str[NR];
int a[NR], b[NR], c[NR], cnt[MR];
int row[NR], cul[NR], block[NR];
int len, sta[NR];

inline int lowbit(int x)
{
	return x & (-x);
}

inline int count(int x)
{
	int ans = 0;
	for (register int i = x; i > 0; i -= lowbit(i)) ans++;
	return ans;
}

inline void change(int x, int y)
{
	row[a[x]] ^= y;
	cul[b[x]] ^= y;
	block[c[x]] ^= y;
}

bool dfs()
{
	int v_min = 2e9, x = -1;
	for (int i = 0; i < 81; i++) {
		if (sta[i]) continue;
		int val = cnt[row[a[i]] & cul[b[i]] & block[c[i]]];
		if (v_min > val) v_min = val, x = i;
	}
	if (x == -1) {
		for (int i = 0; i < 81; i++)
			for (int j = 0; j < 9; j++)
				if (sta[i] >> j & 1) printf("%d", j + 1);
		puts("");
		return true;
	}
	for (register int i = row[a[x]] & cul[b[x]] & block[c[x]]; i > 0; i -= lowbit(i)) {
		change(x, sta[x] = lowbit(i));
		if (dfs()) return true;
		change(x, lowbit(i)), sta[x] = 0;
	}
	return false;
}

int main()
{
	for (int i = 0; i < 81; i++) {
		a[i] = i / 9;
		b[i] = i % 9;
		c[i] = a[i] / 3 * 3 + b[i] / 3;
	}
	for (int i = 0; i < (1 << 9); i++)
		cnt[i] = count(i);
	while (scanf("%s", str) && str[0] != 'e') {
		for (register int i = 0; i < 9; i++)
			row[i] = cul[i] = block[i] = (1 << 9) - 1;
		memset(sta, 0, sizeof(sta));
		for (register int i = 0; i < 81; i++)
			if (str[i] != '.') change(i, sta[i] = 1 << (str[i] - '0' - 1));
		dfs();
	}
	return 0;
}