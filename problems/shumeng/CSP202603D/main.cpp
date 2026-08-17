/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500000;
const int MAXM = 10000;
const int MAXD = 20;        // k 进制位数上限
const int MAXNODE = MAXN * 4 + 5;

// 一条操作：type=1 区间加，type=2 区间查询
struct Operation {
    int type;
    int l;
    int r;
    long long v;
};

// 一次区间查询聚合出来的统计量，各量都按模 k 保存
struct Info {
    int s0;          // 第 0 位 d0 之和
    int s00;         // d0^2 之和
    int sp[MAXD];    // sp[p] 为第 p 位 dp 之和
    int sp0[MAXD];   // sp0[p] 为 dp*d0 之和
};

int n, m;
long long base_k;      // k 进制基数
int digits;            // 当前有效位数
vector<long long> value_array; // 原始序列，1 下标
vector<Operation> operations;  // 全部操作

// 线段树全局数组：sum0/sum00 存第 0 位统计，sum_p/sum_p0 存高位统计
int sum0[MAXNODE];
int sum00[MAXNODE];
int sum_p[MAXD][MAXNODE];
int sum_p0[MAXD][MAXNODE];
int lazy_shift[MAXD][MAXNODE]; // 懒标记：每个数位当前的平移量

// 把 x 拆成 k 进制各位，结果写入 result[0..digits-1]。
void split_digits(long long x, int result[MAXD]) {
    for (int i = 0; i < MAXD; i++) {
        result[i] = 0;
    }
    for (int i = 0; i < digits; i++) {
        result[i] = (int)(x % base_k);
        x /= base_k;
    }
}

// 给节点 p 的整体加 shift：所有位各自平移，length 是节点覆盖的区间长度。
// 核心是利用完全平方公式：(d+c)^2 = d^2 + 2cd + c^2 逐项更新各统计量。
void apply_shift(int p, int length, int shift[MAXD]) {
    int old_s0 = sum0[p];
    int old_s00 = sum00[p];
    int s0_shift = shift[0];
    long long len_mod = length % base_k;

    sum0[p] = (int)((old_s0 + len_mod * s0_shift) % base_k);
    sum00[p] = (int)((old_s00 + 2LL * s0_shift * old_s0
                      + len_mod * s0_shift % base_k * s0_shift) % base_k);

    for (int digit = 1; digit < digits; digit++) {
        int old_sp = sum_p[digit][p];
        int old_sp0 = sum_p0[digit][p];
        int digit_shift = shift[digit];
        // (d+c)*(d0+c0) = d*d0 + c*d0 + d*c0 + c*c0
        long long next_sp0 = old_sp0;
        next_sp0 += 1LL * s0_shift * old_sp;
        next_sp0 += 1LL * digit_shift * old_s0;
        next_sp0 += len_mod * digit_shift % base_k * s0_shift;
        sum_p[digit][p] = (int)((old_sp + len_mod * digit_shift) % base_k);
        sum_p0[digit][p] = (int)(next_sp0 % base_k);
    }

    for (int digit = 0; digit < digits; digit++) {
        lazy_shift[digit][p] = (int)((lazy_shift[digit][p] + shift[digit]) % base_k);
    }
}

// 用左右孩子合并当前节点的统计量。
void pull(int p) {
    int left = p * 2;
    int right = left + 1;
    sum0[p] = (int)((sum0[left] + (long long)sum0[right]) % base_k);
    sum00[p] = (int)((sum00[left] + (long long)sum00[right]) % base_k);
    for (int digit = 1; digit < digits; digit++) {
        sum_p[digit][p] = (int)((sum_p[digit][left]
                                 + (long long)sum_p[digit][right]) % base_k);
        sum_p0[digit][p] = (int)((sum_p0[digit][left]
                                  + (long long)sum_p0[digit][right]) % base_k);
    }
}

// 建树：叶子节点直接保存原数的各位统计量。
void build(int p, int l, int r) {
    if (l == r) {
        int digit_value[MAXD];
        split_digits(value_array[l], digit_value);
        sum0[p] = digit_value[0] % base_k;
        sum00[p] = (int)(1LL * digit_value[0] * digit_value[0] % base_k);
        for (int digit = 1; digit < digits; digit++) {
            sum_p[digit][p] = digit_value[digit] % base_k;
            sum_p0[digit][p] = (int)(1LL * digit_value[digit]
                                      * digit_value[0] % base_k);
        }
        return;
    }
    int mid = (l + r) / 2;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
    pull(p);
}

// 把节点 p 的懒标记下传给两个孩子。
void push_down(int p, int l, int r) {
    bool has_lazy = false;
    int shift[MAXD];
    for (int digit = 0; digit < digits; digit++) {
        shift[digit] = lazy_shift[digit][p];
        if (shift[digit] != 0) {
            has_lazy = true;
        }
    }
    if (!has_lazy || l == r) {
        return;
    }
    int mid = (l + r) / 2;
    apply_shift(p * 2, mid - l + 1, shift);
    apply_shift(p * 2 + 1, r - mid, shift);
    for (int digit = 0; digit < digits; digit++) {
        lazy_shift[digit][p] = 0;
    }
}

// 区间加：给 [ql, qr] 上的每个数整体平移 shift。
void update(int p, int l, int r, int ql, int qr, int shift[MAXD]) {
    if (ql <= l && r <= qr) {
        apply_shift(p, r - l + 1, shift);
        return;
    }
    push_down(p, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid) {
        update(p * 2, l, mid, ql, qr, shift);
    }
    if (qr > mid) {
        update(p * 2 + 1, mid + 1, r, ql, qr, shift);
    }
    pull(p);
}

// 取出节点 p 的统计量，拼成 Info 结构。
Info node_info(int p) {
    Info result;
    result.s0 = sum0[p];
    result.s00 = sum00[p];
    for (int digit = 0; digit < MAXD; digit++) {
        result.sp[digit] = 0;
        result.sp0[digit] = 0;
    }
    for (int digit = 1; digit < digits; digit++) {
        result.sp[digit] = sum_p[digit][p];
        result.sp0[digit] = sum_p0[digit][p];
    }
    return result;
}

// 合并两个区间的统计量，用于查询拼接。
Info merge_info(const Info &left, const Info &right) {
    Info result;
    result.s0 = (int)((left.s0 + (long long)right.s0) % base_k);
    result.s00 = (int)((left.s00 + (long long)right.s00) % base_k);
    for (int digit = 0; digit < MAXD; digit++) {
        result.sp[digit] = 0;
        result.sp0[digit] = 0;
    }
    for (int digit = 1; digit < digits; digit++) {
        result.sp[digit] = (int)((left.sp[digit]
                                  + (long long)right.sp[digit]) % base_k);
        result.sp0[digit] = (int)((left.sp0[digit]
                                   + (long long)right.sp0[digit]) % base_k);
    }
    return result;
}

// 区间查询：返回 [ql, qr] 聚合出的统计量。
Info query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return node_info(p);
    }
    push_down(p, l, r);
    int mid = (l + r) / 2;
    if (qr <= mid) {
        return query(p * 2, l, mid, ql, qr);
    }
    if (ql > mid) {
        return query(p * 2 + 1, mid + 1, r, ql, qr);
    }
    Info left = query(p * 2, l, mid, ql, qr);
    Info right = query(p * 2 + 1, mid + 1, r, ql, qr);
    return merge_info(left, right);
}

// 打印 __int128，因为 k 的幂可能超出 long long 范围。
void print_int128(__int128 value) {
    if (value == 0) {
        cout << 0 << '\n';
        return;
    }
    string result;
    while (value > 0) {
        result.push_back((char)('0' + value % 10));
        value /= 10;
    }
    reverse(result.begin(), result.end());
    cout << result << '\n';
}

// 由聚合统计量还原答案：第 0 位是 (S00+S0)/2，第 p 位是 Sp0+Sp。
void answer_query(const Info &info) {
    long long inverse_two = (base_k + 1) / 2; // k 为奇数，2 的逆元
    int low = (int)((info.s00 + (long long)info.s0) % base_k);
    low = (int)(low * inverse_two % base_k);

    __int128 answer = low;
    __int128 power = base_k;
    for (int digit = 1; digit < digits; digit++) {
        int current = (info.sp0[digit] + (long long)info.sp[digit]) % base_k;
        answer += power * current;
        power *= base_k;
    }
    print_int128(answer);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> base_k;
    value_array.assign(n + 1, 0);
    long long max_value = 0;
    for (int i = 1; i <= n; i++) {
        cin >> value_array[i];
        max_value = max(max_value, value_array[i]);
    }

    // 先读入全部操作，统计出现过的最大值，确定需要的 k 进制位数
    operations.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> operations[i].type;
        if (operations[i].type == 1) {
            cin >> operations[i].l >> operations[i].r >> operations[i].v;
            max_value = max(max_value, operations[i].v);
        } else {
            cin >> operations[i].l >> operations[i].r;
            operations[i].v = 0;
        }
    }

    digits = 1;
    while (max_value >= base_k && digits < MAXD) {
        max_value /= base_k;
        digits++;
    }

    build(1, 1, n);
    for (int i = 0; i < m; i++) {
        if (operations[i].type == 1) {
            int shift[MAXD];
            split_digits(operations[i].v, shift);
            update(1, 1, n, operations[i].l, operations[i].r, shift);
        } else {
            Info result = query(1, 1, n, operations[i].l, operations[i].r);
            answer_query(result);
        }
    }
    return 0;
}