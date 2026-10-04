/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:37
 * update_at: 2026-10-04 23:37
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll side[3]; // 三条线段长度，读入后升序排列

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 3; i++) {
        cin >> side[i];
    }
    sort(side, side + 3); // 升序后 side[2] 是最长边

    // 两条短边之和严格大于最长边即构成三角形；取等表示共线退化，仍输出 no。
    if (side[0] + side[1] > side[2]) {
        cout << "yes" << "\n";
    } else {
        cout << "no" << "\n";
    }

    return 0;
}
