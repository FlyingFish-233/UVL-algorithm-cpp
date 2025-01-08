# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <stack>

using namespace std;

const int NR = 100;

int n, cnt, qsz, top;
int q[NR], s[NR];

void dfs(int x)
{
	if (x > n) {
		for (int i = 1; i <= qsz; i++)
			printf("%d", q[i]);
		for (int i = top; i >= 1; i--)
			printf("%d", s[i]);
		puts("");
		if (++cnt == 20) exit(0);
		return;
	}
	if (top > 0) {
		q[++qsz] = s[top--];
		dfs(x);
		s[++top] = q[qsz--];
	}
	s[++top] = x;
	dfs(x + 1);
	top--;
}

int main()
{
	scanf("%d", &n);
	dfs(1);
	return 0;
}