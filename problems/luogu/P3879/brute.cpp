#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接用 map 记录每个单词出现在哪些文章里。
// 由于同一篇文章里可能出现同一个单词多次，所以要先去重。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    map<string, vector<int> > mp;

    for (int i = 1; i <= n; i++) {
        int cnt;
        cin >> cnt;
        set<string> used;
        for (int j = 1; j <= cnt; j++) {
            string s;
            cin >> s;
            used.insert(s);
        }

        for (set<string>::iterator it = used.begin(); it != used.end(); ++it) {
            mp[*it].push_back(i);
        }
    }

    int m;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        string s;
        cin >> s;
        vector<int> &v = mp[s];
        for (int j = 0; j < (int) v.size(); j++) {
            if (j > 0) {
                cout << ' ';
            }
            cout << v[j];
        }
        cout << '\n';
    }

    return 0;
}
