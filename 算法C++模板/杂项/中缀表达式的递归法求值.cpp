// AcWing151 (100 pts)
# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

int n;
string s, s0;

void init()
{
	int cnt = 0, now = 0, len = s0.length();
	for (int i = 0; i < len; i++) {
		if (s0[i] == '(') cnt++;
		if (s0[i] == ')') cnt--;
	}
	if (cnt < 0) {
		for (int i = 0; i < len; i++) {
			if (s0[i] == '(') now++;
			if (s0[i] == ')') now--;
			if (now < 0) now = 0;
			else s += s0[i];
		}
	}
	else  {
		for (int i = len - 1; i >= 0; i--) {
			if (s0[i] == '(') now++;
			if (s0[i] == ')') now--;
			if (now > 0) now = 0;
			else s += s0[i];
		}
		len = s.length();
		reverse(s.begin(), s.end());
	}
	s0 = s, s = "", len = s0.length();
	for (int i = 0; i < len; s += s0[i], i++)
		if (s0[i] == '-' && (i == 0 || s0[i - 1] == '(')) s += '0';
}

int level(char c)
{
	if (c == '+' || c == '-') return 1;
	if (c == '*' || c == '/') return 2;
	if (c == '^') return 3;
	return 0;
}

int qpow(int a, int b)
{
	int ans = 1;
	for (int i = b; i; i >>= 1, a *= a)
		if (i & 1) ans *= a;
	return ans;
}

int dfs(int l, int r)
{
	if (l > r) return 0;
	int now = 0, pos = -1;
	for (int i = l; i <= r; i++) {
		if (s[i] == '(') now++;
		if (s[i] == ')') now--;
		if (now == 0 && level(s[i]) != 0 && 
			(pos == -1 || level(s[pos]) >= level(s[i])) ) pos = i;
	}
	if (pos == -1) {
		if (s[l] == '(' && s[r] == ')') return dfs(l + 1, r - 1);
		int num = 0;
		for (int i = l; i <= r; i++)
			num = num * 10 + s[i] - '0';
		return num;
	}
	int x = dfs(l, pos - 1), y = dfs(pos + 1, r);
	switch (s[pos]) {
		case '+': return x + y;
		case '-': return x - y;
		case '*': return x * y;
		case '/': return x / y;
		case '^': return qpow(x, y);
	}
	return 0;
}

int main()
{
	cin >> s0, init(), n = s.length();
	printf("%d\n", dfs(0, n - 1));
    return 0;
}