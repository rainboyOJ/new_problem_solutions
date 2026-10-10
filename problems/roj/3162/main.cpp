/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <cstdio>
using namespace std;

typedef long long ll;

const int MAXN = 22;

// way[k][rank][high]：k 块待排的板里，本块排第 rank 小、它是 high 位（1 高位 / 0 低位）时，
// 后面还有多少种排法。板长互不相同，「谁挨着谁」只由相对大小决定，所以剩下 k 块板的长度
// 可以重新编号成 1..k，rank 就是本块的编号——这是唯一需要的状态。
ll way[MAXN + 1][MAXN + 2][2];

ll n, c;
ll avail[MAXN + 2]; // 还没用上的板，长度升序存放；下标 i 就是第 i+1 小
int cnt;            // avail 里的板数
ll ans[MAXN + 2];
ll solved_cnt; // 本次询问实际填入的板数（无解时为 0，与 main.py 的空列表对齐）

void build_way() {
    way[1][1][0] = way[1][1][1] = 1; // 只剩本块，后面没有板，跳不跳都合法
    for (int k = 2; k <= MAXN; k++) {
        for (int rank = 1; rank <= k; rank++) {
            ll sum_high = 0, sum_low = 0;
            for (int r = 1; r < rank; r++) sum_high += way[k - 1][r][0]; // 高位块下一块必须更矮
            for (int r = rank + 1; r <= k; r++) sum_low += way[k - 1][r - 1][1]; // 低位块下一块必须更高
            way[k][rank][1] = sum_high;
            way[k][rank][0] = sum_low;
        }
    }
}

// 字典序第 c 个围栏：从左往右逐位试填，用「这一位取它时后面还有多少排法」整块跳过
void kth_fence() {
    cnt = n;
    for (ll i = 1; i <= n; i++) avail[i - 1] = i;
    ll high = -1;      // -1 表示本块是第一块，没有前一块来限制它
    ll lo = 0, hi = n - 1; // 本块的候选板在 avail 中的下标闭区间，由前一块的高低决定
    for (ll step = 0; step < n; step++) {
        ll k = cnt;
        for (ll idx = lo; idx <= hi; idx++) {
            // 试填顺序即字典序：候选板按长度升序，同一块板先数「它是高位」的方案（下一块更矮，更小）
            ll roles[2];
            int role_cnt;
            if (high < 0) {
                roles[0] = 1;
                roles[1] = 0;
                role_cnt = 2;
            } else {
                roles[0] = 1 - high; // 高低交错：角色与上一块相反
                role_cnt = 1;
            }
            int picked = 0;
            for (int t = 0; t < role_cnt; t++) {
                ll role = roles[t];
                ll ways = way[k][idx + 1][role];
                if (c > ways) {
                    c -= ways;
                    continue;
                }
                ans[solved_cnt] = avail[idx];
                solved_cnt += 1; // ★ 与 main.py 的 ans.append 对齐：计数 = 实际填入次数，不是 step+1
                                 //   （否则中途有空轮时 ans[] 留洞，输出残留 0）
                for (ll i = idx; i + 1 < cnt; i++) avail[i] = avail[i + 1]; // 删掉这块板
                cnt--;
                high = role;
                if (role == 1) {
                    lo = 0;
                    hi = idx - 1; // 高位块只配更矮的板
                } else {
                    lo = idx;
                    hi = k - 2; // 低位块只配更高的板（删掉后下标整体左移 1）
                }
                picked = 1;
                break;
            }
            if (picked) break;
        }
    }
}

int main() {
    build_way();
    ll cases;
    scanf("%lld", &cases);
    for (ll t = 0; t < cases; t++) {
        scanf("%lld%lld", &n, &c);
        solved_cnt = 0;
        kth_fence();
        // 与 main.py 对齐：无解（c 超过总方案数）时 ans 为空 ⇒ 输出空行
        for (ll i = 0; i < solved_cnt; i++) {
            if (i) printf(" ");
            printf("%lld", ans[i]);
        }
        printf("\n");
    }
    return 0;
}
