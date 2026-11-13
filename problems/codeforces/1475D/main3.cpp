/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-13 10:00
 * update_at: 2026-11-13 10:00
 */
// main3.cpp：解法 3 反悔贪心（全选代价1物品，逐个换入代价2物品并最大化退货）
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 200000 + 50;
const long long INF = 1e18;

long long a[maxn];
int b[maxn];

long long one[maxn];
long long two[maxn];

void solve() {
    int n;
    long long m;
    if (!(cin >> n >> m)) return;

    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];

    int cnt1 = 0, cnt2 = 0;
    for (int i = 1; i <= n; ++i) {
        if (b[i] == 1) {
            one[++cnt1] = a[i];
        } else {
            two[++cnt2] = a[i];
        }
    }

    sort(one + 1, one + cnt1 + 1, greater<long long>());
    sort(two + 1, two + cnt2 + 1, greater<long long>());

    // 第一阶段：贪心构造初始基线
    // 优先全选队伍 A（代价为 1），直到总空间满足 >= m
    long long cur_space = 0;
    int x = 0;
    while (x < cnt1 && cur_space < m) {
        x++;
        cur_space += one[x];
    }

    // 如果队伍 A 全选后依然不够，不得不向队伍 B 借调（代价为 2）
    int y = 0;
    while (y < cnt2 && cur_space < m) {
        y++;
        cur_space += two[y];
    }

    // 倾尽全力仍无法达到 m，无解
    if (cur_space < m) {
        cout << -1 << "\n";
        return;
    }

    // 关键修正：借调完成后，总空间可能已经溢出，若手里有队伍 A 的物品，先执行最大化退货
    while (x > 0 && cur_space - one[x] >= m) {
        cur_space -= one[x];
        x--;
    }

    // 记录初始有效基线代价
    long long ans = (long long)x + 2LL * y;

    // 第二阶段：反悔替换
    // 逐个尝试向队伍 B 增选更大的应用（y 逐渐增大），并尽可能“退回”手里最小的队伍 A 应用（x 减少）
    while (y < cnt2) {
        y++;
        cur_space += two[y]; // 买入 2 元大件，增加空间

        // 反悔退货：只要手里还有队伍 A 的物品，且退掉后空间依然 >= m，就果断退掉节省花费
        while (x > 0 && cur_space - one[x] >= m) {
            cur_space -= one[x];
            x--;
        }

        ans = min(ans, (long long)x + 2LL * y);
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
