// AcWing151 (100 pts)
# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <stack>

using namespace std;

const int NR = 1e6 + 10;

int n;
string s, s0;

// 去除多余括号 & 给负号前加0
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

struct Formula
{
    int type; int v; char c;
};

int m;
Formula f[NR];

int level(char c)
{
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return 0;
}

void change()
{
    stack<char> st;
    for (int i = 0; i <= n - 1; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            int now = s[i] - '0';
            while (s[i + 1] >= '0' && s[i + 1] <= '9')
                now = now * 10 + s[++i] - '0';
            f[++m] = (Formula) {0, now, 0};
        }
        if (s[i] == '(') st.push(s[i]);
        if (s[i] == ')') {
            while (st.top() != '(')
                f[++m] = (Formula) {1, 0, st.top()}, st.pop();
            st.pop();
        }
        if (level(s[i]) > 0) {
            while (!st.empty() && level(st.top()) >= level(s[i]))
                f[++m] = (Formula) {1, 0, st.top()}, st.pop();
            st.push(s[i]);
        }
    }
    while (!st.empty())
        f[++m] = (Formula) {1, 0, st.top()}, st.pop();
}

int qpow(int a, int b)
{
    int ans = 1;
    for (int i = b; i; i >>= 1, a *= a)
        if (i & 1) ans *= a;
    return ans;
}

int getsum()
{
    stack<int> st;
    for (int i = 1; i <= m; i++) {
        if (f[i].type == 0) { st.push(f[i].v); continue; }
        int y = st.top(); st.pop();
        int x = st.top(); st.pop();
        switch (f[i].c) {
            case '+': st.push(x + y); break;
            case '-': st.push(x - y); break;
            case '*': st.push(x * y); break;
            case '/': st.push(x / y); break;
            case '^': st.push(qpow(x, y)); break;
        }
    }
    return st.top();
}

int main()
{
    cin >> s0, init(), n = s.length();
    change();
    printf("%d\n", getsum());
    return 0;
}