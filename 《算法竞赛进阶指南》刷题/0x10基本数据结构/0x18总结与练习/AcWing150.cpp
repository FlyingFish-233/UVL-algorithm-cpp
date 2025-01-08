# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <stack>

using namespace std;

const int NR = 1e5 + 10;

char c[NR];

int top, l[NR];
char s[NR];

bool check(char a, char b)
{
	return (a == '{' && b == '}') || (a == '[' && b == ']') || (a == '(' && b == ')');
}

int main()
{
	scanf("%s", c);
	int len = strlen(c), ans = 0;
	for (int i = 0; i < len; i++) {
		if (c[i] == '{' || c[i] == '[' || c[i] == '(') s[++top] = c[i], l[top] = 0;
		else if (top > 0 && check(s[top], c[i])) ans = max(ans, l[top - 1] += l[top] + 1), top--;
		else l[top = 0] = 0;
	}
	printf("%d\n", ans << 1);
	return 0;
}