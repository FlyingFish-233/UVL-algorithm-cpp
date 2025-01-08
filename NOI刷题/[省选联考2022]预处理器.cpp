// P8289 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <iostream>
# include <unordered_map>

using namespace std;

unordered_map<string, pair<string, bool> > def;

bool check(char c)
{
    if (c >= 'a' && c <= 'z') return true;
    if (c >= 'A' && c <= 'Z') return true;
    if (c >= '0' && c <= '9') return true;
    return c == '_';
}

string dfs(string s)
{
    string ans;
    for (int i = 0, j; i < s.length(); i += j) {
        for (j = 0; i + j < s.length() && check(s[i + j]); j++);
        if (j == 0) { ans += s[i++]; continue; }
        string tmp = s.substr(i, j);
        if (def.count(tmp) == 0 || def[tmp].second) ans += tmp;
        else def[tmp].second = true, ans += dfs(def[tmp].first), def[tmp].second = false;
    }
    return ans;
}

int main()
{
    int T;
    scanf("%d\n", &T);
    while (T--) {
        string s;
        getline(cin, s);
        if (s[0] == '#') {
            if (s.substr(1, 6) == "define") {
                int p = s.find(' ', 8);
                def[s.substr(8, p - 8)] = make_pair(s.substr(p + 1), false);
            }
            if (s.substr(1, 5) == "undef")
                def.erase(s.substr(7));
            cout << endl;
        }
        else cout << dfs(s) << endl;
    }
    return 0;
}



