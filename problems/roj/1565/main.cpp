/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 08:34
 * update_at: 2026-10-09 08:34
 */
#include <iostream>
#include <set>

using namespace std;

typedef long long ll;

const int MAXN = 32770;       // n < 2^15 = 32768，再留一点余量
const int INF = 2000000000;   // 候选差值的哨兵，只需大于 max|a_i - a_j|

int n;
int a[MAXN]; // 每天的营业额；|a_i| <= 10^6，用 int 足够

void read_input() {
    if (!(cin >> n)) return;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
}

// 用有序集合维护「已经出现过的营业额」，逐天累加最小波动值：
// 第 i 天 (i >= 2) 在集合里取 a[i] 的前驱与后继，f_i = 两者差值绝对值的较小者；
// 第 1 天的最小波动值就是当天的营业额（题面规定），直接累加 a[1]。
void solve() {
    set<int> appeared; // 已经出现过的营业额，始终有序
    ll total = 0;      // 答案；题面称不超过 2^31，仍用 64 位防临界溢出

    for (int i = 1; i <= n; ++i) {
        if (i == 1) {
            total += a[i];
            appeared.insert(a[i]);
            continue;
        }

        // lower_bound 给出第一个 >= a[i] 的元素，即后继
        set<int>::iterator it = appeared.lower_bound(a[i]);
        int min_diff = INF; // i >= 2 时集合非空，前驱/后继至少命中一个，下界一定被更新

        if (it != appeared.end()) {
            int diff = *it - a[i];
            if (diff < 0) diff = -diff;
            if (diff < min_diff) min_diff = diff;
        }
        if (it != appeared.begin()) {
            set<int>::iterator pred_it = it;
            --pred_it; // 前驱：小于 a[i] 的最大元素
            int diff = a[i] - *pred_it;
            if (diff < 0) diff = -diff;
            if (diff < min_diff) min_diff = diff;
        }

        total += min_diff;
        appeared.insert(a[i]);
    }

    cout << total << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
