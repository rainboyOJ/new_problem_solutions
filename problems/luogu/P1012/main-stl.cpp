/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 01:43
 * update_at: 2026-10-07 01:43
 */
// 这是 STL 写法：用 vector<string> 保存每个数，用函数对象 CmpConcat 表达
// 「谁排在前面」的拼接规则，再把这个规则交给 sort。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<string> nums; // 每个正整数按原样（字符串）保存，避免拼接后超出整数范围

// 比较规则：x 拼在 y 前面能拼出更大的数时返回 true。
// cmp(x, y) 回答的是「x 应该排在 y 前面吗」，不是「谁更大」。
struct CmpConcat {
    bool operator()(const string &x, const string &y) const {
        return x + y > y + x; // 只看两种拼接顺序哪个更大
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        string s;
        cin >> s;
        nums.push_back(s);
    }

    // 传入函数对象作为比较规则，让 sort 按「谁排在前面」重排整个 vector
    sort(nums.begin(), nums.end(), CmpConcat());

    for (ll i = 0; i < n; i++) {
        cout << nums[i];
    }
    cout << '\n';

    return 0;
}
