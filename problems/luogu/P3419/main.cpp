#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXP = 500005;
const int INF = 1000000007;

int n, k, p;
int a[MAXP];            // a[i] 表示第 i 次请求的玩具车编号
int nxt_pos[MAXP];      // nxt_pos[i] 表示这次请求的车下一次什么时候再出现
int last_pos[MAXN];     // 倒着扫时，记录每种车最近一次出现的位置
bool in_floor[MAXN];    // 当前这辆车是否在地板上
int current_next[MAXN]; // 当前在地板上的这辆车，下一次会在什么时候被请求

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> p;
    for (int i = 1; i <= p; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        last_pos[i] = INF;
    }

    for (int i = p; i >= 1; i--) {
        nxt_pos[i] = last_pos[a[i]];
        last_pos[a[i]] = i;
    }

    // 按“下一次出现位置”排序，位置越大说明越晚才会再用到，越应该被淘汰。
    set<pair<int, int> > st;
    int used = 0; // 当前地板上放了多少辆车
    int ans = 0;  // 从书架拿下来的总次数

    for (int i = 1; i <= p; i++) {
        int x = a[i];

        if (in_floor[x]) {
            // 已经在地板上，只需要把“下一次出现时间”更新成新的值。
            st.erase(make_pair(current_next[x], x));
            current_next[x] = nxt_pos[i];
            st.insert(make_pair(current_next[x], x));
            continue;
        }

        ans++;

        if (used == k) {
            // 地板满了，删掉未来最晚才会再被请求的那辆车。
            set<pair<int, int> >::iterator it = st.end();
            --it;
            int del = it->second;
            st.erase(it);
            in_floor[del] = false;
            used--;
        }

        in_floor[x] = true;
        current_next[x] = nxt_pos[i];
        st.insert(make_pair(current_next[x], x));
        used++;
    }

    cout << ans << '\n';
    return 0;
}
