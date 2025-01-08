// P3378 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e6 + 10;

struct Node
{
    int ch, bro, val, fa;
};

int tot, root;
Node h[NR];

int newNode(int val)
{
    h[++tot].val = val;
    return tot;
}

int merge(int x, int y)
{
    if (x == 0 || y == 0) return x + y;
    if (h[x].val > h[y].val) swap(x, y);
    h[h[x].ch].fa = y, h[y].fa = x;
    h[y].bro = h[x].ch, h[x].ch = y;
    return x;
}

int merges(int x)
{
    h[x].fa = 0;
    if (x == 0 || h[x].bro == 0) return x;
    int y = h[x].bro, z = h[y].bro;
    h[y].fa = h[x].bro = h[y].bro = 0;
    return merge(merge(x, y), merges(z));
}

void decrease_key(int x, int val)
{
    h[x].val = val;
    if (h[x].fa == 0) { root = x; return; }
    if (h[h[x].fa].ch == x) h[h[x].fa].ch = h[x].bro;
    else h[h[x].fa].bro = h[x].bro;
    h[h[x].bro].fa = h[x].fa, h[x].fa = h[x].bro = 0;
    root = merge(root, x);
}

int main(){
    int T;
    scanf("%d", &T);
    while (T--) {
        int op, x;
        scanf("%d", &op);
        if (op == 1) scanf("%d", &x), root = merge(root, newNode(x));
        if (op == 2) printf("%d\n", h[root].val);
        if (op == 3) root = merges(h[root].ch);
    } 
} 
