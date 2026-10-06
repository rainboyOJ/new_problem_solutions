/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:47
 * update_at: 2026-10-06 09:47
 */
#include <iostream>
using namespace std;

// 五个轮子共用这些全局数组：ns[k][j] 是轮 k 第 j 个缺口的起始角度，nl[k][j] 是张角
const int DEG = 360; // 角度模数：转过 359 度后回到 0 度
int v[5];            // v[k]：轮 k 的转速（度/秒）
int w[5];            // w[k]：轮 k 的缺口个数
int ns[5][5];        // 缺口起始角度
int nl[5][5];        // 缺口张角（闭区间，覆盖 len+1 个角度）

// 判断轮子 id 在时刻 t、角度 d 处是否被某个缺口盖住
bool covered(int id, int t, int d) {
    for (int j = 0; j < w[id]; ++j) {
        // 缺口在时刻 t 的起点：整体转过 v*t 度再取模
        int start = (ns[id][j] + v[id] * t) % DEG;
        // d 相对缺口起点沿转动方向的偏移，落在 [0, len] 内即被盖住（闭区间）
        int diff = (d - start + DEG) % DEG;
        if (diff <= nl[id][j]) return true;
    }
    return false;
}

int main() {
    // 读入五个轮子：转速、缺口数、每个缺口的起始角度和张角
    for (int k = 0; k < 5; ++k) {
        cin >> v[k] >> w[k];
        for (int j = 0; j < w[k]; ++j) cin >> ns[k][j] >> nl[k][j];
    }
    // 轮子在时刻 t 的图案只由 v*t mod 360 决定，整体图案以 360 秒为周期，
    // 所以只枚举 t = 0..359；一圈都没有公共角度就是无解
    for (int t = 0; t < DEG; ++t) {
        for (int d = 0; d < DEG; ++d) {
            bool ok = true;
            // 检查五个轮子在角度 d 处是否都有缺口（光能否穿过）
            for (int k = 0; k < 5; ++k) {
                if (!covered(k, t, d)) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                cout << t << endl;
                return 0;
            }
        }
    }
    cout << "none" << endl;
    return 0;
}
