# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e5 + 10;

int n, m, t;
int row[NR], col[NR];

long long solve(int a[NR], int sz)
{
	int sum = 0;
	for (int i = 1; i <= sz; i++)
		sum += a[i];
	if (sum % sz != 0) return -1;
	int target = sum / sz, s[NR] = {0};
	for (int i = 1; i <= sz; i++)
		s[i] = s[i - 1] + a[i] - target;
	sort(s + 1, s + sz + 1);
	int pos = sz / 2 + 1;
	long long ans = 0;
	for (int i = 1; i <= sz; i++)
		ans += abs(s[i] - s[pos]);
	return ans;
}

int main()
{
	scanf("%d%d%d", &n, &m, &t);
	for (int i = 1; i <= t; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		row[x]++, col[y]++;
	}
	long long ans1 = solve(row, n), ans2 = solve(col, m);
	if (ans1 != -1 && ans2 != -1) printf("both %lld\n", ans1 + ans2);
	if (ans1 != -1 && ans2 == -1) printf("row %lld\n", ans1);
	if (ans1 == -1 && ans2 != -1) printf("column %lld\n", ans2);
	if (ans1 == -1 && ans2 == -1) printf("impossible\n");
	return 0;
}