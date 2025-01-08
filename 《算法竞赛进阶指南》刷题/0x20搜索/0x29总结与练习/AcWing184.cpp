# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

# define mod(x) ((x >= n) ? x - n : x)

using namespace std;

const int NR = 30;

int n;
char s1[NR], s2[NR], s3[NR];
int a[NR], b[NR], c[NR];
int num[NR];
bool used[NR];

inline bool check(int x)
{
	if (num[a[1]] != -1 && num[b[1]] != -1 && num[a[1]] + num[b[1]] >= n) return false;
	for (register int i = 1; i <= x; i++) {
		if (num[a[i]] == -1 || num[b[i]] == -1 || num[c[i]] == -1) continue;
		if (mod(num[a[i]] + num[b[i]]) != num[c[i]] && mod(num[a[i]] + num[b[i]] + 1) != num[c[i]]) return false;
	}
	return true;
}

inline void dfs(int x, int add)
{
	if (!check(x)) return;
	if (x < 1) {
		if (add == 1) return;
		for (register int i = 0; i < n; i++)
			printf("%d ", num[i]);
		puts("");
		exit(0);
	}
	if (num[a[x]] == -1) {
		for (register int i = 0; i < n; i++)
			if (!used[i]) {
				used[num[a[x]] = i] = true;
				dfs(x, add);
				used[i] = false, num[a[x]] = -1;
			}
		return;
	}
	if (num[b[x]] == -1) {
		for (register int i = 0; i < n; i++)
			if (!used[i]) {
				used[num[b[x]] = i] = true;
				dfs(x, add);
				used[i] = false, num[b[x]] = -1;
			}
		return;
	}
	int ans = num[a[x]] + num[b[x]] + add;
	if (num[c[x]] == -1 && !used[mod(ans)]) {
		used[num[c[x]] = mod(ans)] = true;
		dfs(x - 1, ans / n);
		used[mod(ans)] = false, num[c[x]] = -1;
		return;
	}
	if (num[c[x]] == mod(ans)) dfs(x - 1, ans / n);
}

int main()
{
	scanf("%d", &n);
	scanf("%s%s%s", s1 + 1, s2 + 1, s3 + 1);
	for (int i = 1; i <= n; i++) {
		a[i] = s1[i] - 'A';
		b[i] = s2[i] - 'A';
		c[i] = s3[i] - 'A';
	}
	memset(num, -1, sizeof(num));
	dfs(n, 0);
	return 0;
}