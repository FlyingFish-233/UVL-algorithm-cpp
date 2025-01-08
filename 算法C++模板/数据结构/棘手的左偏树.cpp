// P3273 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <set>

using namespace std;

const int NR = 3e5 + 10;

int read()
{
    char c = getchar(); int num = 0, flag = 1;
    for ( ; c < '0' || c > '9' ; c = getchar())
        if (c == '-') flag = -1;
    for ( ; c >= '0' && c <= '9'; c = getchar())
        num = num * 10 + c - '0';
    return flag * num;
}

struct Node
{
    int ls, rs, d, fa, val;
};

int n, m, all_tag;
Node h[NR];
int root[NR], tag[NR], sz[NR];
multiset<int> s;

int find(int x)
{
    if (root[x] == x) return x;
    return root[x] = find(root[x]);
}

void pushDown(int x, int delta)
{
    if (x == 0) return;
    h[x].val += delta;
    pushDown(h[x].ls, delta);
    pushDown(h[x].rs, delta);
}

int& R(int x)
{
    if (h[h[x].ls].d > h[h[x].rs].d) return h[x].rs;
    return h[x].ls;
}

int merge(int x, int y)
{
    if (x == 0 || y == 0) return x + y;
    if (h[x].val < h[y].val) swap(x, y);
    h[R(x) = merge(R(x), y)].fa = x;
    h[x].d = h[R(x)].d + 1;
    return x;
}

int del(int x)
{
    int y = merge(h[x].ls, h[x].rs); h[y].fa = h[x].fa;
    if (h[x].fa != 0 && h[h[x].fa].ls == x) h[h[x].fa].ls = y;
    if (h[x].fa != 0 && h[h[x].fa].rs == x) h[h[x].fa].rs = y;
    for (int z = h[x].fa; z && h[z].d != h[R(z)].d + 1; z = h[z].fa)
        h[z].d = h[R(z)].d + 1;
    h[x].ls = h[x].rs = h[x].fa = h[x].d = 0;
    return y;
}

int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
        root[i] = i, sz[i] = 1, s.insert(h[i].val = read());
    int T = read();
    char op[10]; int x, y;
    while (T--) {
        scanf("%s", op);

        if (op[0] == 'U') {
            x = find(read()), y = find(read());
            if (x == y) continue;
            if (sz[x] > sz[y]) swap(x, y);
            pushDown(x, tag[x] - tag[y]);
            root[x] = root[y] = merge(x, y);
            if (root[x] == x) {
                s.erase(s.find(h[y].val + tag[y]));
                tag[x] = tag[y], sz[x] += sz[y], tag[y] = sz[y] = 0;
            }
            else {
                s.erase(s.find(h[x].val + tag[y]));
                sz[y] += sz[x], tag[x] = sz[x] = 0;
            }
        }

        if (op[0] == 'A') {
            if (op[1] == '1') {
                x = read();
                if (h[x].fa == 0) {
                    y = del(x);
                    s.erase(s.find(h[x].val + tag[x]));
                    h[x].val += read();
                    root[x] = root[y] = merge(x, y);
                    s.insert(h[root[x]].val + tag[x]);
                    if (root[x] == y) tag[y] = tag[x], sz[y] = sz[x], tag[x] = sz[x] = 0;
                }
                else {
                    del(x), h[x].val += read();
                    y = find(x), root[x] = root[y] = merge(x, y);
                    if (root[x] == x) {
                        s.erase(s.find(h[y].val + tag[y]));
                        s.insert(h[x].val + tag[y]);
                        tag[x] = tag[y], sz[x] = sz[y], tag[y] = sz[y] = 0;
                    }
                }
            }
            if (op[1] == '2') {
                x = find(read());
                s.erase(s.find(h[x].val + tag[x]));
                tag[x] += read();
                s.insert(h[x].val + tag[x]);
            }
            if (op[1] == '3') all_tag += read();
        }

        if (op[0] == 'F') {
            if (op[1] == '1') x = read(), printf("%d\n", h[x].val + tag[find(x)] + all_tag);
            if (op[1] == '2') x = find(read()), printf("%d\n", h[x].val + tag[x] + all_tag);
            if (op[1] == '3') printf("%d\n", *s.rbegin() + all_tag);
        }
    }
    return 0;
}