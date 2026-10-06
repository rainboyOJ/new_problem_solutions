/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 17:02
 * update_at: 2026-10-06 17:02
 */

// roj 3062 「Sticks」 木棒
// 多重集划分 + 回溯搜索（降序、等长跳过、空木棒剪枝、恰好补满剪枝、最后一根免检）
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 70;        // 每组最多 64 节木棍，数组开大一点留余量
const int MAX_PIECE = 50;   // 题面保证每节不超过 50；数据里混进的非法长节直接忽略

ll stick[MAXN];             // 清洗并降序排序后的木棍长度
ll used[MAXN];              // used[i] 标记第 i 节木棍是否已被用掉
ll stick_cnt;               // 清洗后的木棍节数
ll total_len;               // 清洗后所有木棍的总长度
ll target_len;              // 当前正在判定的目标木棒长度 L

// 判定目标长度 target_len 是否可行。
// done 表示已拼好的木棒根数，cur 表示当前这根已拼长度，start 表示本层从哪个下标继续选。
// 返回 true 表示能恰好拼成若干根长度为 target_len 的木棒。
int fit(ll done, ll cur, ll start)
{
    // 已经拼好 S/L - 1 根，剩下的木棍总长恰好是 target_len，最后一根必然成立
    if (done == total_len / target_len - 1) {
        return 1;
    }
    // 当前这根拼满，换下一根，从最长的木棍重新开始选
    if (cur == target_len) {
        return fit(done + 1, 0, 0);
    }

    ll failed = 0; // 本层已经试过并失败的长度；等长木棍互换后局面同构，无需重复试
    for (ll i = start; i < stick_cnt; i++) {
        if (used[i]) {
            continue;
        }
        if (cur + stick[i] > target_len) {
            continue;
        }
        if (stick[i] == failed) { // 等长剪枝：同层失败过的长度直接跳过
            continue;
        }

        used[i] = 1;
        if (fit(done, cur + stick[i], i + 1)) {
            return 1;
        }
        used[i] = 0;

        failed = stick[i]; // 必须在撤销标记之后记录失败长度，成功路径不会污染它

        // 空木棒剪枝：当前木棒还是空的都放不下它，说明这个 L 无解，直接判死
        if (cur == 0) {
            return 0;
        }
        // 恰好补满剪枝：a[i] 恰好补齐当前空缺却失败，同样说明整个 L 无解
        if (cur + stick[i] == target_len) {
            return 0;
        }
    }
    return 0;
}

// 求原始木棒的最小可能长度；清洗后无木棍时返回 0。
ll solve_one()
{
    if (stick_cnt == 0) {
        return 0;
    }
    total_len = 0;
    for (ll i = 0; i < stick_cnt; i++) {
        total_len += stick[i];
    }

    // 按根数 k 从多到少枚举，等价于把长度 L 从小到大枚举，第一个可行解即最小答案
    for (ll groups = total_len / stick[0]; groups >= 1; groups--) {
        if (total_len % groups != 0) {
            continue;
        }
        target_len = total_len / groups;
        for (ll i = 0; i < stick_cnt; i++) {
            used[i] = 0; // 每次判定前清空标记
        }
        if (fit(0, 0, 0)) {
            return target_len;
        }
    }
    return total_len; // 兜底：每节各成一根总是可行
}

// 比较函数：降序，让长木棍先被放置，尽早收紧搜索
int cmp_desc(ll a, ll b)
{
    return a > b;
}

int main()
{
    ll n;
    while (scanf("%lld", &n) == 1 && n != 0) {
        ll raw[MAXN];
        for (ll i = 0; i < n; i++) {
            scanf("%lld", &raw[i]);
        }

        // 输入清洗：丢弃与题面矛盾的长度大于 50 的非法节
        stick_cnt = 0;
        for (ll i = 0; i < n; i++) {
            if (raw[i] <= MAX_PIECE) {
                stick[stick_cnt] = raw[i];
                stick_cnt++;
            }
        }
        sort(stick, stick + stick_cnt, cmp_desc);

        printf("%lld\n", solve_one());
    }
    return 0;
}
