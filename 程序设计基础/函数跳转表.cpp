# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <iostream>

using namespace std;

void bubble(int data[], int num, bool (*op) (int, int)) {
    for (int i = 0; i < num - 1; i++)
        for (int j = 0; j < num - 1 - i; j++)
            if (op(data[j], data[j+1]))
                swap(data[j], data[j + 1]);
}

bool op1(int a, int b) { return a > b; }
bool op2(int a, int b) { return a < b; }

int main()
{
    bool (*pf[2]) (int, int) = {op1, op2};
    int data[] = {8, 4, 7, 9, 3, 5, 1}, cmp_type;
    scanf("%d", &cmp_type);
    printf("2>1? %d\n", pf[cmp_type](2, 1));
    bubble(data, 7, pf[cmp_type]);
    for (int i = 0; i < 7; i++)
        printf("%d ", data[i]);
    puts("");
}