# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <iostream>

using namespace std;

int main()
{
    int f[5][5], **e = new int*[5];
    for (int i = 0; i < 5; i++) {
        e[i] = new int[5];
        for (int j = 0; j < 5; j++)
            f[i][j] = e[i][j] = j;
    }
    for (int i = 0; i < 25; i++)
        cout << *(e[0] + i) << " ";
    cout << endl;
    for (int i = 0; i < 25; i++)
        cout << *(f[0] + i) <<" ";
    cout << endl;

    return 0;
}