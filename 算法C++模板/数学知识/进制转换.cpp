// POJ1220 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 100 + 10;

char s[NR];
int len, num[NR];
int sz, ans[NR];

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int a, b;
		scanf("%d%d%s", &a, &b, s);
		printf("%d %s\n%d ", a, s, b);
		len = strlen(s), sz = 0;
		for (int i = 0; i < len; i++) {
			if (s[i] >= '0' && s[i] <= '9') num[len - i] = s[i] - '0';
			if (s[i] >= 'A' && s[i] <= 'Z') num[len - i] = s[i] - 'A' + 10;
			if (s[i] >= 'a' && s[i] <= 'z') num[len - i] = s[i] - 'a' + 36;
		}
		while (len != 1 || num[1] != 0) {
			int now = 0;
			for (int i = len; i >= 1; i--) {
				now = now * a + num[i];
				num[i] = now / b;
				now %= b;
			}
			while (num[len] == 0 && len > 1) len--;
			ans[++sz] = now;
		}
		for (int i = sz; i >= 1; i--) {
			if (ans[i] >= 0 && ans[i] <= 9) putchar(ans[i] + '0');
			if (ans[i] >= 10 && ans[i] <= 35) putchar(ans[i] + 'A' - 10);
			if (ans[i] >= 36 && ans[i] <= 62) putchar(ans[i] + 'a' - 36);
		}
		if (sz == 0) printf("0");
		printf("\n\n");
	}
	return 0;
}