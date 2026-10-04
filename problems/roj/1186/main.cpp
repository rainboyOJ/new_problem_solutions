/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:41
 * update_at: 2026-10-05 04:41
 */

#include <iostream>
using namespace std;

typedef long long ll;

const int OFFSET = 50;          // 把 -49..49 平移到 0..98 的桶偏移
const int MAXB = 100;           // 桶数量，覆盖值域 [-49, 49] 共 99 个值

int cnt[MAXB];                  // cnt[i] 表示值 (i - OFFSET) 出现的次数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;  // 数组大小
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;               // 读入数组元素
        cnt[x + OFFSET]++;      // 桶计数
    }

    // 找出现次数最多的值
    int best_id = 0;            // 众数对应的桶下标
    for (int i = 0; i < MAXB; ++i) {
        if (cnt[i] > cnt[best_id]) best_id = i;
    }
    int times = cnt[best_id];   // 众数出现次数
    int value = best_id - OFFSET; // 还原为真实数值

    // 严格过半：times / n > 1/2 等价于 2 * times > n，整数比较避免浮点
    if (2 * times > n) cout << value << "\n";
    else cout << "no\n";

    return 0;
}