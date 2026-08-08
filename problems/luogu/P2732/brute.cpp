#include <bits/stdc++.h>
using namespace std;

const int MAXS = 110;
const int MAXB = 5;
const int MAXO = 120;
const int MAXSTATE = 8000;
const int INF = 1e9;

struct RawOffer {
    int item_cnt;
    int code[6];
    int num[6];
    int price;
} raw_offer[MAXS];

struct Offer {
    int num[MAXB];
    int price;
} offer[MAXO];

int s, b;
int target_code[MAXB], need[MAXB], single_price[MAXB];
int pow6[6];
int offer_cnt;
int memo[MAXSTATE];
bool vis[MAXSTATE];

int get_id(int code) {
    for (int i = 0; i < b; i++) {
        if (target_code[i] == code) {
            return i;
        }
    }
    return -1;
}

void add_offer(int cnt[], int price) {
    offer_cnt++;
    for (int i = 0; i < b; i++) {
        offer[offer_cnt].num[i] = cnt[i];
    }
    offer[offer_cnt].price = price;
}

int dfs(int state) {
    if (state == 0) {
        return 0;
    }
    if (vis[state]) {
        return memo[state];
    }
    vis[state] = true;

    int rem[MAXB] = {0};
    int x = state;
    for (int i = 0; i < b; i++) {
        rem[i] = x % 6;
        x /= 6;
    }

    int ans = INF;

    for (int k = 1; k <= offer_cnt; k++) {
        bool ok = true;
        int next_state = state;

        for (int i = 0; i < b; i++) {
            if (offer[k].num[i] > rem[i]) {
                ok = false;
                break;
            }
            next_state -= offer[k].num[i] * pow6[i];
        }

        if (ok) {
            ans = min(ans, dfs(next_state) + offer[k].price);
        }
    }

    memo[state] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
    // 从目标购买状态出发，递归尝试最后一次使用哪一个优惠包或单买方案。
    cin >> s;
    for (int i = 1; i <= s; i++) {
        cin >> raw_offer[i].item_cnt;
        for (int j = 0; j < raw_offer[i].item_cnt; j++) {
            cin >> raw_offer[i].code[j] >> raw_offer[i].num[j];
        }
        cin >> raw_offer[i].price;
    }

    cin >> b;
    for (int i = 0; i < b; i++) {
        cin >> target_code[i] >> need[i] >> single_price[i];
    }

    for (int i = 1; i <= s; i++) {
        int cnt[MAXB] = {0};
        bool bad = false;
        bool useful = false;

        for (int j = 0; j < raw_offer[i].item_cnt; j++) {
            int id = get_id(raw_offer[i].code[j]);
            if (id == -1) {
                bad = true;
                break;
            }
            cnt[id] += raw_offer[i].num[j];
            useful = true;
        }

        if (!bad && useful) {
            add_offer(cnt, raw_offer[i].price);
        }
    }

    for (int i = 0; i < b; i++) {
        int cnt[MAXB] = {0};
        cnt[i] = 1;
        add_offer(cnt, single_price[i]);
    }

    pow6[0] = 1;
    for (int i = 1; i <= b; i++) {
        pow6[i] = pow6[i - 1] * 6;
    }

    int target_state = 0;
    for (int i = 0; i < b; i++) {
        target_state += need[i] * pow6[i];
    }

    cout << dfs(target_state) << '\n';
    return 0;
}
