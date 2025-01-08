# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e6 + 10;

char s1[NR], s2[NR];

int getMin(char c[NR])
{
	int len = strlen(c);
	for (int i = 0; i < len; i++)
		c[i + len] = c[i];

	int t1 = 0, t2 = 1;
	while (t1 < len && t2 < len) {
		int k = 0;
		while (k < len && c[t1 + k] == c[t2 + k]) k++;
		if (k == len) return min(t1, t2);
		if (c[t1 + k] < c[t2 + k]) t2 += k + 1;
		else t1 += k + 1;
		if (t1 == t2) t2++;
	}
	return min(t1, t2);
}

int main()
{
	scanf("%s%s", s1, s2);
	int len = strlen(s1), t1 = getMin(s1), t2 = getMin(s2);
	bool flag = true;
	for (int i = 0; i < len; i++)
		if (s1[t1 + i] != s2[t2 + i]) { flag = false; break; }
	if (!flag) { puts("No"); return 0; }
	puts("Yes");
	for (int i = 0; i < len; i++)
		putchar(s1[t1 + i]);
	puts("");
	return 0;
}