/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 09:00
 * update_at: 2026-10-09 12:20
 */
// roj 3066《送礼物》：N 个礼物，一次搬重量和不超过 W 的任意多件，求最大搬运重量。
// 容量 W 可达 2^31-1，容量维 DP 不可行；N 可达 48，朴素 2^N 也不可行。
// 故用折半搜索（meet in the middle）：前半枚举出全部合法子集和并排序，
// 后半枚举时在表里二分找「不超过 W - S」的最大值。
// 题面三步判据（关键词 / 括号内算法名 / 标题）全空 ⇒ 未指定实现手段。
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

typedef long long ll;

const int MAXN = 50;            // 题面 N ≤ 46，实测最大 48，留余量
const int MAX_HALF = 1 << 24;   // 前半最多 24 件，子集和最多 2^24 个

ll W;                           // 力气上限（可到 2^31-1，必须 ll）
int n;                          // 过滤超重礼物后剩下的礼物数
ll gift[MAXN];                  // 过滤后的礼物重量，按降序排列

// 前半枚举出的所有合法子集和。
// 每个状态都由「和不超过 W」的递归产生，故取值 ≤ W ≤ 2^31-1，收窄成 int 不会溢出；
// 用 int 而不是 ll，是为了让最坏情况的 2^24 个状态只占 64MB（ll 要 128MB+，会超过 128MB 限额）。
int half_sum[MAX_HALF + 10];
int half_cnt;

ll answer;                      // 当前能达到的最大搬运重量

// 枚举 gift[idx..half_end-1] 每件选或不选，叶子处把当前和收进 half_sum
void dfs_first(int idx, int half_end, ll current_sum) {
    if (idx == half_end) {
        half_sum[half_cnt++] = current_sum;
        return;
    }
    dfs_first(idx + 1, half_end, current_sum);              // 不拿第 idx 件
    if (current_sum + gift[idx] <= W) {                     // 拿第 idx 件
        dfs_first(idx + 1, half_end, current_sum + gift[idx]);
    }
}

// 枚举 gift[idx..end_idx-1] 的每种取法，用当前和 S 去表里配一个最大的另一半
void dfs_second(int idx, int end_idx, ll current_sum) {
    if (idx == end_idx) {
        ll remain = W - current_sum;                        // 还能再塞多少
        int lo = 0, hi = half_cnt - 1, pos = 0;
        while (lo <= hi) {                                  // 找最后一个 ≤ remain 的下标
            int mid = lo + (hi - lo) / 2;
            if (half_sum[mid] <= remain) {
                pos = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        ll total = current_sum + half_sum[pos];
        if (total > answer) {
            answer = total;
        }
        return;
    }
    dfs_second(idx + 1, end_idx, current_sum);              // 不拿第 idx 件
    if (current_sum + gift[idx] <= W) {                     // 拿第 idx 件
        dfs_second(idx + 1, end_idx, current_sum + gift[idx]);
    }
}

// 读入并按题意过滤：单个重量就超过 W 的礼物永远搬不动，直接剔除。
// 返回 false 表示连 W / N 都没读到（无输入），此时不输出任何内容。
bool read_input() {
    int total;
    if (!(cin >> W >> total)) {
        return false;
    }
    n = 0;
    for (int i = 0; i < total; i++) {
        ll value;
        if (!(cin >> value)) {          // 礼物少于声明的 N 件：按已读到的件数处理
            break;
        }
        if (value <= W) {
            gift[n++] = value;
        }
    }
    return true;
}

void solve() {
    if (!read_input()) {                // 无输入：静默退出
        return;
    }
    if (n == 0) {                       // 全部超重（或 N = 0）：一件都搬不动
        cout << 0 << "\n";
        return;
    }
    sort(gift, gift + n, greater<ll>());    // 降序：先搜大件，更快触发「超过 W」的剪枝

    int half = n / 2;
    dfs_first(0, half, 0);

    sort(half_sum, half_sum + half_cnt);    // 排序后二分，顺带去重压缩表长
    int unique_cnt = 1;
    for (int i = 1; i < half_cnt; i++) {
        if (half_sum[i] != half_sum[i - 1]) {
            half_sum[unique_cnt++] = half_sum[i];
        }
    }
    half_cnt = unique_cnt;

    dfs_second(half, n, 0);
    cout << answer << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
