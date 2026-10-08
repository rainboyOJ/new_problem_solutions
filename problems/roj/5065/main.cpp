/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 01:43
 * update_at: 2026-10-09 01:43
 */
// 一本通 2064 【例2.1】交换值
// 题面：输入两个正整数 a 和 b，交换它们的值后输出（a 输出原 b，b 输出原 a）。
// 题面未声明 a、b 的取值范围；实测 10 个测试点里最大值为 2147483647（即 INT_MAX，
// 见 problem2 / problem9 / problem10），没有出现 INT_MIN。按项目 skill
// 「题目数据默认 long long」统一用 ll 读写（这是规范问题：本题只做赋值、
// 不涉及任何算术，int 同样能过且不会溢出）。
#include <iostream>

using namespace std;

typedef long long ll;

ll a; // 第一个正整数
ll b; // 第二个正整数

// 借助临时变量交换 a、b 的值：先把 a 存进 t，再用 b 覆盖 a，最后用 t 还原 b。
// 全程只有赋值，没有任何算术运算，因此不存在溢出风险。
void solve() {
    if (!(cin >> a >> b)) return;

    ll t = a;
    a = b;
    b = t;

    // 交换后 a 是原 b、b 是原 a，中间一个空格，行末一个换行
    cout << a << " " << b << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
