#include <bits/stdc++.h>
using namespace std;

int n;
set<string> classes_of_words;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;

        // 同一类单词排序后一定得到同一个标准形。
        sort(s.begin(), s.end());
        classes_of_words.insert(s);
    }

    cout << classes_of_words.size() << '\n';
    return 0;
}
