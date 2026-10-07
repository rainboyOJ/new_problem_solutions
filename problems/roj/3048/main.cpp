/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:14
 * update_at: 2026-10-06 16:14
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXM = 1005;

ll n, m;
ll heights[MAXM + 2]; // heights[j] 表示以当前行为底，第 j 列向上连续的 'F' 格数
int stk[MAXM + 2];    // 单调栈，存下标，对应的 heights 从栈底到栈顶严格递增
int top_idx;          // 栈顶指针，stk[1..top_idx] 为有效元素

// 求以当前行为底的直方图最大矩形面积
ll max_histogram_area() {
    ll best = 0;
    top_idx = 0;
    // i 扫描到 m+1，视作高度为 0 的哨兵，保证收尾时栈内柱子全部结算
    for (int i = 1; i <= m + 1; i++) {
        ll cur = (i <= m) ? heights[i] : 0;
        // 当前柱子比栈顶矮（或等高），说明栈顶柱子的右边界确定为 i
        while (top_idx > 0 && heights[stk[top_idx]] >= cur) {
            int bar = stk[top_idx];
            top_idx--;
            int left = (top_idx > 0) ? stk[top_idx] : 0; // 左边第一个更矮的位置
            ll area = heights[bar] * (i - left - 1);
            if (area > best) {
                best = area;
            }
        }
        stk[++top_idx] = i;
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    ll answer = 0;
    for (int r = 1; r <= n; r++) {
        for (int j = 1; j <= m; j++) {
            char cell;
            cin >> cell;
            // F 可以踩着上一行继续长高，R 把该列高度清零
            if (cell == 'F') {
                heights[j]++;
            } else {
                heights[j] = 0;
            }
        }
        ll area = max_histogram_area();
        if (area > answer) {
            answer = area;
        }
    }

    cout << answer * 3 << '\n'; // 题面要求输出 3 倍最大面积
    return 0;
}
