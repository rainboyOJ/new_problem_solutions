/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 02:58
 * update_at: 2026-10-08 02:58
 */

#include <cstdio>

typedef long long ll;

const int MAXM = 10005;  // 学生数上限 10000，留一点余量
const int MAXN = 205;    // 班级数上限 200，留一点余量
const ll INF = 4000000000000000000LL; // 无穷大哨兵：答案上界约 1e17，4e18 既远离溢出又足够大

ll X[MAXM];   // 第 i 个学生的敏感指数 X[i]
ll G[MAXN];   // 第 j 个教室的舒适程度 G[j]
ll pre[MAXM]; // pre[i] = Σ_{t<=i} (X[t]-Average)^2，即偏离平方的前缀和

ll prv[MAXM]; // f[j-1][i]：前 i 个学生恰好分成 j-1 个班的最小评价指数
ll cur[MAXM]; // f[j][i]  ：前 i 个学生恰好分成 j 个班的最小评价指数

// 单调队列：存候选断点 k 及其价值 val[k] = prv[k] - G[j]*pre[k]，
// val 沿队列严格递增，故队首即窗口内最小价值。
struct Node {
    int k;    // 断点下标
    ll val;   // prv[k] - gj*pre[k]
};
Node q[MAXM];

// 由 prv[] 推出 cur[]：固定班数 j 时，转移式
//     f[j][i] = G[j]*pre[i] + min_{i-B <= k <= i-A} { prv[k] - G[j]*pre[k] }
// 中的取值只依赖 k，窗口随 i 滑动，用单调队列均摊 O(1) 求最小值。
// 返回 f[j][M]（不可达时返回 INF）；out_last_k 返回 f[j][M] 取到最小值时最大的断点 k。
ll layer(int j, ll gj, int M, int A, int B, int &out_last_k) {
    int head = 0, tail = -1;                 // 空队列
    int lo = j * A;                          // j 个班每班至少 A 人
    int hi = j * B < M ? j * B : M;           // j 个班每班至多 B 人，故 i <= j*B
    out_last_k = -1;
    for (int i = 0; i <= M; ++i) cur[i] = INF;
    for (int i = lo; i <= hi; ++i) {
        int k = i - A;                       // 本步新滑入窗口的断点
        if (prv[k] < INF) {
            ll val = prv[k] - gj * pre[k];
            // 相等也弹掉队尾：平手时保留更大的 k，好让最后一个班更小
            while (head <= tail && val <= q[tail].val) --tail;
            ++tail;
            q[tail].k = k;
            q[tail].val = val;
        }
        while (head <= tail && q[head].k < i - B) ++head; // 滑出窗口
        if (head > tail) continue;                        // 该 i 不可达
        int kb = q[head].k;
        cur[i] = prv[kb] + gj * (pre[i] - pre[kb]);
        if (i == M) out_last_k = kb;
    }
    return cur[M];
}

int main() {
    int ncase;
    if (scanf("%d", &ncase) != 1) return 0;
    while (ncase--) {
        int M, N, A, B;
        if (scanf("%d %d %d %d", &M, &N, &A, &B) != 4) break;

        ll sum = 0;
        for (int i = 1; i <= M; ++i) {
            scanf("%lld", &X[i]);
            sum += X[i];
        }
        for (int j = 1; j <= N; ++j) scanf("%lld", &G[j]);

        ll avg = sum / M; // 先全部加起来再整除，取下整
        pre[0] = 0;
        for (int i = 1; i <= M; ++i) {
            ll d = X[i] - avg;
            pre[i] = pre[i - 1] + d * d;
        }

        // 边界：0 个学生分成 0 个班，评价指数为 0
        for (int i = 0; i <= M; ++i) prv[i] = INF;
        prv[0] = 0;

        ll best = INF;
        int best_class = 0, best_last = 0;
        int limit = N < M / A ? N : M / A; // 每个班至少 A 人，班数不可能超过 M/A
        for (int j = 1; j <= limit; ++j) {
            int last_k = -1;
            ll value = layer(j, G[j], M, A, B, last_k);
            for (int i = 0; i <= M; ++i) prv[i] = cur[i]; // 滚动数组：本层结果留给下一层
            // 严格小于：先保评价指数最小，同价时保留更小的班数
            if (last_k >= 0 && value < best) {
                best = value;
                best_class = j;
                best_last = M - last_k; // 最后一个班的人数已被单调队列压到最小
            }
        }

        printf("%lld %d %d\n", best, best_class, best_last);
    }
    return 0;
}
