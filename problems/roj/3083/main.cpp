/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 17:44
 * update_at: 2026-10-06 17:44
 */

// 逐日推进的可达性 DP：
// 状态 = (云的左上角位置, 最近 6 天雨迹)。
// 雨迹不用 16 个"连续几天没下雨"计数器，而是存 6 个 16 位掩码 W[0..5]，
// W[k] 表示"最近 k+1 天下过雨的区域并集"，判罚只需读 W[5]：
// 最近 6 天没被淋到的区域，今天必须全部被淋到，等价于所有长度为 7 的窗口都合法。
// 每天枚举 13 种位移生成后继，用排序去重合并等价状态，集合空了就无解。

#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

// 把 (云位置, W[0..5]) 打包成两个 64 位字作键：
// a 低 4 位是云位置，第 4..35 位放 W[0]、W[1]；b 依次放 W[2]、W[3]、W[4]、W[5]
// 六项都要存：W[5] 是最近 6 天的并集，不能由前 5 项推出
// （W[0]|...|W[4] 只是最近 5 天的并集，少一天）
typedef pair<ull, ull> Key;

Key pack_key(int code, int W0, int W1, int W2, int W3, int W4, int W5) {
    ull a = (ull)code | ((ull)W0 << 4) | ((ull)W1 << 20);
    ull b = (ull)W2 | ((ull)W3 << 16) | ((ull)W4 << 32) | ((ull)W5 << 48);
    return Key(a, b);
}


const int SIDE = 4;               // 村子是 4 x 4 的网格
const int SPOTS = 3;              // 云是 2 x 2，左上角只能落在 3 x 3 个位置
const int CENTER = 4;             // 云在正中 (1,1) 时盖住 6,7,10,11，第一天固定在这里
const int STREAK = 6;             // 同一块地连续 6 天不下雨还合法，第 7 天必须下
const int NDAY = 370;             // N <= 365，数组多开一点

int n;                            // 本组用例的天数
int plan[NDAY];                   // plan[d]：第 d 天赶集过节区域的 16 位掩码（1 表示不能淋雨）

int cover_mask[SPOTS * SPOTS];    // cover_mask[code]：云在 code 位置淋到的区域掩码，code = 行*3+列
vector<int> nxt[SPOTS * SPOTS];   // nxt[code]：从 code 出发一天内能到的所有云位置（含原地不动）
bool vis[SPOTS * SPOTS];          // 预处理 nxt 时的临时标记

// 当前层和下一层的状态集合。逐层滚动，不保存历史层。
vector<Key> cur_list, next_list;

// 云左上角在 (r,c)（行列从 0 开始）时覆盖的区域掩码，16 位按行优先
int mask_at(int r, int c) {
    return (1 << (r * SIDE + c)) | (1 << (r * SIDE + c + 1))
         | (1 << ((r + 1) * SIDE + c)) | (1 << ((r + 1) * SIDE + c + 1));
}

// 预处理 9 个覆盖掩码和每个位置一天内的 13 种位移
void prepare() {
    for (int r = 0; r < SPOTS; r++)
        for (int c = 0; c < SPOTS; c++)
            cover_mask[r * SPOTS + c] = mask_at(r, c);
    // 位移：东南西北各 1 或 2 格，或原地不动，不允许对角线
    for (int code = 0; code < SPOTS * SPOTS; code++) {
        memset(vis, 0, sizeof(vis));
        int r = code / SPOTS, c = code % SPOTS;
        for (int dr = -2; dr <= 2; dr++)
            for (int dc = -2; dc <= 2; dc++) {
                if (dr != 0 && dc != 0) continue;      // 不允许对角线
                if (dr * dr + dc * dc > 4) continue;   // 距离超过 2 格
                int nr = r + dr, nc = c + dc;
                if (nr < 0 || nr >= SPOTS || nc < 0 || nc >= SPOTS) continue;
                int ncode = nr * SPOTS + nc;
                if (!vis[ncode]) {
                    vis[ncode] = true;
                    nxt[code].push_back(ncode);
                }
            }
    }
}

// 检查今天 (第 d 天，0 起) 的转移是否合法；enforce 为真时 7 天窗口已满
bool check_day(int cover, ull U, bool enforce, int planmask) {
    // 约束 1：当天不能淋到赶集过节区
    if (cover & planmask) return false;
    // 约束 2：最近 6 天没淋到的区域（~U），今天必须全部淋到
    if (enforce) {
        int dry = (~U) & 0xFFFF;          // 旱满 6 天的区域
        if (dry & (~cover & 0xFFFF)) return false; // 今天淋不到就违规
    }
    return true;
}

void solve() {
    for (int d = 0; d < n; d++) {
        int m = 0;
        for (int i = 0; i < SIDE * SIDE; i++) {
            int x;
            scanf("%d", &x);
            if (x) m |= 1 << i;
        }
        plan[d] = m;
    }

    // 第一天云固定盖住 6,7,10,11 且不允许移动，所以初态唯一；
    // 雨迹 6 项都填第一天的覆盖，从第 2 天起 U 永远是"最近 6 天雨迹"
    int c0 = cover_mask[CENTER];
    cur_list.clear();
    // 第一天也不允许淋到赶集过节区，违规则直接无解
    if (!(c0 & plan[0]))
        cur_list.push_back(pack_key(CENTER, c0, c0, c0, c0, c0, c0));

    for (int d = 1; d < n; d++) {
        bool enforce = (d >= STREAK);   // 第 7 天（d=6）起窗口才满 7 天
        next_list.clear();
        // 由当天集合里的每个状态，枚举 13 种位移生成后继
        for (int i = 0; i < (int)cur_list.size(); i++) {
            Key key = cur_list[i];
            int code = (int)(key.first & 15);
            // 从键里拆出 W[0..5]，U = 六项的并 = 最近 6 天雨迹
            int W[6];
            W[0] = (int)((key.first >> 4) & 0xFFFF);
            W[1] = (int)((key.first >> 20) & 0xFFFF);
            W[2] = (int)(key.second & 0xFFFF);
            W[3] = (int)((key.second >> 16) & 0xFFFF);
            W[4] = (int)((key.second >> 32) & 0xFFFF);
            W[5] = (int)((key.second >> 48) & 0xFFFF);
            int U = W[0] | W[1] | W[2] | W[3] | W[4] | W[5];
            for (int j = 0; j < (int)nxt[code].size(); j++) {
                int ncode = nxt[code][j];
                int cover = cover_mask[ncode];
                if (!check_day(cover, U, enforce, plan[d])) continue;
                // W'[k] = cover | W[k-1]，W'[0] = cover
                next_list.push_back(pack_key(ncode, cover, cover | W[0],
                                             cover | W[1], cover | W[2],
                                             cover | W[3], cover | W[4]));
            }
        }
        // 排序去重，合并等价状态
        sort(next_list.begin(), next_list.end());
        next_list.erase(unique(next_list.begin(), next_list.end()), next_list.end());
        cur_list.swap(next_list);
        if (cur_list.empty()) break;   // 集合空了，后面再也不可能有合法方案
    }

    printf("%d\n", cur_list.empty() ? 0 : 1);
}

int main() {
    prepare();
    while (scanf("%d", &n) == 1 && n != 0) solve();
    return 0;
}
