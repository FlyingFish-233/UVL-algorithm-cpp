# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <stack>

using namespace std;

const int NR = 1e3 + 10;

int n, m;
int h[NR][NR];
stack< pair<int, int> > s;

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			char c;
			cin >> c;
			if (c == 'F') h[i][j] = h[i - 1][j] + 1;
		}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m + 1; j++) {
			int sum = 0;
			while (!s.empty() && s.top().first >= h[i][j]) {
				sum += s.top().second;
				ans = max(ans, s.top().first * sum);
				s.pop();
			}
			s.push(make_pair(h[i][j], sum + 1));
		}
	printf("%d\n", 3 * ans);
	return 0;
}