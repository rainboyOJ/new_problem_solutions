/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:24
 * update_at: 2026-10-06 00:24
 */

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 15;

// str[i] : 第 i 个数字串，下标从 1 开始
string str[MAXN];

// 判断 a 是否是 b 的前缀
bool is_prefix(const string &a, const string &b) {
    if (a.size() > b.size()) return false;
    return b.compare(0, a.size(), a) == 0;
}

int main() {
    string s;
    int cas = 0;
    while (cin >> s) {
        if (s == "9") continue; // 单独的 9 是结束标志，不参与前缀判定

        int n = 1;
        str[1] = s;
        while (cin >> s && s != "9") { // 读入本组的所有数字串，读到 9 结束
            str[++n] = s;
        }

        sort(str + 1, str + 1 + n);
        cas++;

        // 字典序排序后，若某串是另一串的前缀，则必有一对相邻串满足前缀关系
        bool decodable = true;
        for (int i = 1; i < n; i++) {
            if (is_prefix(str[i], str[i + 1])) decodable = false;
        }

        if (decodable)
            cout << "Set " << cas << " is immediately decodable" << endl;
        else
            cout << "Set " << cas << " is not immediately decodable" << endl;
    }
    return 0;
}
