#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;
const int LOG = 17;
const long long INF = (1LL << 62);

int n, q;
long long prefix_sum[MAXN];
long long max_st[LOG][MAXN], min_st[LOG][MAXN];
int lg2_value[MAXN];

long long best_left[MAXN], best_right[MAXN], best_start[MAXN], answer_pos[MAXN];
int que[MAXN];

void build_st() {
    lg2_value[1] = 0;
    for (int i = 2; i <= n + 1; i++) {
        lg2_value[i] = lg2_value[i >> 1] + 1;
    }

    for (int i = 0; i <= n; i++) {
        max_st[0][i] = prefix_sum[i];
        min_st[0][i] = prefix_sum[i];
    }

    for (int j = 1; j < LOG; j++) {
        int len = 1 << j;
        for (int i = 0; i + len - 1 <= n; i++) {
            max_st[j][i] = max(max_st[j - 1][i], max_st[j - 1][i + (len >> 1)]);
            min_st[j][i] = min(min_st[j - 1][i], min_st[j - 1][i + (len >> 1)]);
        }
    }
}

long long range_max_prefix(int l, int r) {
    l = max(l, 0);
    r = min(r, n);
    if (l > r) {
        return -INF;
    }
    int len = r - l + 1;
    int lg = lg2_value[len];
    return max(max_st[lg][l], max_st[lg][r - (1 << lg) + 1]);
}

long long range_min_prefix(int l, int r) {
    l = max(l, 0);
    r = min(r, n);
    if (l > r) {
        return INF;
    }
    int len = r - l + 1;
    int lg = lg2_value[len];
    return min(min_st[lg][l], min_st[lg][r - (1 << lg) + 1]);
}

void push_max_queue(int &head, int &tail, long long value_array[], int pos) {
    while (head <= tail && value_array[que[tail]] <= value_array[pos]) {
        tail--;
    }
    que[++tail] = pos;
}

unsigned long long solve_query(int L, int R) {
    for (int i = 0; i <= n + 2; i++) {
        best_left[i] = -INF;
        best_right[i] = -INF;
        best_start[i] = -INF;
        answer_pos[i] = -INF;
    }

    // 右侧平行四边形：固定左前缀位置 x，右端点在 [x+L, x+R]。
    for (int x = 0; x + L <= n; x++) {
        best_start[x] = range_max_prefix(x + L, x + R) - prefix_sum[x];
    }

    int head = 1, tail = 0;
    for (int i = 1; i <= n; i++) {
        while (head <= tail && que[head] < i - L) {
            head++;
        }
        push_max_queue(head, tail, best_start, i - 1);
        answer_pos[i] = best_start[que[head]];
    }

    int half = R - L + 1;
    if (half & 1) {
        half++;
    }
    half >>= 1;

    // 左侧三角形拆出来的第一块。
    for (int x = 0; x + L + half <= n; x++) {
        best_left[x] = range_max_prefix(x + L + half, x + R) - prefix_sum[x];
    }

    head = 1;
    tail = 0;
    for (int i = L; i <= n; i++) {
        int expired = i - L - half;
        int add_pos = i - L;
        while (head <= tail && que[head] <= expired) {
            head++;
        }
        push_max_queue(head, tail, best_left, add_pos);
        if (head <= tail) {
            answer_pos[i] = max(answer_pos[i], best_left[que[head]]);
        }
    }

    // 左侧三角形拆出来的第二块。
    for (int y = L + half; y <= n; y++) {
        best_right[y] = prefix_sum[y] - range_min_prefix(y - R, y - L - half);
    }

    head = 1;
    tail = 0;
    for (int i = L + 1; i <= n; i++) {
        int add_pos = i + half - 1;
        while (head <= tail && que[head] < i) {
            head++;
        }
        if (add_pos <= n) {
            push_max_queue(head, tail, best_right, add_pos);
        }
        if (head <= tail) {
            answer_pos[i] = max(answer_pos[i], best_right[que[head]]);
        }
    }

    // 中间正方形：左右端点可以分开取最优前缀最大值和最小值。
    for (int i = L; i <= n; i++) {
        long long value = range_max_prefix(i, i + half - 1)
                        - range_min_prefix(i - L - half + 1, i - L);
        answer_pos[i] = max(answer_pos[i], value);
    }

    unsigned long long result = 0;
    for (int i = 1; i <= n; i++) {
        long long product = answer_pos[i] * (long long)i;
        result ^= (unsigned long long)product;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        prefix_sum[i] = prefix_sum[i - 1] + x;
    }

    build_st();

    cin >> q;
    while (q--) {
        int L, R;
        cin >> L >> R;
        cout << solve_query(L, R) << '\n';
    }

    return 0;
}
