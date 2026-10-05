/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:45
 * update_at: 2026-10-06 01:45
 */
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

ll first_pos[26]; // first_pos[c] 表示颜色 c 首次出现的笔编号，0 表示还没出现

int main() {
    string s;
    cin >> s;
    ll n = s.size();
    for (ll pos = 1; pos <= n; pos++) {
        ll color = s[pos - 1] - 'A'; // 把 A~Z 映射到 0~25
        if (first_pos[color] != 0) {
            // 这种颜色之前出现过，first_pos 里存的就是较小的编号
            cout << first_pos[color] << " " << pos << "\n";
            return 0;
        }
        first_pos[color] = pos;
    }
    cout << "different\n";
    return 0;
}
