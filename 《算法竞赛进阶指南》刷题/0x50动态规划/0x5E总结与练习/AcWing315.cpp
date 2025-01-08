# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 100;

int n1, n2;
string s1, s2;
int f[NR][NR];
int pre1[NR][30], pre2[NR][30];
vector<string> v;

void dfs(int i, int j, int rest, string s)
{
    if (rest == 0) { v.push_back(s); return; }
    for (int c = 1; c <= 26; c++) {
        int i0 = pre1[i][c], j0 = pre2[j][c];
        if (f[i0][j0] == rest) dfs(i0 - 1, j0 - 1, rest - 1, (char) (c + 'a' - 1) + s);
    }
}

int main()
{
    cin >> s1 >> s2;
    n1 = s1.size(), n2 = s2.size();
    s1 = " " + s1, s2 = " " + s2;
    for (int i = 1; i <= n1; i++)
        for (int j = 1; j <= n2; j++) {
            f[i][j] = max(f[i][j], max(f[i - 1][j], f[i][j - 1]));
            if (s1[i] == s2[j]) f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
        }
    for (int i = 1; i <= n1; i++)
        for (int j = 1; j <= 26; j++)
            if (s1[i] == j + 'a' - 1) pre1[i][j] = i;
            else pre1[i][j] = pre1[i - 1][j];
    for (int i = 1; i <= n2; i++)
        for (int j = 1; j <= 26; j++)
            if (s2[i] == j + 'a' - 1) pre2[i][j] = i;
            else pre2[i][j] = pre2[i - 1][j];
    dfs(n1, n2, f[n1][n2], "");
    sort(v.begin(), v.end());
    for (int i = 0; i < (int) v.size(); i++)
        cout << v[i] << endl;
    return 0;
}