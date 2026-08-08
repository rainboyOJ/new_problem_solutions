// brute.cpp：把每个单词排序成标准形后去重，作为教学版和对拍基准程序。
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

        // 排序后的结果只和每个字母出现次数有关。
        sort(s.begin(), s.end());
        classes_of_words.insert(s);
    }

    cout << classes_of_words.size() << '\n';
    return 0;
}
