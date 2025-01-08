// openjudge6261 (100 pts)
# include <cstdio>
# include <iostream> 
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;

int n;
char a, b, c;

void hanoi(int num, char l, char mid, char r)
{
	if (num == 1) printf("%c->%d->%c\n", l, num, r);
	else {
		hanoi(num - 1, l, r, mid);
		printf("%c->%d->%c\n", l, num, r);
		hanoi(num - 1, mid, l, r);
	}
}

int main()
{
	scanf("%d", &n);
	cin >> a >> b >> c;
	hanoi(n, a, c, b);
	return 0;
}