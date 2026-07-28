/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-28 21:58
 * update_at: 2026-07-28 21:58
 */
// brute.cpp：排序字符串作 key，分组输出。
// O(n * k log k)，适合小数据，帮助理解题意。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        for (const string& s : strs) {
            string key = s;
            sort(key.begin(), key.end());
            groups[key].push_back(s);
        }
        vector<vector<string>> ans;
        for (auto& [_, v] : groups)
            ans.push_back(move(v));
        return ans;
    }
};

// 本地测试 adapter，提交 LeetCode 时只保留 Solution 类
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> strs(n);
    for (int i = 0; i < n; i++)
        cin >> strs[i];

    auto ans = Solution().groupAnagrams(strs);
    for (auto& group : ans) {
        for (size_t i = 0; i < group.size(); i++) {
            if (i) cout << ' ';
            cout << group[i];
        }
        cout << '\n';
    }
    return 0;
}
