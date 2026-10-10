/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 00:41
 * update_at: 2026-10-09 00:41
 */
// 一本通 5055《【例3.3】三个数》
// 题面只要求「按从大到小的顺序输出」，未指定实现手段，故用三次比较交换。
// 数据里含 32 位极值（problem1 三个 -2147483648、problem2 三个 2147483647），
// 实现全程只做比较与赋值，不做取反/取绝对值/求和，因此用 int 也不会溢出；
// 这里默认用 ll 存题目数据，彻底规避边界风险。
#include <iostream>

using namespace std;

typedef long long ll;

ll a, b, c; // 输入的三个整数

// 三次比较交换，把 a、b、c 排成降序 a >= b >= c。
void solve() {
    if (a < b) { // 先保证 a >= b
        ll temp = a;
        a = b;
        b = temp;
    }
    if (a < c) { // 再保证 a >= c，此时 a 已是三者最大
        ll temp = a;
        a = c;
        c = temp;
    }
    if (b < c) { // 最后保证 b >= c
        ll temp = b;
        b = c;
        c = temp;
    }
    // 单空格分隔、行末换行（实测 .out 无行尾空格）
    cout << a << " " << b << " " << c << "\n";
}

int main() {
    if (!(cin >> a >> b >> c)) return 0; // 无输入时静默退出
    solve();
    return 0;
}
