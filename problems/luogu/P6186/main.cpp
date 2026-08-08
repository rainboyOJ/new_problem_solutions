#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n, m;
int p[MAXN];         // p[i] 表示当前位置上的数
int inv_cnt[MAXN];   // inv_cnt[x] 表示当前有多少个比 x 大的数在 x 左边

int bit_val[MAXN];   // 计算初始 inv_cnt 时使用：按值统计出现次数
int bit_num[MAXN];   // 按 inv_cnt 的取值统计有多少个数
long long bit_sum[MAXN]; // 按 inv_cnt 的取值统计 inv_cnt 总和

int lowbit(int x) {
    return x & -x;
}

void add_bit(int bit[], int pos, int val) {
    for (int i = pos; i <= n; i += lowbit(i)) {
        bit[i] += val;
    }
}

int sum_bit(int bit[], int pos) {
    int ret = 0;
    for (int i = pos; i > 0; i -= lowbit(i)) {
        ret += bit[i];
    }
    return ret;
}

void add_bit_sum(int pos, long long val) {
    for (int i = pos; i <= n; i += lowbit(i)) {
        bit_sum[i] += val;
    }
}

long long sum_bit_sum(int pos) {
    long long ret = 0;
    for (int i = pos; i > 0; i -= lowbit(i)) {
        ret += bit_sum[i];
    }
    return ret;
}

// 在“inv_cnt 的分布”上删除旧值，再加入新值。
void modify_inv_cnt(int x, int new_value) {
    int old_value = inv_cnt[x];
    add_bit(bit_num, old_value + 1, -1);
    add_bit_sum(old_value + 1, -old_value);

    inv_cnt[x] = new_value;

    add_bit(bit_num, new_value + 1, 1);
    add_bit_sum(new_value + 1, new_value);
}

long long query_answer(int k) {
    if (k >= n) {
        return 0;
    }

    // 只统计 inv_cnt > k 的那些值。
    int cnt = sum_bit(bit_num, n) - sum_bit(bit_num, k + 1);
    long long s = sum_bit_sum(n) - sum_bit_sum(k + 1);
    return s - 1LL * k * cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    // 预处理每个值 x 的 inv_cnt[x]：
    // 扫描到 p[i] 时，前面一共有 i-1 个数，其中 <= p[i] 的个数能用树状数组求出，
    // 因而“前面比它大的数”就是这两者之差。
    for (int i = 1; i <= n; i++) {
        int x = p[i];
        int not_greater = sum_bit(bit_val, x);
        inv_cnt[x] = (i - 1) - not_greater;
        add_bit(bit_val, x, 1);
    }

    // 建立 inv_cnt 的值域分布。
    for (int x = 1; x <= n; x++) {
        add_bit(bit_num, inv_cnt[x] + 1, 1);
        add_bit_sum(inv_cnt[x] + 1, inv_cnt[x]);
    }

    while (m--) {
        int op;
        cin >> op;

        if (op == 1) {
            int pos;
            cin >> pos;
            int a = p[pos];
            int b = p[pos + 1];

            if (a < b) {
                // 顺序对交换后会变成逆序对，较小值 a 左边多了一个更大的数 b。
                modify_inv_cnt(a, inv_cnt[a] + 1);
            } else {
                // 逆序对交换后会被消掉，较小值 b 左边少了一个更大的数 a。
                modify_inv_cnt(b, inv_cnt[b] - 1);
            }

            swap(p[pos], p[pos + 1]);
        } else {
            int k;
            cin >> k;
            cout << query_answer(k) << '\n';
        }
    }

    return 0;
}
