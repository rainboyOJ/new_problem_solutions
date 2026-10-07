/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:23
 * update_at: 2026-10-05 12:23
 */

#include <cstdio>
#include <queue>
#include <string>
#include <iostream>

using namespace std;

typedef long long ll;

// 大根堆：堆顶是当前排队中优先级最大的患者（pair 先比优先级，再比姓名）
priority_queue< pair<ll, string> > q;

int main() {
    ll n;
    scanf("%lld", &n);

    for (ll i = 1; i <= n; i++) {
        string op;
        cin >> op;
        if (op == "push") {
            string name;
            ll pri;
            cin >> name >> pri;
            q.push(make_pair(pri, name)); // 入队
        } else {
            // pop：输出当前优先级最大的患者
            if (q.empty()) {
                printf("none\n");
            } else {
                cout << q.top().second << " " << q.top().first << endl;
                q.pop();
            }
        }
    }
    return 0;
}
