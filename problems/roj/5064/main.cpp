/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 01:40
 * update_at: 2026-10-09 01:40
 */
#include <iostream>

using namespace std;

typedef long long ll;

// 题面给出的两组观测：n1 头牛正好吃 t1 天，n2 头牛正好吃 t2 天
ll n1 = 15;
ll t1 = 20;
ll n2 = 20;
ll t2 = 10;

// 每天新生的草量可供几头牛吃 1 天（一头牛吃一天的草量记作 1 个单位草）。
//
// 设牧场初始草量为 G、每天新生草量为 g，两组观测给出：
//     G + t1 * g = n1 * t1
//     G + t2 * g = n2 * t2
// 两式相减消去 G，得 (t1 - t2) * g = n1 * t1 - n2 * t2，于是
//     g = (n1 * t1 - n2 * t2) / (t1 - t2)
// 本题这个商恰好是整数，直接用整数除法即可。
void solve() {
    ll eaten_diff = n1 * t1 - n2 * t2; // 两组观测总消耗草量之差 = 多吃的天数里新生的草量
    ll days_diff = t1 - t2;            // 两组观测的吃草天数之差
    cout << eaten_diff / days_diff << "\n";
}

int main() {
    solve();
    return 0;
}
