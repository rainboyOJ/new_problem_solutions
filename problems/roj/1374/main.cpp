/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 15:03
 * update_at: 2026-10-08 15:03
 */
// 一本通 1374《铲雪车(snow)》
// 每条街道都是双向单车道，拆成一正一反两条有向边后每个顶点入度=出度，
// 又保证"从起点可达任何街道"（连通），所以图存在欧拉回路：
// 铲雪车能一路铲着雪走遍所有车道再回到起点，全程 20 km/h，不会有 50 km/h 的空驶。
// 答案 = 所有街道长度之和 × 2 ÷ 20000 小时（街道按双车道各走一次）。
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

double total_distance; // 所有街道的单向长度之和，单位米

// 读入停车点坐标（题意用不到，只按格式消费）与全部街道端点，累加街道长度
void read_input() {
    ll start_x, start_y;
    if (!(cin >> start_x >> start_y)) return;

    ll x1, y1, x2, y2;
    while (cin >> x1 >> y1 >> x2 >> y2) {
        double dx = x1 - x2;
        double dy = y1 - y2;
        total_distance += sqrt(dx * dx + dy * dy);
    }
}

// 时间(分钟) = 总路程(米) × 2 ÷ 20000(米/小时) × 60 = total_distance × 0.006，
// 四舍五入到整分钟，再按 小时:分钟 输出（分钟补两位零）
void solve() {
    ll total_minutes = floor(total_distance * 0.006 + 0.5);
    ll hour = total_minutes / 60;
    ll minute = total_minutes % 60;
    cout << hour << ":" << setfill('0') << setw(2) << minute << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
