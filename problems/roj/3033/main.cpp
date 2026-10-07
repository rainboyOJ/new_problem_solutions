/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:20
 * update_at: 2026-10-06 11:20
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXID = 1000000; // 编号范围 0 ~ 999999
const int MAXT = 1005;     // 小组数上限 1000，多开一点

int member[MAXID];      // member[x]：编号 x 所属的小组下标（只存 0~999，用 int 省内存）
queue<ll> seats[MAXT];  // seats[g]：小组 g 内部成员的先后队列，队首是本组最前面的人
queue<ll> order;        // order：当前队列中各个小组块的先后顺序，队首是最前面的小组

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;          // 小组数量，读到 0 结束
    ll scenario = 0;
    while (cin >> t && t != 0) {
        scenario++;

        for (ll g = 0; g < t; g++) {
            ll size;
            cin >> size;
            for (ll i = 0; i < size; i++) {
                ll x;
                cin >> x;
                member[x] = g;
            }
        }

        // 清空上一用例残留的两级队列
        while (!order.empty()) order.pop();
        for (ll g = 0; g < t; g++) {
            while (!seats[g].empty()) seats[g].pop();
        }

        cout << "Scenario #" << scenario << '\n';

        string command;
        while (cin >> command) {
            if (command == "STOP") break;

            if (command == "DEQUEUE") {
                ll g = order.front(); // 队列非空是题意保证：为空时不会要求出队
                ll x = seats[g].front();
                seats[g].pop();
                cout << x << '\n';
                if (seats[g].empty()) order.pop(); // 本组最后一人走了，小组块才离开块序列
            } else { // ENQUEUE
                ll x;
                cin >> x;
                ll g = member[x];
                if (seats[g].empty()) order.push(g); // 本组还不在队伍里，把小组块压到队尾
                seats[g].push(x);                    // 否则直接接在本组最后一人后面
            }
        }

        cout << '\n'; // 每个用例（含最后一个）末尾都补一个空行
    }

    return 0;
}
