# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <stack>

using namespace std;

const int NR = 1e6 + 10;

struct Array
{
	bool type;
	int num;
	char op;
};

string s0, s;
stack<char> ch;
stack<int> save;
Array a[NR];

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
	s0 = s, s = "";
	len = s0.length();
	for (int i = 0; i < len; s += s0[i], i++)
		if (s0[i] == '-' && (i == 0 || s0[i - 1] == '(')) s += '0';
}

int main()
{
	cin >> s0;
	init();
	int len = s.length(), cnt = 0;
	for (int i = 0; i < len; i++) {
		if (s[i] == '(') { ch.push(s[i]); continue; }
		if (s[i] >= '0' && s[i] <= '9') {
			int num = 0;
			while (i < len && s[i] >= '0' && s[i] <= '9')
				num = num * 10 + s[i++] - '0';
			a[++cnt] = (Array) {false, num, 0}, i--;
			continue;
		}
		if (s[i] == ')') {
			while (ch.top() != '(')
				a[++cnt] = (Array) {true, 0, ch.top()}, ch.pop();
			ch.pop();
			continue;
		}
		while (!ch.empty() && value(ch.top()) >= value(s[i]))
			a[++cnt] = (Array) {true, 0, ch.top()}, ch.pop();
		ch.push(s[i]);
	}
	while (!ch.empty())
		a[++cnt] = (Array) {true, 0, ch.top()}, ch.pop();
	for (int i = 1; i <= cnt; i++) {
		if (!a[i].type) { save.push(a[i].num); continue; }
		int y = save.top(); save.pop();
		int x = save.top(); save.pop();
		switch (a[i].op) {
			case '+': save.push(x + y); break;
			case '-': save.push(x - y); break;
			case '*': save.push(x * y); break;
			case '/': save.push(x / y); break;
			case '^': save.push(fastPow(x, y));
		}
	}
	printf("%d\n", save.top());
	return 0;
}