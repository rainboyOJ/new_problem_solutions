/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-01 10:24
 * update_at: 2026-11-01 10:24
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int MAXN = 50005;
const int LOG = 17;
const ll NEG_INF = -(1LL << 60);
// 编号与长度不超过50000，用int；前缀和、候选权值用long long。
int n, q, lg[MAXN];
ll prefix_sum[MAXN], max_st[LOG][MAXN], min_st[LOG][MAXN];
ll candidate[MAXN], answer[MAXN];
int que[MAXN];

void build_st() {
    for (int i = 2; i <= n + 1; i++) lg[i] = lg[i / 2] + 1;
    for (int i = 0; i <= n; i++) max_st[0][i] = min_st[0][i] = prefix_sum[i];
    for (int k = 1; (1 << k) <= n + 1; k++) {
        int half = 1 << (k - 1);
        for (int i = 0; i + (1 << k) <= n + 1; i++) {
            max_st[k][i] = max(max_st[k - 1][i], max_st[k - 1][i + half]);
            min_st[k][i] = min(min_st[k - 1][i], min_st[k - 1][i + half]);
        }
    }
}

ll range_max(int left, int right) {
    int k = lg[right - left + 1];
    return max(max_st[k][left], max_st[k][right - (1 << k) + 1]);
}

ll range_min(int left, int right) {
    int k = lg[right - left + 1];
    return min(min_st[k][left], min_st[k][right - (1 << k) + 1]);
}

// 对每个位置i，用candidate[i+left_shift .. i+right_shift]的最大值更新答案。
// 窗口裁到[0,n]；两端随i右移，next保证每个候选只入队一次。
void merge_window(int left_shift, int right_shift) {
    int head = 0, tail = 0, next = 0;
    for (int i = 1; i <= n; i++) {
        int right = min(n, i + right_shift);
        while (next <= right) {
            while (head < tail && candidate[que[tail - 1]] <= candidate[next]) tail--;
            que[tail++] = next++;
        }
        int left = max(0, i + left_shift);
        while (head < tail && que[head] < left) head++;
        if (head < tail) answer[i] = max(answer[i], candidate[que[head]]);
    }
}

void compute_answers(int L, int R) {
    fill(answer + 1, answer + n + 1, NEG_INF);
    fill(candidate, candidate + n + 1, NEG_INF);

    // A：位置i落在区间的前L个点，固定左前缀x。
    for (int x = 0; x + L <= n; x++) {
        candidate[x] = range_max(x + L, min(n, x + R)) - prefix_sum[x];
    }
    merge_window(-L, -1);
    if (L == R) return; // 固定长度时，A已经覆盖区间的每个位置。

    int h = (R - L) / 2 + 1;
    int long_length = L + h;

    // B：固定x，只取长度至少L+h的区间；i对应的x窗口宽h。
    fill(candidate, candidate + n + 1, NEG_INF);
    for (int x = 0; x + long_length <= n; x++) {
        candidate[x] = range_max(x + long_length, min(n, x + R)) - prefix_sum[x];
    }
    merge_window(-L - h + 1, -L);

    // C：固定右端点y，同样只取长度至少L+h的区间。
    fill(candidate, candidate + n + 1, NEG_INF);
    for (int y = long_length; y <= n; y++) {
        candidate[y] = prefix_sum[y] - range_min(max(0, y - R), y - long_length);
    }
    merge_window(0, h - 1);

    // D：左右端点相互独立的小矩形，任意配对的长度都在[L,R]内。
    for (int i = L; i <= n; i++) {
        ll value = range_max(i, min(n, i + h - 1))
                 - range_min(max(0, i - L - h + 1), i - L);
        answer[i] = max(answer[i], value);
    }
}

ull checksum() {
    ull result = 0;
    // 先转无符号，再相乘：负数及乘法都按模2^64解释。
    for (int i = 1; i <= n; i++) result ^= (ull)i * (ull)answer[i];
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        ll value;
        cin >> value;
        prefix_sum[i] = prefix_sum[i - 1] + value;
    }
    build_st();
    cin >> q;
    while (q--) {
        int L, R;
        cin >> L >> R;
        compute_answers(L, R);
        cout << checksum() << '\n';
    }
    return 0;
}
