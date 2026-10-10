/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 02:20
 * update_at: 2026-10-09 07:30
 */
// 一本通 2071《【例2.14】平均分》（ROJ 5072）
//
// 题意：x 位男生平均 87 分、y 位女生平均 85 分，求全班平均分，保留 4 位小数。
//   全体总分 87x + 85y，总人数 x + y，故 avg = (87x + 85y) / (x + y)。
// 题面（problem.md 与官方题面）未声明 x、y 的范围，也未指定实现手段
// （grep 「利用|循环|递归|不使用|必须用」与「（算法名）」均无命中），
// 故按仓库习惯自定范围 0 <= x, y <= 10^6，x + y >= 1。
//
// 【难点一：整数除法】两个整数相除是整除，会把小数部分截掉（2 3 会算成 85.0000），
//   所以必须先转成实数再除。这里用 `1.0 *` 抬成 double，不写强制转换。
// 【难点二：分子用 64 位】87x + 85y 在 x = y = 10^6 时是 1.72e8，
//   在 32 位 int 里其实也安全（远小于 2^31-1 = 2.147e9），
//   但题目数据默认用 ll，防将来范围加大后溢出。
//
// 注：x + y == 0（全班无人）时题面无定义，真实数据也没有这样的点；
//   此时是浮点除以 0.0，结果为 nan，不是未定义行为（UBSan 实测无误报）。

#include <iostream>
#include <iomanip>

using namespace std;

typedef long long ll;

ll x; // 男生人数
ll y; // 女生人数

// 读入 x、y，输出全班平均分，保留 4 位小数（末尾 0 补齐）。
void solve() {
    double avg = 1.0 * (87 * x + 85 * y) / (x + y); // 1.0 * 抬成实数除法，避免整除截断
    cout << fixed << setprecision(4) << avg << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (cin >> x >> y) { // 单组输入：一行两个人数
        solve();
    }
    return 0;
}
