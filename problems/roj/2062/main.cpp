/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:29
 * update_at: 2026-10-06 10:32
 */
// usaco 4.1.2 栅栏的木料：二分答案 + 大件优先 DFS 装箱判定 + 废料上限剪枝。
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 60;     // 木板数 <= 50
const int MAXR = 1030;   // 需求数 <= 1023

ll n, r;                 // 木板数、需求数
ll board[MAXN];          // board[i] = 第 i 块木板的剩余长度（会被切分修改）
ll req[MAXR];            // req[i] = 第 i 短的需求长度（升序）
ll pref[MAXR];           // pref[i] = 前 i 短需求的长度和（pref[0] = 0）
ll total_board;          // 所有木板总长度
ll min_req;              // 最短需求长度，废料的判定阈值
ll max_waste;            // 本次判定允许的最大废料 = total_board - 前 mid 需求和
ll waste;                // 当前累计的不可回收废料

// 判定的核心 DFS：这一层在为第 idx 短（剩余中最大的）需求选木板。
// start_board：相同长度的需求只能放在编号不小于它的需求的木板里（对称性剪枝）。
bool dfs(ll idx, ll start_board) {
    if (idx < 0) return true; // 前 mid 个需求全部放好

    ll cur = req[idx];
    for (ll i = start_board; i < n; i++) {
        if (board[i] < cur) continue;

        // 切下需求，统计这块木板是否当场变成废料（剩余 < 最短需求）
        board[i] -= cur;
        ll add = 0;
        if (board[i] < min_req) add = board[i];
        waste += add;

        bool ok = false;
        if (waste <= max_waste) {
            // 相同长度的相邻需求，下一块木板下标不能小于 i，避免同构搜索；
            // 长度不同则下一层从 0 号木板重新找起
            ll nxt = 0;
            if (idx > 0 && req[idx - 1] == cur) nxt = i;
            ok = dfs(idx - 1, nxt);
        }

        // 无论成功与否都要恢复现场：check() 成功返回后木板数组还要给下一次二分用
        waste -= add;
        board[i] += cur;

        if (ok) return true;

        // 这根木板刚好被用完：放不下当前需求的更长的木板只会更差，剪枝
        if (board[i] == cur) break;
    }
    return false;
}

// 判定能否用木板切出最小的 mid 根需求木料
bool check(ll mid) {
    if (mid == 0) return true;
    if (pref[mid] > total_board) return false; // 需求总长超过木板总长，必不可能

    max_waste = total_board - pref[mid]; // 允许的废料上限
    waste = 0;
    return dfs(mid - 1, 0);
}

int main() {
    scanf("%lld", &n);
    total_board = 0;
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &board[i]);
        total_board += board[i];
    }
    scanf("%lld", &r);
    for (ll i = 0; i < r; i++) scanf("%lld", &req[i]);

    // 需求升序：能切 k 根时最优选最小的 k 根；数量具有单调性，可二分
    sort(req, req + r);
    sort(board, board + n);
    pref[0] = 0;
    for (ll i = 0; i < r; i++) pref[i + 1] = pref[i] + req[i];
    min_req = req[0];

    ll low = 0, high = r, ans = 0;
    while (low <= high) {
        ll mid = (low + high) / 2;
        if (check(mid)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
