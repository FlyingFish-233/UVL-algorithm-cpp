# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 1e3 + 10, MR = 1e6 + 10;

int n, group[MR];
queue<int> q[NR];

int main()
{
	for (int cnt = 1; ; cnt++) {
		scanf("%d", &n);
		if (n == 0) break;
		for (int i = 1, sz; i <= n; i++) {
			scanf("%d", &sz);
			for (int j = 1, x; j <= sz; j++)
				scanf("%d", &x), group[x] = i;
		}
		while (!q[0].empty()) {
			int g = q[0].front();
			while (!q[g].empty()) q[g].pop();
			q[0].pop();
		}
		printf("Scenario #%d\n", cnt);
		while (true) {
			char s[10]; int x;
			scanf("%s", s);
			if (s[0] == 'S') break;
			if (s[0] == 'E') {
				scanf("%d", &x);
				if (q[group[x]].empty()) q[0].push(group[x]);
				q[group[x]].push(x);
			}
			if (s[0] == 'D') {
				int g = q[0].front();
				printf("%d\n", q[g].front());
				q[g].pop();
				if (q[g].empty()) q[0].pop();
			}
		}
		puts("");
	}
	return 0;
}