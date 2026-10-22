/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-20 13:47
 * update_at: 2026-10-22 22:55
 */
// P4447 [AHOI2018初中组] 分组
//
// 把每个组看成一条「链」：链上的实力值依次加 1，不跳也不重复。
// 于是「分组」等价于「把每个实力值的队员分配到若干条链上」。
//
// 按实力值从小到大处理，因为值 x 的队员只能接到「以 x-1 结尾」的链上，
// 接不上就只能以 x 新开一条长度为 1 的链。决策顺序被值域唯一确定，可以贪心。
//
// 三条规则，按执行顺序编号（前两条用交换论证证明不会让答案变差）：
//   一、实力值不连续时，前一段的链全部冻结，必须当场结算
//   二、有多条链可接时，接最短的 —— 短链最可能成为答案，优先给它增长机会
//   三、链比人多的部分接不上，只能冻结；冻结的应当是其中最长的那些
//
// 规则一必须先于规则二：cur 里的链属于「以 value-1 结尾」，断档时这个前提
// 不成立，它们根本不该参与本轮延长；若挪到后面，cur 已被规则二错误地接上。
// 规则一与规则三冻结链的动作完全一样，都归结为下面的 freeze_all()。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

typedef priority_queue<int, vector<int>, greater<int> > MinHeap;

int n;
int a[MAXN];

// 冻结堆里所有链：长度已定格，拿去更新答案后清空。
// 规则一（断档时冻掉整段）和规则三（冻掉接不上的最长链）都调用它。
void freeze_all(MinHeap &heap, int &answer) {
    while (!heap.empty()) {
        answer = min(answer, heap.top());
        heap.pop();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);

    // 排序后扫描一遍，把相等的实力值压成一块：
    //   blocks[k].first  = 这个实力值
    //   blocks[k].second = 拥有这个实力值的人数
    // 这样后面按值块处理时，块的先后顺序就是实力值从小到大的顺序。
    vector<pair<int, int> > blocks;
    for (int i = 1; i <= n; ) {
        int j = i;
        while (j <= n && a[j] == a[i]) j++;
        blocks.push_back(make_pair(a[i], j - i));
        i = j;
    }

    // cur：以「当前值块的实力值」结尾的各条链长度，小根堆让最短的链先被取出。
    // nxt：以「下一个值块的实力值」结尾的链。两者轮换，nxt 每次用完即空。
    MinHeap cur, nxt;

    int answer = n;  // 链长的最小值即答案，先取最坏上界
    // 上一块处理过的实力值。a_i 最小到 -1e9，用 long long 避免 value-1 溢出。
    long long last_value = LLONG_MIN;

    for (auto [value, count] : blocks) {
        // ── 规则一（断档冻结）────────────────────────────────
        // 与上一块不连续，cur 里的链无法再从 value-1 延续，整段冻结。
        // 这一步必须先于规则二：否则这些链会被错误地接到 value 上。
        // last_value 记录上一块的实力值，初值取一个不可能相邻的数。
        if (value != last_value + 1) {
            freeze_all(cur, answer);
        }
        last_value = value;

        // ── 规则二（延长最短链）──────────────────────────────
        // 能接的链里优先接最短的，所以从堆顶取。最多接 min(count, cur.size()) 条。
        int extend = min(count, (int)cur.size());
        for (int k = 0; k < extend; k++) {
            nxt.push(cur.top() + 1);
            cur.pop();
        }

        // ── 规则三（冻结最长链）──────────────────────────────
        // 链比人多的那些接不上，只能停在上一块的值。刚才取走的是最短的若干条，
        // cur 里剩下的正是最长的那些，全部冻结即「冻最长、保最短」。
        freeze_all(cur, answer);

        // 接不上旧链的队员，只能以当前值新开一条长度为 1 的链
        for (int k = 0; k < count - extend; k++) {
            nxt.push(1);
        }

        swap(cur, nxt);  // nxt 在 swap 后为空，下一轮直接复用
    }

    // 收尾：最后一个值块留下的链全部冻结
    freeze_all(cur, answer);

    cout << answer << '\n';
    return 0;
}
