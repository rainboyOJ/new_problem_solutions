/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 21:38
 * update_at: 2026-10-04 21:38
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;

struct Girl {
    ll score;   // 评分
    ll id;      // 读入编号，从 1 开始
    string name;
};

vector<Girl> bucket[26]; // bucket[c] 存放名字以字符 'a' + c 结尾的妹子
ll cnt[26];             // cnt[c] = bucket[c] 中的元素个数

// 排序比较：评分大的在前，评分相同时先读入（编号小）的在前
bool cmp_girl(const Girl &a, const Girl &b) {
    if (a.score != b.score) return a.score > b.score;
    return a.id < b.id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    // 读入时按名字的最后一个字母分桶，顺便记下读入编号
    for (ll i = 1; i <= n; i++) {
        string name;
        ll score;
        cin >> name >> score;
        int c = name[name.size() - 1] - 'a';
        Girl g;
        g.score = score;
        g.id = i;
        g.name = name;
        bucket[c].push_back(g);
        cnt[c]++;
    }

    // 每个桶内部排好序，桶内下标 k - 1 就是该字母下第 k 大的名字
    for (int c = 0; c < 26; c++) {
        sort(bucket[c].begin(), bucket[c].end(), cmp_girl);
    }

    for (ll q = 1; q <= m; q++) {
        char x;
        ll k;
        cin >> x >> k;
        int c = x - 'a';
        if (k > cnt[c]) {
            cout << "Orz YYR tql" << endl;
        } else {
            cout << bucket[c][k - 1].name << endl;
        }
    }

    return 0;
}