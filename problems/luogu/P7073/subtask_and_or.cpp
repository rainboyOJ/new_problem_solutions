/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-11 21:51
 * update_at: 2026-10-11 21:51
 */
/*
 * subtask_and_or.cpp：P7073 的 20% 档（表达式中只有一种二元运算）
 *
 * 这一档保证表达式里只有 & 或者只有 |，且不含 !。
 * 又因为每个变量恰好出现一次，同一种二元运算满足结合律：
 *   - 只有 &  => 整个表达式 = x1 & x2 & ... & xn（全为 1 才是 1）
 *   - 只有 |  => 整个表达式 = x1 | x2 | ... | xn（有一个 1 就是 1）
 * 所以根本不用建树，统计 1 的个数就能回答每次询问。
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读表达式：只需要认出唯一出现的二元运算符，表达式结构本身不用管
    string tok;
    char op = 0;
    while (cin >> tok) {
        if (tok[0] >= '0' && tok[0] <= '9') {
            break; // 读到 n（表达式之后的第一个数字），此时 n 已经在 tok 里
        }
        if (tok[0] == '&' || tok[0] == '|') {
            op = tok[0]; // 该档只会出现其中一种
        }
    }
    int n = stoi(tok);

    int ones = 0; // 初值里 1 的个数
    vector<int> value(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> value[i];
        ones += value[i];
    }

    int q;
    cin >> q;
    while (q--) {
        int k;
        cin >> k;
        // 翻转 x_k：先减掉旧值，再加上取反后的值
        int new_ones = ones - value[k] + (1 - value[k]);
        if (op == '&') {
            // 全与：翻转后每个变量都是 1，结果才是 1
            cout << (new_ones == n ? 1 : 0) << '\n';
        } else {
            // 全或：翻转后至少有一个 1，结果就是 1
            cout << (new_ones > 0 ? 1 : 0) << '\n';
        }
    }
    return 0;
}
