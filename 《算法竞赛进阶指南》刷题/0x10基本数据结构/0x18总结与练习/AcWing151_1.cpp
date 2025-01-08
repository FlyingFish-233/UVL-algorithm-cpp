# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

string s0, s;

int value(char c)
{
	if (c == '+' || c == '-') return 1;
	if (c == '*' || c == '/') return 2;
	if (c == '^') return 3;
	return 0;
}

int fastPow(int a, int b)
{
	int sum = 1;
	for (int i = b; i > 0; i >>= 1, a *= a)
		if (i & 1) sum *= a;
	return sum;
}

int solve(int l, int r)
{
	int now = 0, pos = -1;
	for (int i = l; i <= r; i++) {
		if (s[i] == '(') now++;
		if (s[i] == ')') now--;
		if (value(s[i]) && now == 0 && (pos == -1 || value(s[pos]) >= value(s[i]))) pos = i;
	}
	if (pos == -1) {
		if (s[l] == '(') return solve(l + 1, r - 1);
		int num = 0;
		for (int i = l; i <= r; i++)
			num = num * 10 + s[i] - '0';
		return num;
	}
	int x = solve(l, pos - 1), y = solve(pos + 1, r);
	switch (s[pos]) {
		case '+': return x + y;
		case '-': return x - y;
		case '*': return x * y;
		case '/': return x / y;
		case '^': return fastPow(x, y);
	}
	return 0;
}

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
		for (int i = 0; i < len / 2; i++)
			swap(s[i], s[len - i - 1]);
	}
}

int main()
{
	cin >> s0;
	init();
	printf("%d\n", solve(0, s.length() - 1));
	return 0;
}