/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:01
 * update_at: 2026-10-05 10:01
 */
// roj 1332 【例2-1】周末舞会
#include <iostream>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll men_count, women_count, dances;
    cin >> men_count >> women_count;
    cin >> dances;

    // 出队者立刻回到队尾，队伍只是整体轮转，
    // 所以第 i 支舞曲的出场编号就是两条长度分别为 m、n 的循环序列。
    for (ll i = 1; i <= dances; i++) {
        ll man = (i - 1) % men_count + 1;     // 男队队头编号
        ll woman = (i - 1) % women_count + 1; // 女队队头编号
        cout << man << ' ' << woman << '\n';
    }
    return 0;
}
