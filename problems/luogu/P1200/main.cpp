/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

char comet[10], group[10]; // 彗星名和团队名

// 计算名字的模 47 值：字母编号乘积 % 47
int name_value(char *name) {
    int res = 1;
    int len = strlen(name);
    for (int i = 0; i < len; i++) {
        int num = name[i] - 'A' + 1; // A=1, B=2, ...
        res = res * num % 47;
    }
    return res;
}

int main() {
    cin >> comet >> group;
    if (name_value(comet) == name_value(group))
        cout << "GO";
    else
        cout << "STAY";
    return 0;
}
