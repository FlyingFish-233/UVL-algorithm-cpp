# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <iostream>

using namespace std;

const int NR = 1e6 + 10;

typedef unsigned int LL;

int now, tot, trie[NR << 1][2], id[NR << 1];

void insert(LL v, int y)
{
    int rt = 0;
    for (int i = 31; i >= 0; i--) {
        int k = (v >> i) & 1;
        if (trie[rt][k] == 0) trie[rt][k] = ++tot;
        rt = trie[rt][k];
        if (i == 32 - y) id[rt] = now;
    }
}

int top, s[NR];

int getans(LL v, int y, int z)
{
    int rt = 0; top = 0;
    for (int i = 31; i >= 0; i--) {
        int k = (v >> i) & 1;
        if (trie[rt][k] == 0) break;
        rt = trie[rt][k];
        if (id[rt]) {
            while (s[top] > id[rt]) top--;
            s[++top] = id[rt];
        }
    }
    return upper_bound(s + 1, s + top + 1, z) - lower_bound(s + 1, s + top + 1, y);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        char c; cin >> c;
        int x1, x2, x3, x4, y, z;
        if (c == 'A')
            scanf("%d.%d.%d.%d/%d", &x1, &x2, &x3, &x4, &y), ++now, insert((LL) (x1 << 24) + (x2 << 16) + (x3 << 8) + x4, y);
        if (c == 'Q') {
            scanf("%d.%d.%d.%d %d %d", &x1, &x2, &x3, &x4, &y, &z), printf("%d\n", getans((LL) (x1 << 24) + (x2 << 16) + (x3 << 8) + x4, y, z));
        }
    }
    return 0;
}

