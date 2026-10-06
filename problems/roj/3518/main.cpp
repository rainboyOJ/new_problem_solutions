/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:40
 * update_at: 2026-10-06 12:42
 */
#include <cmath>
#include <iostream>
using namespace std;

typedef long long ll;

// 题目数据与时间计算的浮点常量
const double EPS = 1e-4;    // 题目容差：球与车的水平距离不超过它就算接住
const double FUDGE = 1e-7;  // 浮点护栏：防止恰好压在边界上的整数被舍入误差挤掉
const double G_HALF = 5.0;  // 自由落体 d = 0.5*g*t^2，g = 10，故系数为 5

int main() {
    double H;   // 天花板高度
    double S1;  // 车头距原点的初始距离
    double V;   // 小车前进速度
    double L;   // 车长
    double K;   // 车高
    double n_in; // 小球个数（以浮点读入，后面取整）

    cin >> H >> S1 >> V >> L >> K >> n_in;
    ll n = n_in;

    // 球从 H 落到地面、落到车顶高度 K 分别需要的时间
    double t_ground = sqrt(H / G_HALF);
    double t_roof = sqrt(max(H - K, 0.0) / G_HALF); // K >= H 时球一开始就在车顶高度

    // 球只在 t ∈ [t_roof, t_ground] 内可能被接住；这段时间里车头 e(t) = S1 - V*t
    // 单调左移，车身区间扫过的并集仍是一段，取两个端点即可：
    double lo = S1 - V * t_ground - EPS;          // 最晚时刻车头扫到的最左位置
    double hi = S1 - V * t_roof + L + EPS;        // 最早时刻车尾扫到的最右位置

    // 编号 0..n-1 的球落在 [lo, hi] 内的全部被接住，数其中的整数个数
    ll left = ceil(lo - FUDGE);
    ll right = floor(hi + FUDGE);
    if (left < 0) left = 0;
    if (right > n - 1) right = n - 1;

    ll ans = right - left + 1;
    if (ans < 0) ans = 0;
    cout << ans << endl;

    return 0;
}
