/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 02:08
 * update_at: 2026-10-09 02:08
 */
// 一本通 2066《【例2.3】买图书》（ROJ 5067）
//
// 题意：小明有 n 元，买一本原价 m 元的书，书打 8 折（付 0.8*m 元），
//       求还剩多少钱，保留 2 位小数。样例 `100 100` -> `20.00`。
//
// 题面未声明 n、m 的类型与范围，随仓 10 个测试点实测全为整数（最大 10^6），
// 故按 double 读入：既兼容题面的整数，也兼容小数金额。
//
// 【为什么需要「零附近归一化」】数学答案为 0 时（n = 0.8m，如 80 100），
// double 计算 n - m*0.8 会留下 ±4.4e-15 量级的舍入残差；残差为负时
// printf/cout 会打印 "-0.00"（本机 -O2 实测：不加这一行，problem4 输出 -0.00）。
// 答案的精确值是 0.2 的整数倍，最小非零绝对值 0.2，而 m <= 10^6 时
// double 的绝对误差上界实测为 9.3e-11（全枚举 m ∈ [0, 10^6] 得到），
// 因此 |rest| < 1e-6 只可能来自舍入误差，归零是安全的。
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

typedef long long ll;

const double DISC = 0.8;      // 8 折 = 按原价的 80% 付款
const double ZERO_EPS = 1e-6; // 零附近归一化阈值，见文件头说明

double n; // 小明原有的钱（元）
double m; // 书原价（元）

// 计算买书后剩余的钱并保留 2 位小数输出。
// 精确值 = n - 4m/5，分母至多 10，小数位最多 1 位 ⇒ 保留 2 位小数是精确补零，
// 不存在舍入平局，printf("%.2f") 与 Python f-string 必然逐字节一致。
void solve() {
    double rest = n - m * DISC;
    if (fabs(rest) < ZERO_EPS) { // 消除因浮点残差产生的 "-0.00"
        rest = 0.0;
    }
    cout << fixed << setprecision(2) << rest << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (cin >> n >> m) {
        solve();
    }
    return 0;
}
