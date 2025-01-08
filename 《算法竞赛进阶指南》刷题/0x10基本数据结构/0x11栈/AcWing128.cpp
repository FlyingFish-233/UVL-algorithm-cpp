# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e6 + 10;

int top, asz;
int s[NR], s_max[NR] = {(int) -2e9}, a[NR];

void insert(int x)
{
	top++;
	s[top] = s[top - 1] + x;
	s_max[top] = max(s_max[top - 1], s[top]);
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		char c; int x;
		cin >> c;
		if (c == 'I') scanf("%d", &x), insert(x);
		if (c == 'D' && top > 0) top--;
		if (c == 'L' && top > 0) a[++asz] = s[top] - s[top - 1], top--;
		if (c == 'R' && asz > 0) insert(a[asz--]);
		if (c == 'Q') scanf("%d", &x), printf("%d\n", s_max[x]);
	}
	return 0;
}