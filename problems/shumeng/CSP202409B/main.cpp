/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 01:17
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);
    string initial = line.substr(1, line.size() - 2);

    int n;
    cin >> n;
    getline(cin, line);
    int next_char[128];
    for (int i = 0; i < 128; i++) next_char[i] = i;
    for (int i = 0; i < n; i++) {
        getline(cin, line);
        next_char[(unsigned char)line[1]] = (unsigned char)line[2];
    }

    const int LOG = 31;
    int jump[LOG][128];
    for (int i = 0; i < 128; i++) jump[0][i] = next_char[i];
    for (int bit = 1; bit < LOG; bit++) {
        for (int i = 0; i < 128; i++) {
            jump[bit][i] = jump[bit - 1][jump[bit - 1][i]];
        }
    }

    int m;
    cin >> m;
    for (int query = 0; query < m; query++) {
        long long k;
        cin >> k;
        string result;
        for (int i = 0; i < (int)initial.size(); i++) {
            int current = (unsigned char)initial[i];
            long long steps = k;
            int bit = 0;
            while (steps > 0) {
                if (steps & 1) current = jump[bit][current];
                steps >>= 1;
                bit++;
            }
            result.push_back((char)current);
        }
        cout << '#' << result << "#\n";
    }

    return 0;
}
