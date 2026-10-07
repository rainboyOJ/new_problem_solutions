/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:36
 * update_at: 2026-10-07 15:54
 */
// 一本通 1689 堆排问题
//
// 算法：状态压缩 + BFS
//  - 点权互不相同，把权值按大小换成序号 0..N-1（最大权值换成 0），
//    大根堆性质就变成「父亲的序号 < 儿子的序号」，与具体数值无关。
//  - N <= 16，每个结点用 4 位存序号，整棵树的排列压成一个 64 位整数状态。
//  - 一种交换方式就是一条边，边权为 1，同一方式可重复使用。
//    以初始排列为起点跑 BFS，第一次生成出合法的堆排列时所在层数就是最少交换次数。
//  - 状态数上界是 N!，开不出数组，visited 只能用 unordered_set（哈希风险见复杂度说明）。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;  // 状态整数：16 个结点各占 4 位，共 64 位，必须用无符号

const int MAXN = 20;
const int MAXM = 130;

ll N;      // 结点个数
ll M;      // 交换方式的种数
ll fa[MAXN];        // fa[i] = 结点 i 的父亲，0 表示它是根
ull rank_of[MAXN];  // rank_of[i] = 结点 i 的权值序号，最大权值为 0
                    // 左侧要左移 4(i-1) 位，用无符号类型才不会在有符号位移上溢出

struct Swap {  // 一种交换方式
    ll u;
    ll v;
};
Swap swp[MAXM]; // swp[1..M] 存所有交换方式，下标从 1 开始和题面一致

// 判断状态 s 是否已经满足大根堆性质：每个结点序号都小于其父亲的序号
bool is_heap(ull s) {
    for (ll i = 1; i <= N; i++) {
        if (fa[i] == 0) continue;             // 根没有父亲，不用比较
        ll ps = 4 * (fa[i] - 1);              // 父亲在状态里的位偏移
        ll cs = 4 * (i - 1);                  // 结点 i 在状态里的位偏移
        if (((s >> ps) & 15ULL) > ((s >> cs) & 15ULL)) return false;
    }
    return true;
}

// 从初始状态 start 出发做 BFS，返回首次出现堆排列时的交换次数（数据保证有解）
// 逐层扩展：cur 是第 depth 层的全部状态，nxt 是下一层。
// 一个状态一旦被生成出来就立刻判堆：BFS 保证它第一次出现的层数就是最少交换次数，
// 所以命中即可返回，不必等它出队，省下整整一层的哈希表容量。
ll bfs(ull start) {
    if (is_heap(start)) return 0;  // 初始排列已经是堆，一次都不用交换
    unordered_set<ull> vis;        // 状态数上界是 N!，开不出数组，只能用哈希表记录访问
    vis.reserve(1 << 20);
    vis.insert(start);
    vector<ull> cur, nxt;
    cur.push_back(start);
    for (ll depth = 1; !cur.empty(); depth++) {
        nxt.clear();
        for (size_t k = 0; k < cur.size(); k++) {
            ull s = cur[k];
            for (ll i = 1; i <= M; i++) {
                ll su = 4 * (swp[i].u - 1), sv = 4 * (swp[i].v - 1);
                ull a = (s >> su) & 15ULL;  // 两个结点的当前序号
                ull b = (s >> sv) & 15ULL;
                // 清掉这两个 4 位再写回去，就完成一次权值交换
                ull t = (s & ~(15ULL << su) & ~(15ULL << sv)) | (b << su) | (a << sv);
                if (!vis.insert(t).second) continue;
                if (is_heap(t)) return depth;
                nxt.push_back(t);
            }
        }
        cur.swap(nxt);
    }
    return -1;  // 题面保证有解，这里只是兜底
}

int main() {
    scanf("%lld %lld", &N, &M);
    for (ll i = 1; i <= N; i++) scanf("%lld", &fa[i]);
    vector<pair<ll, ll> > vw;  // (权值, 结点编号)，用于把权值换成序号
    for (ll i = 1; i <= N; i++) {
        ll w;
        scanf("%lld", &w);
        vw.push_back(make_pair(w, i));
    }
    for (ll i = 1; i <= M; i++) scanf("%lld %lld", &swp[i].u, &swp[i].v);

    sort(vw.begin(), vw.end());  // 权值升序；序号倒过来给，最大权值的序号是 0
    for (ll r = 0; r < N; r++) rank_of[vw[r].second] = N - 1 - r;

    ull start = 0;
    for (ll i = 1; i <= N; i++) start |= rank_of[i] << (4 * (i - 1));

    printf("%lld\n", bfs(start));
    return 0;
}
