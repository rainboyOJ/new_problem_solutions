#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int T;
int n;
long long a[MAXN];

// left_max[i] 表示下标 i 左侧(不含 i)的最高高度
long long left_max_arr[MAXN];
// right_max[i] 表示下标 i 右侧(不含 i)的最高高度
long long right_max_arr[MAXN];

// pre[i] 表示 1..i 的前缀最高值
long long pre_max[MAXN];
// suf[i] 表示 i..n 的后缀最高值
long long suf_max[MAXN];

// water[i] 表示原序列在位置 i 产生的积水量
long long water_arr[MAXN];
// pre_water[i] 表示 water 的前缀和
long long pre_water[MAXN];

// nxt_ge[i] 表示 i 右边第一个高度 >= a[i] 的位置，不存在则为 n+1
int nxt_ge[MAXN];
// pre_ge[i] 表示 i 左边第一个高度 >= a[i] 的位置，不存在则为 0
int pre_ge_pos[MAXN];

// 如果把 i 变矮，会影响它右边一段位置的积水：
// old_right[i] 是这一段在原序列中的积水总量
// new_right[i] 是删掉 i 这块挡板后，这一段新的积水总量
long long old_right[MAXN];
long long new_right[MAXN];

// 同理，影响左边一段位置时使用下面两个数组
long long old_left[MAXN];
long long new_left[MAXN];

int stk[MAXN];

void build_prefix_suffix() {
    pre_max[0] = 0;
    for (int i = 1; i <= n; i++) {
        pre_max[i] = max(pre_max[i - 1], a[i]);
    }

    suf_max[n + 1] = 0;
    for (int i = n; i >= 1; i--) {
        suf_max[i] = max(suf_max[i + 1], a[i]);
    }

    for (int i = 1; i <= n; i++) {
        left_max_arr[i] = pre_max[i - 1];
        right_max_arr[i] = suf_max[i + 1];
    }
}

long long build_original_water() {
    long long total = 0;
    pre_water[0] = 0;
    for (int i = 1; i <= n; i++) {
        long long level = min(pre_max[i], suf_max[i]);
        if (level > a[i]) {
            water_arr[i] = level - a[i];
        }
        else {
            water_arr[i] = 0;
        }
        total += water_arr[i];
        pre_water[i] = pre_water[i - 1] + water_arr[i];
    }
    return total;
}

void build_nearest_ge() {
    int top = 0;
    for (int i = n; i >= 1; i--) {
        while (top > 0 && a[stk[top]] < a[i]) {
            top--;
        }
        if (top == 0) {
            nxt_ge[i] = n + 1;
        }
        else {
            nxt_ge[i] = stk[top];
        }
        stk[++top] = i;
    }

    top = 0;
    for (int i = 1; i <= n; i++) {
        while (top > 0 && a[stk[top]] < a[i]) {
            top--;
        }
        if (top == 0) {
            pre_ge_pos[i] = 0;
        }
        else {
            pre_ge_pos[i] = stk[top];
        }
        stk[++top] = i;
    }
}

void build_right_change() {
    for (int i = 1; i <= n; i++) {
        old_right[i] = 0;
        new_right[i] = 0;
    }

    int i = 1;
    while (i <= n) {
        // 只有“从左向右看见的新高点”才可能作为右侧许多位置的左挡板
        if (a[i] > pre_max[i - 1]) {
            int r = nxt_ge[i];
            int L = i + 1;
            int R;
            if (r <= n) {
                R = r - 1;
            }
            else {
                R = n;
            }

            if (L <= R) {
                old_right[i] = pre_water[R] - pre_water[L - 1];

                // 把 i 改低到不超过外部挡板后，
                // 这段区间的左侧最高值会退回到 pre_max[i - 1]，
                // 然后从左往右重新维护前缀最高值即可。
                long long cur_left_max = pre_max[i - 1];
                long long sum = 0;
                for (int j = L; j <= R; j++) {
                    cur_left_max = max(cur_left_max, a[j]);
                    long long level = min(cur_left_max, suf_max[j]);
                    if (level > a[j]) {
                        sum += level - a[j];
                    }
                }
                new_right[i] = sum;
            }

            i = R + 1;
        }
        else {
            i++;
        }
    }
}

void build_left_change() {
    for (int i = 1; i <= n; i++) {
        old_left[i] = 0;
        new_left[i] = 0;
    }

    int i = n;
    while (i >= 1) {
        // 对称地处理“从右向左看见的新高点”
        if (a[i] > suf_max[i + 1]) {
            int l = pre_ge_pos[i];
            int L;
            if (l >= 1) {
                L = l + 1;
            }
            else {
                L = 1;
            }
            int R = i - 1;

            if (L <= R) {
                old_left[i] = pre_water[R] - pre_water[L - 1];

                long long cur_right_max = suf_max[i + 1];
                long long sum = 0;
                for (int j = R; j >= L; j--) {
                    cur_right_max = max(cur_right_max, a[j]);
                    long long level = min(pre_max[j], cur_right_max);
                    if (level > a[j]) {
                        sum += level - a[j];
                    }
                }
                new_left[i] = sum;
            }

            i = L - 1;
        }
        else {
            i--;
        }
    }
}

long long solve_one_case() {
    build_prefix_suffix();
    long long total_water = build_original_water();
    build_nearest_ge();
    build_right_change();
    build_left_change();

    long long answer = (long long)4e18;

    for (int i = 1; i <= n; i++) {
        // 位置 i 自己的最优新高度一定取：
        // max(1, min(左侧外部最高, 右侧外部最高))
        // 这样既不会比需要的更高，也不会违反“正整数”限制。
        long long new_height = min(left_max_arr[i], right_max_arr[i]);
        if (new_height < 1) {
            new_height = 1;
        }

        long long self_water = 0;
        long long self_level = min(max(left_max_arr[i], new_height), max(right_max_arr[i], new_height));
        if (self_level > new_height) {
            self_water = self_level - new_height;
        }

        long long cand = total_water;
        cand -= water_arr[i];
        cand -= old_right[i];
        cand -= old_left[i];
        cand += self_water;
        cand += new_right[i];
        cand += new_left[i];

        answer = min(answer, cand);
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        cout << solve_one_case() << '\n';
    }

    return 0;
}
