/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:13
 * update_at: 2026-10-05 12:13
 */

#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

string s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> s;
    // 位置 k 的左右孩子分别是 2k+1、2k+2，
    // 所以相邻位置 (1,2)、(3,4)、... 恰好是一对对兄弟。
    // 每对兄弟同空或同非空时对称；出现一个空一个非空就不对称。
    // 末尾缺失的孩子补 # 只会产生同空对，不影响结论。
    ll n = s.size();
    while ((ll)s.size() < 2 * n) s.push_back('#'); // 补长到 2n
    for (ll i = 1; i + 1 < (ll)s.size(); i += 2) {
        bool left_empty = (s[i] == '#');
        bool right_empty = (s[i + 1] == '#');
        if (left_empty != right_empty) {
            cout << "No\n";
            return 0;
        }
    }
    cout << "Yes\n";
    return 0;
}
