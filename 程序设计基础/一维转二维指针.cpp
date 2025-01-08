#include <iostream>
using namespace std;

int** join(int **a, int **b, int m, int n, int x, int y){
    int **c, *d;
    c = new int*[x], d = new int[x * y];
    for (int i = 0; i < x; i++) c[i] = new int[y];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            d[2*(i * n + j)] = a[i][j];
            d[2*(i * n + j) + 1] = b[i][j];
        }
    for (int i = 0; i < x; i++)
        c[i] = d + i * y;
    return c;
}

int main(){
    int m, n, x, y;
    int **a, **b, **c;
    cin >> m >> n >> x >> y;
    a = new int*[m], b = new int*[m];
    for (int i = 0; i < m; i++) {
        a[i] = new int[n];
        for (int j = 0; j < n; j++) cin >> a[i][j];
    }
    for (int i = 0; i < m; i++) {
        b[i] = new int[n];
        for (int j = 0; j < n; j++) cin >> b[i][j];
    }
    c = join(a,b,m,n,x,y);
    for(int i=0; i<x; i++) {
        for(int j=0; j<y; j++) {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}