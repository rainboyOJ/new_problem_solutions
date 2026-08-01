/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-01 10:37
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500000;
const int MAXM = 10000;
const int MAXD = 20;
const int MAXNODE = MAXN * 4 + 5;

struct Operation {
    int type;
    int l;
    int r;
    long long v;
};

struct Info {
    int s0;
    int s00;
    int sp[MAXD];
    int sp0[MAXD];
};

int n, m;
long long base_k;
int digits;
vector<long long> value_array;
vector<Operation> operations;

int sum0[MAXNODE];
int sum00[MAXNODE];
int sum_p[MAXD][MAXNODE];
int sum_p0[MAXD][MAXNODE];
int lazy_shift[MAXD][MAXNODE];

void split_digits(long long x, int result[MAXD]) {
    for (int i = 0; i < MAXD; i++) {
        result[i] = 0;
    }
    for (int i = 0; i < digits; i++) {
        result[i] = (int)(x % base_k);
        x /= base_k;
    }
}

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

void answer_query(const Info &info) {
    long long inverse_two = (base_k + 1) / 2;
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
