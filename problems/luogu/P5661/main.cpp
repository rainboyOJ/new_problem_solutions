#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5;
const int maxp = 1000 + 5;

struct Ticket {
    int price;
    int time;
    int id;
};

int n;
int typ[maxn], price[maxn], tim[maxn];
long long ans;
queue<Ticket> all_tickets;
queue<int> bucket[maxp];
bool removed_ticket[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> typ[i] >> price[i] >> tim[i];

        while (!all_tickets.empty() && all_tickets.front().time + 45 < tim[i]) {
            removed_ticket[all_tickets.front().id] = true;
            all_tickets.pop();
        }

        if (typ[i] == 0) {
            ans += price[i];
            all_tickets.push({price[i], tim[i], i});
            bucket[price[i]].push(i);
            continue;
        }

        int choose_id = -1;
        int choose_price = -1;

        for (int p = price[i]; p <= 1000; p++) {
            while (!bucket[p].empty() && removed_ticket[bucket[p].front()]) {
                bucket[p].pop();
            }

            if (!bucket[p].empty()) {
                int id = bucket[p].front();
                if (choose_id == -1 || id < choose_id) {
                    choose_id = id;
                    choose_price = p;
                }
            }
        }

        if (choose_id == -1) {
            ans += price[i];
        } else {
            removed_ticket[choose_id] = true;
            bucket[choose_price].pop();
        }
    }

    cout << ans << '\n';
    return 0;
}
