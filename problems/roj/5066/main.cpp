/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 02:00
 * update_at: 2026-10-09 02:00
 */
// 一本通 2065《【例2.2】整数的和》（目标 ROJ 题号 5066）
// 题面：输入 a、b、c 这 3 个整数，输出它们的和（单组输入：一行三个整数）。
// 题面未声明取值范围；实测 10 个测试点里单个数的最大绝对值为 10^6
// （problem1 为 -1000000 -1000000 -1000000），三数之和的绝对值最多 3×10^6。
// 按项目 skill「题目数据默认 long long」统一用 ll 读写：对本题真实数据而言
// 这是规范问题（int 也不会溢出），但范围未声明时 ll 更稳妥。
#include <iostream>

using namespace std;

typedef long long ll;

ll a; // 第一个整数
ll b; // 第二个整数
ll c; // 第三个整数

// 读入三个整数并输出它们的和，只用一次加法，显式拆成中间变量便于阅读。
void solve() {
    if (!(cin >> a >> b >> c)) return;

    ll total = a + b + c; // 三数之和：ll 保证即使超出 32 位也不回绕

    cout << total << "\n"; // 输出只有一个整数，后跟一个换行，无行尾空格
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
