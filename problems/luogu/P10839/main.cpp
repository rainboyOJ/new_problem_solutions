/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:01
 * update_at: 2026-08-14 15:05
 */
// P10839 【MX-J2-T0】Turtle and Equations
// 枚举两个方框的运算符，共有 3*3=9 种组合。
// 本解对应 rbook 模板 enumerate-dynamic-loop：
// 递归实现 n 层循环，每层从 [0, m) 中选择一个值，这里是 2 层、每层 3 种运算符。
#include <bits/stdc++.h>
using namespace std;

int a, b, c, d;
char ops[3] = {'+', '-', '*'}; // 三种可用运算符
int choose[2];                 // choose[i]：第 i 个方框选中的运算符下标

// 计算 x op y。
int calc(int x, int y, char op) {
    if (op == '+') return x + y;
    if (op == '-') return x - y;
    return x * y;
}

// 递归枚举第 dep 个方框的运算符；填满两个方框后检查 (a op1 b) op2 c == d。
bool dfs(int dep) {
    if (dep == 2) {
        int mid = calc(a, b, ops[choose[0]]); // 先算括号内 a op1 b
        return calc(mid, c, ops[choose[1]]) == d;
    }
    for (int i = 0; i < 3; i++) {
        choose[dep] = i;
        if (dfs(dep + 1)) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b >> c >> d;
    cout << (dfs(0) ? "Yes" : "No") << '\n';

    return 0;
}
