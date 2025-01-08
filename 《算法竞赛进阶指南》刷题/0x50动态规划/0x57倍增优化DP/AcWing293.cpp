# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <set>

using namespace std;

const int NR = 1e5 + 10;
const int INF = 0x3f3f3f3f;

int n;
int h[NR];
set < pair<int, int> > st;
int ga[NR], gb[NR];
int f[30][NR][2], da[30][NR][2], db[30][NR][2];
int dis_a, dis_b;

void calc(int s, int x)
{
	dis_a = dis_b = 0;
	for (int i = 20; i >= 0; i--)
		if (f[i][s][0] != 0 && dis_a + dis_b + da[i][s][0] + db[i][s][0] <= x)
			dis_a += da[i][s][0], dis_b += db[i][s][0], s = f[i][s][0];
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &h[i]);
	st.insert({-INF, 0}), st.insert({INF, 0});
	st.insert({-INF, 0}), st.insert({INF, 0});
	for (int i = n; i >= 1; i--) {
		st.insert({h[i], i});
		auto it = st.find({h[i], i});
		auto it1 = it; it1--, it1--;
		auto it2 = it; it2--;
		auto it3 = it; it3++;
		auto it4 = it; it4++, it4++;
		int a = (it2 -> second == 0) ? INF : h[i] - (it2 -> first);
		int b = (it3 -> second == 0) ? INF : (it3 -> first) - h[i];
		if (a <= b) {
			gb[i] = it2 -> second;
			a = (it1 -> second == 0) ? INF : h[i] - (it1 -> first);
			ga[i] = (a <= b) ? it1 -> second : it3 -> second;
		}
		else {
			gb[i] = it3 -> second;
			b = (it4 -> second == 0) ? INF : (it4 -> first) - h[i];
			ga[i] = (a <= b) ? it2 -> second : it4 -> second;
		}
	}
	for (int i = 1; i <= n; i++) {
		f[0][i][0] = ga[i], f[0][i][1] = gb[i];
		da[0][i][0] = abs(h[ga[i]] - h[i]), da[0][i][1] = 0;
		db[0][i][0] = 0, db[0][i][1] = abs(h[gb[i]] - h[i]);
	}
	for (int i = 1; i <= n; i++) {
		f[1][i][0] = f[0][f[0][i][0]][1], f[1][i][1] = f[0][f[0][i][1]][0];
		da[1][i][0] = da[0][i][0], da[1][i][1] = da[0][gb[i]][0];
		db[1][i][0] = db[0][ga[i]][1], db[1][i][1] = db[0][i][1];
	}
	for (int i = 2; (1 << i) <= n; i++)
		for (int j = 1; j <= n; j++) {
			f[i][j][0] = f[i - 1][f[i - 1][j][0]][0], f[i][j][1] = f[i - 1][f[i - 1][j][1]][1];
			da[i][j][0] = da[i - 1][j][0] + da[i - 1][f[i - 1][j][0]][0];
			da[i][j][1] = da[i - 1][j][1] + da[i - 1][f[i - 1][j][1]][1];
			db[i][j][0] = db[i - 1][j][0] + db[i - 1][f[i - 1][j][0]][0];
			db[i][j][1] = db[i - 1][j][1] + db[i - 1][f[i - 1][j][1]][1];
		}
	int x0;
	scanf("%d", &x0);
	calc(1, x0);
	int pos = 1; int ans1 = dis_a, ans2 = dis_b;
	for (int i = 2; i <= n; i++) {
		calc(i, x0);
		if (dis_b == 0) continue;
		if (1ll * dis_a * ans2 < 1ll * dis_b * ans1
			|| (1ll * dis_a * ans2 == 1ll * dis_b * ans1 && h[i] > h[pos]))
			pos = i, ans1 = dis_a, ans2 = dis_b;
	}
	printf("%d\n", pos);
	int T;
	scanf("%d", &T);
	while (T--) {
		int s, x;
		scanf("%d%d", &s, &x);
		calc(s, x);
		printf("%d %d\n", dis_a, dis_b);
	}
	return 0;
}