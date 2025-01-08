// AcWing128 (100 pts)
# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e6 + 10;

int top1, top2;
int s1[NR], s2[NR], s1_max[NR] = {(int) -2e9};

void insert1(int x)
{
	top1++;
	s1[top1] = s1[top1 - 1] + x;
	s1_max[top1] = max(s1_max[top1 - 1], s1[top1]);
}

void insert2(int x)
{
	s2[++top2] = x;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		char c; int x;
		cin >> c;
		if (c == 'I') scanf("%d", &x), insert1(x);
		if (c == 'D' && top1 > 0) top1--;
		if (c == 'L' && top1 > 0) insert2(s1[top1] - s1[--top1]);
		if (c == 'R' && top2 > 0) insert1(s2[top2--]);
		if (c == 'Q') scanf("%d", &x), printf("%d\n", s1_max[x]);
	}
	return 0;
}