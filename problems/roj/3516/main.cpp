/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:40
 * update_at: 2026-10-06 12:40
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 105;

ll a[MAXN]; // 每堆纸牌数量

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    ll sum = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sum += a[i];
    }
    ll avg = sum / n; // 每堆最终张数：总数必为 n 的倍数

    // 贪心：第 i 堆只能与 i+1 堆交互，其差额必须一次搬完；搬完后第 i 堆永久定型为 avg。
    // 依次处理到第 n-1 堆，每堆不等于 avg 就做一次移动，把差额整体推给右邻。
    int moves = 0;
    for (int i = 1; i <= n - 1; ++i) {
        if (a[i] != avg) {
            moves++;              // 一次移动可搬任意张数，只计次数
            a[i + 1] += a[i] - avg; // 右邻接管差额，本堆定型为 avg
        }
    }
    cout << moves << '\n';
    return 0;
}
