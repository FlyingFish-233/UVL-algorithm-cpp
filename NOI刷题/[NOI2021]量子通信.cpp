# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

typedef unsigned long long ull;

const int NR = 4e5 + 10;

int n, m;
bool s[NR][256];

ull myRand(ull &k1, ull &k2) {
    ull k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 << 23);
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}

void gen(int n, ull a1, ull a2) {
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 256; j++)
            s[i][j] = (myRand(a1, a2) & (1ull << 32)) ? 1 : 0;
}

int cnt[NR];
int head[16][65536], to[16][NR];

void add(int i, int num, int x)
{
	to[i][x] = head[i][num], head[i][num] = x;
}

int cnt0, lim;
char c[64];
bool a[256];

int ctoi(char ch)
{
	if (ch >= '0' && ch <= '9') return ch - '0';
	return ch - 'A' + 10;
}

bool check(int x)
{
	if (abs(cnt0 - cnt[x]) > lim) return false;
	int tmp = 0;
	for (int i = 0; i < 256; i++) {
		if (a[i] != s[x][i]) tmp++;
		if (tmp > lim) return false;
	}
	return true;
}

int main()
{
	ull a1, a2;
	cin >> n >> m >> a1 >> a2;
	gen(n, a1, a2);
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < 16; j++) {
			int num = 0;
			for (int k = 0; k < 16; k++)
				num = num * 2 + s[i][j * 16 + k], cnt[i] += s[i][j * 16 + k];
			add(j, num, i);
		}
	bool lastans = 0;
	while (m--) {
		scanf("%s%d", c, &lim), cnt0 = 0;
		for (int i = 0; i < 64; i++) {
			int x = ctoi(c[i]);
			cnt0 += (a[4 * i] = x / 8 ^ lastans);
			cnt0 += (a[4 * i + 1] = x / 4 % 2 ^ lastans);
			cnt0 += (a[4 * i + 2] = x / 2 % 2 ^ lastans);
			cnt0 += (a[4 * i + 3] = x % 2 ^ lastans);
		}
		bool flag = false;
		for (int i = 0; i < 16; i++) {
			int num = 0;
			for (int j = 0; j < 16; j++)
				num = num * 2 + a[i * 16 + j];
			for (int j = head[i][num]; j; j = to[i][j])
				if (check(j)) { flag = true; break; }
			if (flag) break;
		}
		printf("%d\n", lastans = flag);
	}
	
}
