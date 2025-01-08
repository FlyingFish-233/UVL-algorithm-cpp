# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <iostream>
# include <fstream>

using namespace std;

void create_test_file(const char* fn, const char* str)
{   
    ofstream fout(fn);
    fout << str;
    fout.close();
}

void f0(const char* str)
{
    ifstream fin(str);
    while (1) {
        int data;
        fin >> data;
        if (fin.eof()) break;
        cout << data << ' ';
    }
    cout << endl;
}

void f1(const char* str)
{
    ifstream fin(str);
    while (!fin.fail()) {
        int data;
        fin >> data;
        cout << data << ' ';
    }
    cout << endl;
}

void f2(const char* str)
{
    ifstream fin(str);
    while (!fin.eof()) {
        int data;
        fin >> data;
        cout << data << ' ';
    }
    cout << endl;
}

void f3(const char* str)
{
    ifstream fin(str);
    int data;
    while (fin >> data)
        cout << data << ' ';
    cout << endl;
}

int main()
{
    void (*pf[4])(const char*) = {f0, f1, f2, f3};
    char test_data[7][10] = {"1 2", "1 2 ", "1 2\n", "1 2 \n", "1\n2", "1\n2 ", "1\n2\n"};
    for (int i = 0; i < 7; i++) {
        char fn[20];
        sprintf(fn, "save\\in%d.txt", i);
        create_test_file(fn, test_data[i]);//生成测试文件,包含不同的文本数据
        cout << "Case " << i << " testing... " << endl;
        for (int j = 0; j < 4; j++) pf[j](fn);
        cout << endl;
}
    return 0;
}