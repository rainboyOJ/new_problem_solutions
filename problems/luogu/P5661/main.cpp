#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5;   // 最大记录数 n <= 1e5
const int maxp = 1000 + 5;     // 票价上限 price <= 1000，按票价分桶

// 一张地铁优惠票的完整信息
struct Ticket {
    int price;  // 地铁票价（可抵扣的额度）
    int time;   // 乘地铁的时间
    int id;     // 记录编号（同时是获得顺序，越小越早）
};

int n;
int typ[maxn], price[maxn], tim[maxn];  // 第 i 条记录：类型(0地铁/1公交)、票价、时间
long long ans;                          // 总花费

// all_tickets：所有"未过期且未被使用"的地铁票，按获得时间(记录编号)递增
// 用它来按时间顺序丢弃超过 45 分钟的过期票
queue<Ticket> all_tickets;

// bucket[p]：票价为 p 的地铁票的记录编号，同桶内编号递增
// 因为"若有多张可用票优先用最早的"，所以每个桶只需看队首
queue<int> bucket[maxp];

// removed_ticket[i]：第 i 条记录（地铁票）是否已失效(过期/已使用)
// 采用"惰性删除"：不在队列中间真正删除，只在出队时跳过
bool removed_ticket[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> typ[i] >> price[i] >> tim[i];

        // 记录按时间递增给出，因此只需要从队首弹出过期的票
        // 条件：t_bus - t_subway > 45 即失效
        while (!all_tickets.empty() && all_tickets.front().time + 45 < tim[i]) {
            removed_ticket[all_tickets.front().id] = true;
            all_tickets.pop();
        }

        // 乘地铁：必须花钱，同时获得一张有效期为 45 分钟的优惠票
        if (typ[i] == 0) {
            ans += price[i];
            all_tickets.push({price[i], tim[i], i});
            bucket[price[i]].push(i);
            continue;
        }

        // 乘公交：在票价 >= 本次票价的桶里找最早获得的那张票
        int choose_id = -1;      // 选中的票的记录编号
        int choose_price = -1;   // 选中的票的票价（即所在桶）

        // 票价只需枚举到 1000；每个桶先惰性弹出已失效的票，再看队首
        for (int p = price[i]; p <= 1000; p++) {
            while (!bucket[p].empty() && removed_ticket[bucket[p].front()]) {
                bucket[p].pop();
            }

            if (!bucket[p].empty()) {
                int id = bucket[p].front();
                // 多个桶都有票时，取记录编号最小的（获得最早的）
                if (choose_id == -1 || id < choose_id) {
                    choose_id = id;
                    choose_price = p;
                }
            }
        }

        if (choose_id == -1) {
            // 没有可用优惠票，只能全价乘车
            ans += price[i];
        } else {
            // 用掉这张票：标记失效，并从对应桶中弹出
            removed_ticket[choose_id] = true;
            bucket[choose_price].pop();
        }
    }

    cout << ans << '\n';
    return 0;
}
