# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 210, MR = 400;

int n, m;
int a[NR], b[NR];
int f[21][(MR << 1) + 10];
int pre[NR][21][(MR << 1) + 10];
bool used[NR];

void get_method(int i, int x, int y)
{
	int last = pre[i][x][y];
	if (last == 0) return;
	used[last] = true;
	get_method(last - 1, x - 1, y - (a[last] - b[last]));
}

int main()
{
	int T = 0;
	while (scanf("%d%d", &n, &m) && !(n == 0 && m == 0)) {
		for (int i = 1; i <= n; i++)
			scanf("%d%d", &a[i], &b[i]);
		memset(f, -0x3f, sizeof(f));
		f[0][MR] = 0;
		for (int i = 1; i <= n; i++) {
			memcpy(pre[i], pre[i - 1], sizeof(pre[i - 1]));
			for (int j = m; j >= 1; j--)
				for (int k = 0; k <= (MR << 1); k++) if (k - (a[i] - b[i]) >= 0 && k - (a[i] - b[i]) <= MR << 1)
					if (f[j][k] < f[j - 1][k - (a[i] - b[i])] + a[i] + b[i])
						f[j][k] = f[j - 1][k - (a[i] - b[i])] + a[i] + b[i], pre[i][j][k] = i;
		}
		int d = 0;
		for (int i = 0; i <= MR; i++)
			if (f[m][MR + i] > -1e9 || f[m][MR - i] > -1e9) {
				d = (f[m][MR + i] >= f[m][MR - i]) ? i : -i;
				break;
			}
		printf("Jury #%d\n", ++T);
		printf("Best jury has value %d for prosecution and value %d for defence:\n", (f[m][MR + d] + d) >> 1, (f[m][MR + d] - d) >> 1);
		memset(used, false, sizeof(used));
		get_method(n, m, MR + d);
		for (int i = 1; i <= n; i++)
			if (used[i]) printf(" %d", i);
		puts("\n");
	}
	return 0;
}