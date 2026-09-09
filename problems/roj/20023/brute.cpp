/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 23:40
 * update_at: 2026-08-28 23:40
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 做法：对每次询问，把区间内的曲目原样取出来、按难度从小到大排序，
//       再按题目规则逐首检查（下一首难度 = 上一首 或 上一首 + 1），不满足就终止。
//       这是对题面最直接的模拟，复杂度高，只适合小数据。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, m;
int a[MAXN];

// 直接模拟区间 [l, r] 的练习过程，返回练习的曲目数量。
int brute_ask(int l, int r) {
    vector<int> b;
    for (int i = l; i <= r; i++) {
        b.push_back(a[i]);
    }
    // 按难度从小到大排序
    sort(b.begin(), b.end());

    int ans = 1; // 区间内至少有一首，第一首一定被练习
    for (size_t i = 1; i < b.size(); i++) {
        // 下一首难度必须等于上一首，或比上一首大 1
        if (b[i] == b[i - 1] || b[i] == b[i - 1] + 1) {
            ans++;
        } else {
            break; // 出现断档，终止练习
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    cin >> m;
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << brute_ask(l, r) << '\n';
    }

    return 0;
}
