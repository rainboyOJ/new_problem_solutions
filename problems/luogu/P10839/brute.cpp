/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:01
 * update_at: 2026-08-14 15:05
 */
// brute.cpp：小数据暴力解，两重循环枚举两个方框的全部 3*3=9 种运算符组合，
// 与题意一一对应，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int a, b, c, d;

// 计算 x op y。
int calc(int x, int y, char op) {
    if (op == '+') return x + y;
    if (op == '-') return x - y;
    return x * y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b >> c >> d;

    char ops[3] = {'+', '-', '*'};
    bool ok = false;
    for (int i = 0; i < 3 && !ok; i++) {        // 第一个方框
        for (int j = 0; j < 3 && !ok; j++) {    // 第二个方框
            int mid = calc(a, b, ops[i]);       // 先算括号内 a op1 b
            if (calc(mid, c, ops[j]) == d) ok = true;
        }
    }

    cout << (ok ? "Yes" : "No") << '\n';
    return 0;
}
