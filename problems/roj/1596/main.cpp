/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:52
 * update_at: 2026-10-05 11:52
 */
// main.cpp：环形状态压缩 DP 求解最多高兴的小朋友数。
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 10005;      // 围栏数上限
const int MAXC = 50005;      // 小朋友数上限
const int STATES = 32;       // 连续 5 个围栏的留/移状态数 2^5
const int NEG = -1000000000; // 不可达状态的初值，比任何合法得分都小

ll fence_n;  // 围栏数 N
ll child_cnt; // 小朋友数 C

int head[MAXN];        // head[e]：起始围栏为 e 的小朋友链表头
int nxt_child[MAXC];   // 小朋友链表的后继
int afraid_mask[MAXC]; // 该小朋友害怕的围栏在窗口内的 5 位掩码，位 j 对应围栏 e+j
int fond_mask[MAXC];   // 该小朋友喜欢的围栏在窗口内的 5 位掩码
int edge_cnt;

int gain[MAXN][STATES]; // gain[e][s]：窗口起点为 e、5 位保留情况为 s 时高兴的小朋友数

int cur[STATES];    // 当前窗口状态的最高得分
int next_dp[STATES]; // 窗口右移一格后的最高得分

// 把小朋友挂到起点 e 的链表上。
void add_child(ll e, int afraid, int fond) {
    edge_cnt++;
    afraid_mask[edge_cnt] = afraid;
    fond_mask[edge_cnt] = fond;
    nxt_child[edge_cnt] = head[e];
    head[e] = edge_cnt;
}

// 预计算 gain 表：只在小朋友视野起点处结算一次得分。
void build_gain() {
    for (ll e = 1; e <= fence_n; e++) {
        for (int s = 0; s < STATES; s++) {
            int cnt = 0;
            for (int i = head[e]; i != 0; i = nxt_child[i]) {
                // 高兴：有害怕的动物被移走（掩码位为 0）或有喜欢的动物被保留（掩码位为 1）。
                if ((afraid_mask[i] & ~s) != 0 || (fond_mask[i] & s) != 0) {
                    cnt++;
                }
            }
            gain[e][s] = cnt;
        }
    }
}

void read_input() {
    cin >> fence_n >> child_cnt;
    for (ll k = 1; k <= child_cnt; k++) {
        ll e, f, l;
        cin >> e >> f >> l;
        int afraid = 0;
        for (ll j = 1; j <= f; j++) {
            ll x;
            cin >> x;
            ll idx = ((x - e) % fence_n + fence_n) % fence_n; // 围栏编号换算成窗口内下标 0..4
            afraid |= 1 << idx;
        }
        int fond = 0;
        for (ll j = 1; j <= l; j++) {
            ll y;
            cin >> y;
            ll idx = ((y - e) % fence_n + fence_n) % fence_n;
            fond |= 1 << idx;
        }
        add_child(e, afraid, fond);
    }
}

void solve() {
    int best = 0;
    // 圆环没有天然起点，枚举第 1 个窗口的 32 种取值，滑 N 格后要求状态回到同一个。
    for (int first = 0; first < STATES; first++) {
        for (int s = 0; s < STATES; s++) {
            cur[s] = NEG;
        }
        cur[first] = gain[1][first];

        // 窗口起点从 2 推到 N，每步右移一格并结算该起点的小朋友。
        for (ll e = 2; e <= fence_n; e++) {
            for (int s = 0; s < STATES; s++) {
                next_dp[s] = NEG;
            }
            for (int s = 0; s < STATES; s++) {
                if (cur[s] == NEG) {
                    continue;
                }
                int base = cur[s];
                int t = s >> 1; // 新进视野的围栏把动物移走
                if (base + gain[e][t] > next_dp[t]) {
                    next_dp[t] = base + gain[e][t];
                }
                t = (s >> 1) | 16; // 新进视野的围栏保留动物，16 = 1 << 4
                if (base + gain[e][t] > next_dp[t]) {
                    next_dp[t] = base + gain[e][t];
                }
            }
            for (int s = 0; s < STATES; s++) {
                cur[s] = next_dp[s];
            }
        }

        // 再做一次不带得分的平移：窗口回到起点 1（起点 N+1 模 N 后为 1），避免重复计分。
        for (int s = 0; s < STATES; s++) {
            next_dp[s] = NEG;
        }
        for (int s = 0; s < STATES; s++) {
            if (cur[s] == NEG) {
                continue;
            }
            int t = s >> 1;
            if (cur[s] > next_dp[t]) {
                next_dp[t] = cur[s];
            }
            t = (s >> 1) | 16;
            if (cur[s] > next_dp[t]) {
                next_dp[t] = cur[s];
            }
        }
        // 只有首尾状态吻合的方案才对应合法的圆环安排。
        if (next_dp[first] > best) {
            best = next_dp[first];
        }
    }
    cout << best << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    build_gain();
    solve();

    return 0;
}
