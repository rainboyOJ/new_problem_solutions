/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:03
 * update_at: 2026-10-05 08:03
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;

int n;                    // 当前组测试数据的建筑数量
int h[MAXN];              // 建筑高度序列，下标从 1 开始
int key[MAXN];            // key[i] = -h[i]，把"下降"翻成"上升"
int tails[MAXN];          // tails[L-1] 是长度为 L 的上升子序列的最小结尾；序列严格递增

// 在 tails[0..len-1] 上二分：找到第一个 >= value 的位置 p。
// p == len 表示 value 比所有层结尾都大，可以再接一层；
// 否则 p 是 value 顶替的位置，让同长度留出更小的结尾。
int lower_bound_pos(int len, int value) {
    int l = 0, r = len; // [l, r) 半开区间
    while (l < r) {
        int mid = (l + r) / 2;
        if (tails[mid] < value) l = mid + 1;
        else r = mid;
    }
    return l;
}

// 求 seq[1..len] 上严格上升子序列的最大长度；调用前 seq 已是准备好的序列
int lis_length(int len) {
    int sz = 0; // 当前 tails 的有效长度
    for (int i = 1; i <= len; i++) {
        int p = lower_bound_pos(sz, key[i]);
        if (p == sz) {
            tails[sz] = key[i]; // 追加一层
        } else {
            tails[p] = key[i];   // 顶替同长度的结尾
        }
        sz = (p == sz) ? sz + 1 : sz;
    }
    return sz;
}

// 一次单向滑翔最多经过的建筑数；方向任选、起点任选，但只能飞向更低的建筑
int best_glide(int len) {
    // 向右滑：下标递增、高度递减 → 取负后变成严格上升子序列
    for (int i = 1; i <= len; i++) key[i] = -h[i];
    int right_ans = lis_length(len);

    // 向左滑：把序列反转，等价于反转序列的向右滑
    for (int i = 1; i <= len; i++) key[i] = -h[len - i + 1];
    int left_ans = lis_length(len);

    return right_ans > left_ans ? right_ans : left_ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k; // 测试数据组数
    cin >> k;
    while (k--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> h[i];
        cout << best_glide(n) << "\n";
    }

    return 0;
}