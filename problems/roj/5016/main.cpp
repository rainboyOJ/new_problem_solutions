/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 20:12
 * update_at: 2026-10-08 20:12
 */
// 一本通 1680《序列》/ roj 5016：分块 + 前缀和 + 二分
//
// 题面：序列从 1,2,2 开始；读到第 i 个数 v_i 就往后写 v_i 个 i（题面例子：
//   第 3 个数是 2 ⇒ 写 2 个 3；第 4 个数是 3 ⇒ 写 3 个 4），得到
//   1,2,2,3,3,4,4,4,5,5,5,6,6,6,6,...。这就是 Golomb 自描述序列。
//   last(x) = x 最后一次出现的位置 = a[1]+...+a[x]（a[v] 为 v 出现的次数）。
//   求 last(last(N)) mod (1e9+7)。
//
// 关键恒等式：last(last(N)) = Σ_{v=1..N} v * a[v]。
//   于是把出现的值相同的项看作一块：第 k 块（值恒为 k）覆盖位置区间
//   (last(k-1), last(k)]，共 a[k] 个位置。答案就是
//   Σ_{k} k * (第 k 块覆盖的位置编号之和) —— 即「位置 × 该位置上的值」的总和。
//
// 复杂度：N <= 1e9 时块号只到 438744，预处理 O(K)（K≈4.4e5）；
//   单次询问在 last(k) 数组上二分定位块号，O(log K)。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1000000007LL;
const ll INV2 = 500000004LL;   // 2 在模 1e9+7 下的逆元
const ll LIMIT = 1000000000LL; // 题面 N 的上限
const int MAXK = 500005;       // K ≈ 4.4e5（last(K) 首次 >= 1e9），留足余量

struct Block {
    ll appear_cnt; // a[k]：数字 k 在序列中出现的次数，也是第 k 块的元素个数
    ll end_pos;    // last(k) = a[1]+...+a[k]，第 k 块的右端点
};

Block block[MAXK]; // block[0].end_pos = 0；第 k 块覆盖 (end_pos[k-1], end_pos[k]]
ll pref[MAXK];     // pref[k] = 前 k 块对答案的完整贡献之和 (mod MOD)
int block_cnt;     // 已构造的块数，也是覆盖 N <= 1e9 所需的块号上限

// 按 Golomb 序列的自描述规则构造块表：
// 值 p 总共要出现 a[p] 次，所以连续产生 a[p] 个「值为 p」的块。
void build_block() {
    block[0].appear_cnt = 0;
    block[0].end_pos = 0;
    block[1].appear_cnt = 1;
    block[1].end_pos = 1;
    block[2].appear_cnt = 2;
    block[2].end_pos = 3;
    block[3].appear_cnt = 2; // 题面给出的初始段 1,2,2 决定 a[3] = 2
    block[3].end_pos = 5;

    int k = 3;      // 当前块号
    int value = 3;  // 正在复制的块号：值 value 要出现 block[value].appear_cnt 次
    ll used = 0;    // 值 value 已经复制出去的次数
    while (block[k].end_pos < LIMIT) {
        if (used == block[value].appear_cnt) { // 值 value 已经用完，换下一个值
            value++;
            used = 0;
        }
        k++;
        block[k].appear_cnt = value;
        block[k].end_pos = block[k - 1].end_pos + value;
        used++;
    }
    block_cnt = k;

    // pref[k] = Σ_{i<=k} i * (第 i 块的位置编号之和)，位置编号之和用等差数列公式
    pref[0] = 0;
    for (int i = 1; i <= block_cnt; i++) {
        ll left_end = block[i - 1].end_pos + 1;
        ll right_end = block[i].end_pos;
        ll cnt = right_end - left_end + 1;
        ll pos_sum = (left_end + right_end) % MOD * (cnt % MOD) % MOD * INV2 % MOD;
        pref[i] = (pref[i - 1] + i % MOD * pos_sum) % MOD;
    }
}

// 求 last(last(n)) mod MOD = Σ_{v<=n} v*a[v]：定位 n 所在块，整块查前缀和，
// 最后一块只取到 n 为止的等差部分。
ll query(ll n) {
    int lo = 1;
    int hi = block_cnt;
    while (lo < hi) { // 找最小的 g 使 end_pos[g] >= n
        int mid = (lo + hi) / 2;
        if (block[mid].end_pos >= n) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    ll g = lo;
    ll left_end = block[g - 1].end_pos + 1;
    ll cnt = n - left_end + 1;
    ll pos_sum = (left_end + n) % MOD * (cnt % MOD) % MOD * INV2 % MOD;
    return (pref[g - 1] + g % MOD * pos_sum) % MOD;
}

void solve() {
    ll T;
    if (!(cin >> T)) {
        return;
    }
    for (ll i = 1; i <= T; i++) {
        ll n;
        cin >> n;
        cout << query(n) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    build_block();
    solve();

    return 0;
}
