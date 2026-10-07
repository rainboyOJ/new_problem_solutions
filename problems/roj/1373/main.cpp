/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:23
 * update_at: 2026-10-05 12:23
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 105;
const int MAXT = 1005;

ll f[MAXN];      // 第 i 个鱼塘第 1 分钟能钓到的鱼数
ll d[MAXN];      // 第 i 个鱼塘每分钟钓鱼数的减少量
ll t[MAXN];      // 从第 i 个鱼塘走到第 i+1 个鱼塘的时间
ll picks[MAXN * MAXT]; // 所有鱼塘展开后的每分钟收益
int pick_cnt;    // picks 当前有效长度

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> f[i];
    for (int i = 1; i <= n; ++i) cin >> d[i];
    for (int i = 1; i < n; ++i) cin >> t[i];
    int T;
    cin >> T;

    ll best = 0;
    ll spent = 0; // 走到当前最远鱼塘累计花费的路程时间
    pick_cnt = 0;

    for (int L = 1; L <= n; ++L) {
        int left = T - spent; // 剩余可用于钓鱼的分钟数
        if (left < 0) break;  // 时间已不够走到更远的鱼塘

        // 把第 L 个鱼塘的每分钟收益展开并加入 picks
        ll cur = f[L];
        while (cur > 0) {
            picks[pick_cnt++] = cur;
            cur -= d[L];
        }

        // 降序排序，取前 left 大求和
        sort(picks, picks + pick_cnt, greater<ll>());
        ll sum = 0;
        int use = min(left, pick_cnt);
        for (int i = 0; i < use; ++i) sum += picks[i];
        if (sum > best) best = sum;

        if (L < n) spent += t[L];
    }

    cout << best << "\n";
    return 0;
}
