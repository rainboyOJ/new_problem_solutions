/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:30
 * update_at: 2026-10-10 13:30
 */

// 疫情控制：二分答案 + 贪心 + 树状数组。
// 判定 limit 小时内能否让每条「首都→边境」路径上都有检查点：
// 走不到首都的军队就近跳到最高可达祖先；能到首都的军队当预备队，
// 优先补自己子树的需求（免费），不够再花时间折返。
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXN = 50005;
const int MAXLOG = 18; // 2^17 > 50000

struct Ed { // 邻接表里的一条边
    int to;
    ll w;
};

int n, m, lg;
vector<vector<Ed> > adj;      // 按输入顺序建邻接表
vector<int> children[MAXN];   // 先根序下的孩子表
int parent[MAXN];
ll depth[MAXN];  // 各城市到首都的距离
ll pw[MAXN];     // 到父边的权值
int order[MAXN]; // 栈式 DFS 的先根序
int up[MAXLOG][MAXN]; // 倍增表
int origin[MAXN];     // 军队属于哪个根儿子的子树，-1 表示没有
int armies[MAXN];
ll dSorted[MAXN]; // 能到首都的判定：按到根距离排序的军队深度
int tops[MAXN], topCnt;    // 根的儿子，按边权从大到小
int tid[MAXN];             // 根儿子 -> tops 下标
int cp[MAXN], cov[MAXN], unc[MAXN];
int bitT[MAXN];            // 树状数组（容量 f）
int bitLen;
int gused[MAXN];           // 本轮军队是否已用
int curs[MAXN];            // 每个根儿子的「可动上界」缓存
int markArr[MAXN];
int needsArr[MAXN];
vector<vector<int> > groups; // 每个根儿子的军队（按深度升序）
vector<vector<ll> > gd;

int findUpperLL(const ll *arr, int len, ll v) { // 第一个 > v 的下标（等于 bisect_right）
    int lo = 0, hi = len;
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (arr[mid] <= v) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

int findUpperVec(const vector<ll> &arr, ll v) { // 同上，作用于升序 vector
    int lo = 0, hi = arr.size();
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (arr[mid] <= v) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

void bitAdd(int i, int delta) { // 0-based 单点增减
    i += 1;
    while (i <= bitLen) {
        bitT[i] += delta;
        i += i & -i;
    }
}

int bitSum(int i) { // 前缀和：下标 [0, i]，i 为 -1 时得 0
    int s = 0;
    i += 1;
    while (i > 0) {
        s += bitT[i];
        i -= i & -i;
    }
    return s;
}

int bitKth(int q) { // 树上倍增找第 q 个 1 的 0-based 下标
    int idx = 0, bit = 1;
    while (bit * 2 <= bitLen + 1) bit *= 2;
    while (bit) {
        int nxt = idx + bit;
        if (nxt <= bitLen && bitT[nxt] < q) {
            q -= bitT[nxt];
            idx = nxt;
        }
        bit >>= 1;
    }
    return idx;
}

bool cmpDepth(int x, int y) { return depth[x] < depth[y]; }
bool cmpPwDesc(int x, int y) { return pw[x] > pw[y]; }

bool feasible(ll limit) {
    int f = findUpperLL(dSorted, m, limit); // 能走到首都的军队数
    int markCnt = 0;
    for (int idx = f; idx < m; ++idx) { // 走不到首都的：原地走到最高可达祖先
        int s = armies[idx];
        ll th = depth[s] - limit; // 祖先距离下限，恒大于 0，跳不进根
        int x = s;
        for (int k = lg - 1; k >= 0; --k) {
            int y = up[k][x];
            if (depth[y] >= th) x = y;
        }
        cp[x] = 1;
        markArr[markCnt] = x;
        ++markCnt;
    }

    cov[0] = cp[0];
    for (int i = 1; i < n; ++i) { // 检查点沿先根序向下渗透
        int x = order[i];
        cov[x] = cp[x] ? 1 : cov[parent[x]];
    }
    for (int i = n - 1; i >= 0; --i) { // 自底向上找「还有裸叶子」的子树
        int x = order[i];
        if (cov[x]) unc[x] = 0;
        else if (!children[x].empty()) {
            unc[x] = 0;
            for (int j = 0; j < (int)children[x].size(); ++j) {
                if (unc[children[x][j]]) { unc[x] = 1; break; }
            }
        } else unc[x] = 1; // 叶子且从根到此无检查点
    }
    int needCnt = 0;
    for (int i = 0; i < topCnt; ++i) {
        int c = tops[i];
        if (unc[c]) {
            needsArr[needCnt] = c;
            ++needCnt;
            if (needCnt > f) break; // 需求比预备队还多，直接判负
        }
    }

    bool ok = needCnt <= f;
    if (ok) {
        bitLen = f;
        bitT[0] = 0;
        for (int i = 1; i <= f; ++i) bitT[i] = i & -i; // 建容量 f 的全 1 树状数组
        for (int i = 0; i < m; ++i) gused[i] = 0;
        for (int i = 0; i < topCnt; ++i) curs[i] = -2;
        for (int i = 0; i < needCnt; ++i) {
            int c = needsArr[i];
            int gtid = tid[c];
            if (!groups[gtid].empty()) { // 优先用「自己子树」的军队免费落在 c
                int cur = curs[gtid];
                if (cur == -2) { // 该组还没算过可动上界
                    cur = findUpperVec(gd[gtid], limit) - 1;
                    curs[gtid] = cur;
                }
                while (cur >= 0 && gused[groups[gtid][cur]]) cur -= 1;
                curs[gtid] = cur;
                if (cur >= 0) {
                    int idx = groups[gtid][cur];
                    gused[idx] = 1;
                    bitAdd(idx, -1);
                    continue;
                }
            }
            // 否则从首都折返下到 c：挑剩余时间够的最弱一支
            int pos = findUpperLL(dSorted, m, limit - pw[c]) - 1;
            int q = bitSum(pos);
            if (q == 0) { ok = false; break; }
            int idx = bitKth(q);
            gused[idx] = 1;
            bitAdd(idx, -1);
        }
    }

    for (int i = 0; i < markCnt; ++i) cp[markArr[i]] = 0; // 清掉本轮检查点，供下次复用
    return ok;
}

int main() {
    if (scanf("%d", &n) != 1) return 0; // 空输入安全返回
    adj.assign(n, vector<Ed>());
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        u -= 1;
        v -= 1;
        Ed e;
        e.to = v; e.w = w;
        adj[u].push_back(e);
        e.to = u;
        adj[v].push_back(e);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d", &armies[i]);
        armies[i] -= 1;
    }

    // 从根出发的迭代 DFS：一次拿到父指针、到根距离、子表和先根序
    for (int i = 0; i < n; ++i) parent[i] = -1;
    parent[0] = 0; // 根的父亲记成自己，回头时不会被当成孩子
    vector<int> stk;
    stk.push_back(0);
    int ordCnt = 0;
    while (!stk.empty()) {
        int x = stk.back();
        stk.pop_back();
        order[ordCnt++] = x;
        for (int j = 0; j < (int)adj[x].size(); ++j) {
            int y = adj[x][j].to;
            ll w = adj[x][j].w;
            if (y == parent[x]) continue;
            parent[y] = x;
            depth[y] = depth[x] + w;
            pw[y] = w;
            children[x].push_back(y);
            stk.push_back(y);
        }
    }

    // 倍增表：判定时让到不了根的军队跳到 limit 内最高的祖先
    lg = 0;
    while ((1 << lg) <= n - 1) ++lg; // lg = (n-1).bit_length()
    if (lg > MAXLOG) lg = MAXLOG;
    for (int x = 0; x < n; ++x) up[0][x] = parent[x];
    for (int k = 1; k < lg; ++k) {
        for (int x = 0; x < n; ++x) up[k][x] = up[k - 1][up[k - 1][x]];
    }

    // 每支军队属于哪个根儿子的子树（根的儿子上不算）
    for (int i = 0; i < n; ++i) origin[i] = -1;
    for (int i = 1; i < n; ++i) {
        int x = order[i];
        origin[x] = (parent[x] == 0) ? x : origin[parent[x]];
    }

    sort(armies, armies + m, cmpDepth); // 按到根距离升序
    for (int i = 0; i < m; ++i) dSorted[i] = depth[armies[i]];

    topCnt = 0;
    for (int i = 0; i < (int)children[0].size(); ++i) tops[topCnt++] = children[0][i];
    stable_sort(tops, tops + topCnt, cmpPwDesc); // 需求按边权从大到小
    for (int i = 0; i < topCnt; ++i) tid[tops[i]] = i;
    groups.assign(topCnt, vector<int>());
    gd.assign(topCnt, vector<ll>());
    for (int idx = 0; idx < m; ++idx) {
        int c = origin[armies[idx]];
        if (c != -1) groups[tid[c]].push_back(idx);
    }
    for (int i = 0; i < topCnt; ++i) {
        for (int j = 0; j < (int)groups[i].size(); ++j) gd[i].push_back(depth[armies[groups[i][j]]]);
    }
    for (int i = 0; i < n; ++i) { cp[i] = 0; cov[i] = 0; unc[i] = 0; }

    // 每支军队最多盖住一个根儿子子树，m 支盖不齐 k 个子树时无解
    if (topCnt > m) {
        printf("-1\n");
        return 0;
    }
    ll high = 0;
    ll mxPw = 0;
    for (int i = 0; i < n; ++i) if (depth[i] > high) high = depth[i];
    for (int i = 0; i < topCnt; ++i) if (pw[tops[i]] > mxPw) mxPw = pw[tops[i]];
    high += mxPw; // 此时全员预备队、剩余时间都够

    ll lo = 0, hi = high; // 可行性随时间单调，二分最小可行时间
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (feasible(mid)) hi = mid;
        else lo = mid + 1;
    }
    printf("%lld\n", lo);
    return 0;
}
