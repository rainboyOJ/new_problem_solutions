/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:18
 * update_at: 2026-10-05 09:18
 */
// main.cpp：排队接水。
// 贪心：按接水时间升序排序；总等待 = Σ (n-1-pos)*t[pos]，平均 = 总等待 / n。

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

typedef long long ll;

const int MAXN = 1005;

int n;
int t[MAXN];                 // 第 i 个人的接水时间（缺项补 0）

void read_input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> t[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();

    // 把 (时间, 编号) 一起排序，std::sort 非稳定，输出顺序与参考答案一致。
    vector<pair<int,int>> a;
    a.reserve(n);
    for (int i = 1; i <= n; i++) a.emplace_back(t[i], i);
    sort(a.begin(), a.end());

    // 第 pos 位（从 0 计）的等待权为 n-1-pos，求加权和再除以 n。
    ll total = 0;
    for (int pos = 0; pos < n; pos++) total += (ll)a[pos].first * (n - 1 - pos);

    cout.setf(ios::fixed); cout << setprecision(2);
    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << a[i].second;
    }
    cout << "\n" << (double)total / n << "\n";

    return 0;
}
