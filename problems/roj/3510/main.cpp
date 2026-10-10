/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int NEG = -1000000000;

// end[p]：从 p 出发能匹配的最短单词的末尾下标；匹配不到为 -1
int end_[205];
int cut[205][205];   // cut[t][j]：把 [t, j) 单独作一份时能数到的单词起点数
int f[205][45];      // f[j][m]：前 j 个字符分成 m 份的最大单词数

// 多组输入，每组算一次
int max_words(const string& text, const vector<string>& words, int k) {
    int n = (int)text.size();
    for (int p = 0; p < n; p++) {
        int best = -1;
        for (size_t i = 0; i < words.size(); i++) {
            if (text.compare(p, words[i].size(), words[i]) == 0) {
                int e = p + (int)words[i].size() - 1;
                if (best == -1 || e < best) best = e;
            }
        }
        end_[p] = best;
    }
    // cut 打表
    for (int j = 1; j <= n; j++) {
        int acc = 0;
        for (int t = j - 1; t >= 0; t--) {
            if (end_[t] != -1 && end_[t] <= j - 1) acc++;
            cut[t][j] = acc;
        }
    }
    for (int j = 0; j <= n; j++)
        for (int m = 0; m <= k; m++)
            f[j][m] = NEG;
    f[0][0] = 0;
    for (int j = 1; j <= n; j++) {
        for (int m = 1; m <= min(j, k); m++) {
            int best = NEG;
            for (int t = m - 1; t < j; t++) {
                if (f[t][m - 1] > NEG) {
                    int v = f[t][m - 1] + cut[t][j];
                    if (v > best) best = v;
                }
            }
            f[j][m] = best;
        }
    }
    return f[n][k];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    vector<string> lines;
    while (getline(cin, line)) {
        // 去首尾空白
        string t;
        int a = 0, b = (int)line.size();
        while (a < b && isspace((unsigned char)line[a])) a++;
        while (b > a && isspace((unsigned char)line[b - 1])) b--;
        t = line.substr(a, b - a);
        if (!t.empty()) lines.push_back(t);
    }
    size_t i = 0;
    while (i < lines.size()) {
        int p, k;
        stringstream ss(lines[i]);
        ss >> p >> k;
        i++;
        string text;
        for (int j = 0; j < p && i < lines.size(); j++, i++)
            text += lines[i];
        int s = 0;
        if (i < lines.size()) {
            stringstream ss2(lines[i]);
            ss2 >> s;
            i++;
        }
        vector<string> words;
        for (int j = 0; j < s && i < lines.size(); j++, i++)
            words.push_back(lines[i]);
        cout << max_words(text, words, k) << "\n";
    }
    return 0;
}
