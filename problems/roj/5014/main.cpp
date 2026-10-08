/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 14:12
 * update_at: 2026-10-08 14:27
 */
// 一本通 1678《独木桥》
// 相遇折返 <=> 互相穿过并交换身份：位置的多重集 = {p_i+t : d_i=1} ∪ {p_i-t : d_i=0}
// 折返模型里点与点永不互相穿越，所以按初始位置排序的名次在任何时刻都不变，
// 初始名次为 r 的孩子，t 秒后就位于该多重集的第 r 小值处。
// 每个询问用「两个有序数组的划分」二分求第 r 小，O(log n)，总复杂度 O((n+q)log n)。
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 200005;    // n, q <= 2*10^5
const ll INF = 4000000000000000000LL;  // 划分二分的哨兵：p±t 的绝对值都远小于它

struct Child {
    ll p;   // 初始位置
    int d;  // 初始朝向：1 向右，0 向左
    int id; // 输入顺序里的编号
};

Child child[MAXN];      // child[]：所有孩子按初始位置升序排列
ll right_pos[MAXN];     // 初始向右走的孩子位置，升序
ll left_pos[MAXN];      // 初始向左走的孩子位置，升序
int rank_of[MAXN];      // rank_of[k]：孩子 k 按初始位置升序的名次，从 1 开始
int right_cnt, left_cnt;

// 按初始位置升序排列孩子
bool cmp_by_pos(const Child &a, const Child &b) {
    return a.p < b.p;
}

// 求 {right_pos[i]+t} ∪ {left_pos[j]-t} 合并后的第 rank 小（rank 从 1 开始）
// 枚举「从 right 里取 x 个」，检查 x 是否让两个数组的划分合法，不合法就二分收缩。
ll kth_after_time(ll t, int rank) {
    int lo = max(0, rank - left_cnt);
    int hi = min(rank, right_cnt);
    while (lo <= hi) {
        int x = (lo + hi) / 2;
        int y = rank - x;
        // 划分点两侧的四个边界值，越界处用哨兵保证比较不会误判
        ll r_last = (x > 0) ? right_pos[x - 1] + t : -INF;
        ll r_next = (x < right_cnt) ? right_pos[x] + t : INF;
        ll l_last = (y > 0) ? left_pos[y - 1] - t : -INF;
        ll l_next = (y < left_cnt) ? left_pos[y] - t : INF;
        if (r_last <= l_next && l_last <= r_next) {
            return max(r_last, l_last);   // 合法划分，第 rank 小就是左半部分的最大值
        }
        if (r_last > l_next) {
            hi = x - 1;                   // right 取多了
        } else {
            lo = x + 1;                   // right 取少了
        }
    }
    return 0;
}

void solve() {
    int n;
    if (scanf("%d", &n) != 1) return;

    for (int i = 0; i < n; i++) {
        scanf("%lld", &child[i].p);
        child[i].id = i;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &child[i].d);
    }

    sort(child, child + n, cmp_by_pos);

    for (int i = 0; i < n; i++) {
        rank_of[child[i].id] = i + 1;
        if (child[i].d == 1) {
            right_pos[right_cnt++] = child[i].p;
        } else {
            left_pos[left_cnt++] = child[i].p;
        }
    }

    int q;
    if (scanf("%d", &q) != 1) return;

    while (q--) {
        int k;
        ll t;
        scanf("%d %lld", &k, &t);
        printf("%lld\n", kth_after_time(t, rank_of[k]));
    }
}

int main() {
    solve();
    return 0;
}
