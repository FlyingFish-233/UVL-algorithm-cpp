# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <iostream>

using namespace std;

void test(int ** a, int len1, int len2)
{

    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < len2; j++)
            printf("%02d ", a[i][j]);
        puts("");
    }
}

int main()
{
    int **e;
    e = new int*[4];
    for (int i = 0; i < 4; i++) e[i] = new int[3];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            e[i][j] = 10 * i + j;
    test(e, 4, 3);
    for (int i = 0; i < 4; i++) delete[] e[i];
    delete[] e;
    return 0;
}