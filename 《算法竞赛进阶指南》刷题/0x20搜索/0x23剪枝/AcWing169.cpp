# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 300, MR = (1 << 16) + 10;
const int lim = (1 << 16) - 1;

char str[20];
int a[NR], b[NR], c[NR];
int id[NR][NR], cnt[MR], pos[MR];
vector<int> g[20];
int box[20], sta[NR], num[NR];

int lowbit(int x)
{
	return x & (-x);
}

void change(int x, int t)
{
	num[x] = t;
	for (int i = 0; i < 16; i++)
		sta[id[a[x]][i]] &= lim - (1 << t);
	for (int i = 0; i < 16; i++)
		sta[id[i][b[x]]] &= lim - (1 << t);
	for (int i = 0; i < 16; i++)
		sta[g[c[x]][i]] &= lim - (1 << t);
}

bool fill()
{
	for (int i = 0; i < 256; i++) {
		if (num[i] != -1) continue;
		if (cnt[sta[i]] == 0) return false;
		if (cnt[sta[i]] == 1) change(i, pos[sta[i]]);
	}
	for (int i = 0; i < 16; i++) {
		memset(box, 0, sizeof(box));
		int now = lim;
		for (int j = 0; j < 16; j++) {
			if (num[id[i][j]] == -1) 
				for (int k = sta[id[i][j]]; k > 0; k -= lowbit(k))
					box[pos[lowbit(k)]]++;
			else now ^= 1 << num[id[i][j]];
		}
		for (int j = now; j > 0; j -= lowbit(j)) {
			int t = pos[lowbit(j)];
			if (box[t] == 0) return false;
			if (box[t] == 1)
				for (int k = 0; k < 16; k++)
					if (num[id[i][k]] == -1 && (sta[id[i][k]] & (1 << t))) {
						change(id[i][k], t);
						break;
					}
		}
	}
	for (int i = 0; i < 16; i++) {
		memset(box, 0, sizeof(box));
		int now = lim;
		for (int j = 0; j < 16; j++) {
			if (num[id[j][i]] == -1) 
				for (int k = sta[id[j][i]]; k > 0; k -= lowbit(k))
					box[pos[lowbit(k)]]++;
			else now ^= 1 << num[id[j][i]];
		}
		for (int j = now; j > 0; j -= lowbit(j)) {
			int t = pos[lowbit(j)];
			if (box[t] == 0) return false;
			if (box[t] == 1)
				for (int k = 0; k < 16; k++)
					if (num[id[k][i]] == -1 && (sta[id[k][i]] & (1 << t))) {
						change(id[k][i], t);
						break;
					}
		}
	}
	for (int i = 0; i < 16; i++) {
		memset(box, 0, sizeof(box));
		int now = lim;
		for (int j = 0; j < 16; j++) {
			if (num[g[i][j]] == -1) 
				for (int k = sta[g[i][j]]; k > 0; k -= lowbit(k))
					box[pos[lowbit(k)]]++;
			else now ^= 1 << num[g[i][j]];
		}
		for (int j = now; j > 0; j -= lowbit(j)) {
			int t = pos[lowbit(j)];
			if (box[t] == 0) return false;
			if (box[t] == 1)
				for (int k = 0; k < 16; k++)
					if (num[g[i][k]] == -1 && (sta[g[i][k]] & (1 << t))) {
						change(g[i][k], t);
						break;
					}
		}
	}
	return true;
}

bool dfs()
{
	if (!fill()) return false;
	int v_min = 2e9, x = -1;
	for (int i = 0; i < 256; i++)
		if (num[i] == -1 && v_min > cnt[sta[i]]) v_min = cnt[sta[i]], x = i;
	if (x == -1) {
		for (int i = 0; i < 256; i++) {
			putchar(num[i] + 'A');
			if (i % 16 == 15) puts("");
		}
		puts("");
		return true;
	}
	int save1[NR], save2[NR];
	memcpy(save1, sta, sizeof(sta));
	memcpy(save2, num, sizeof(num));
	for (int i = sta[x]; i > 0; i -= lowbit(i)) {
		change(x, pos[lowbit(i)]);
		if (dfs()) return true;
		memcpy(sta, save1, sizeof(save1));
		memcpy(num, save2, sizeof(save2));
	}
	return false;
}

int main()
{
	for (int i = 0; i < 256; i++) {
		a[i] = i / 16;
		b[i] = i % 16;
		c[i] = a[i] / 4 * 4 + b[i] / 4;

		id[a[i]][b[i]] = i;
		g[c[i]].push_back(i);
	}
	for (int i = 0; i < lim; i++)
		for (int j = i; j > 0; j -= lowbit(j))
			cnt[i]++;
	for (int i = 0; i < 16; i++)
		pos[1 << i] = i;
	
	while (scanf("%s", str) != EOF) {
		for (int i = 0; i < 256; i++)
			sta[i] = lim;
		memset(num, -1, sizeof(num));
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++)
				if (str[j] != '-')
					change(id[i][j], str[j] - 'A');
			if (i < 15) scanf("%s", str);
		}
		dfs();
	}
	return 0;
}