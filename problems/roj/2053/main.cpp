/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:59
 * update_at: 2026-10-06 09:59
 */
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXS = 100;   // 优惠套餐数上限
const int MAXDIM = 5;   // 清单商品种类数上限
const int STATE = 7776; // 6^5：每种商品最多买 5 件，状态编码上界

struct Species {
    ll id;    // 商品编号
    ll num;   // 需要购买的件数
    ll price; // 原价
};

ll species_cnt;
Species species[MAXDIM]; // 购物清单，排序后第 i 项对应状态的第 i 维

int index_of[1000]; // index_of[商品编号] = 维度下标，不在清单中则为 -1

ll raw_cnt[MAXS];            // 第 t 个套餐包含的商品种类数
ll raw_id[MAXS][MAXDIM];     // 第 t 个套餐的第 i 种商品编号
ll raw_num[MAXS][MAXDIM];    // 第 t 个套餐的第 i 种商品份数
ll raw_price[MAXS];          // 第 t 个套餐的优惠价

ll deal_code[MAXS];          // 保留的套餐编码成 6 进制数
ll deal_digit[MAXS][MAXDIM]; // 保留的套餐在各维上的份数
ll deal_price[MAXS];         // 保留的套餐的优惠价
ll deal_cnt;                 // 去重后保留的套餐数

ll best_price[STATE]; // best_price[code] 存同一份数向量的最低套餐价，-1 表示无
ll memo[STATE];       // memo[code] = 剩余需求为 code 时的最低花费，-1 表示未算过
ll pow6[MAXDIM + 1];  // pow6[i] = 6^i，用于状态与向量的进位编码

// 按商品编号升序排列，使清单维度与编号顺序对应，便于把套餐换算成维度向量。
bool cmp_species(Species a, Species b) {
    return a.id < b.id;
}

// 把一份剩余需求向量编码成 6 进制整数。
ll encode(ll left[]) {
    ll code = 0;
    for (ll i = 0; i < species_cnt; i++) {
        code = code + left[i] * pow6[i];
    }
    return code;
}

// 读取套餐与购物清单，并把套餐换算成清单维度上的份数向量。
void read_input() {
    ll s;
    cin >> s;
    for (ll t = 0; t < s; t++) {
        cin >> raw_cnt[t];
        for (ll i = 0; i < raw_cnt[t]; i++) {
            cin >> raw_id[t][i] >> raw_num[t][i];
        }
        cin >> raw_price[t];
    }

    cin >> species_cnt;
    for (ll i = 0; i < species_cnt; i++) {
        cin >> species[i].id >> species[i].num >> species[i].price;
    }
    sort(species, species + species_cnt, cmp_species);
    for (ll i = 0; i < 1000; i++) {
        index_of[i] = -1;
    }
    for (ll i = 0; i < species_cnt; i++) {
        index_of[species[i].id] = (int)i;
    }

    pow6[0] = 1;
    for (ll i = 1; i <= MAXDIM; i++) {
        pow6[i] = pow6[i - 1] * 6;
    }
    for (ll i = 0; i < STATE; i++) {
        best_price[i] = -1;
        memo[i] = -1;
    }

    for (ll t = 0; t < s; t++) {
        ll digit[MAXDIM];
        for (ll i = 0; i < MAXDIM; i++) {
            digit[i] = 0;
        }
        bool valid = true;
        for (ll i = 0; i < raw_cnt[t]; i++) {
            int pos = index_of[raw_id[t][i]];
            if (pos == -1) { // 套餐含清单外商品，题面禁止顺带购买，整条丢弃
                valid = false;
                break;
            }
            digit[pos] = raw_num[t][i];
        }
        if (!valid) {
            continue;
        }
        bool empty = true;
        for (ll i = 0; i < species_cnt; i++) {
            if (digit[i] > 0) {
                empty = false;
            }
        }
        if (empty) { // 空套餐等于白送，会形成零代价自环，丢弃
            continue;
        }
        ll code = encode(digit);
        if (best_price[code] == -1 || raw_price[t] < best_price[code]) {
            best_price[code] = raw_price[t];
        }
    }

    for (ll code = 0; code < STATE; code++) {
        if (best_price[code] != -1) {
            deal_code[deal_cnt] = code;
            deal_price[deal_cnt] = best_price[code];
            ll rest = code;
            for (ll i = 0; i < species_cnt; i++) {
                deal_digit[deal_cnt][i] = rest % 6;
                rest = rest / 6;
            }
            deal_cnt++;
        }
    }
}

// 记忆化搜索：left 为各商品还差几件时的最低花费。
// 每次要么按原价买一件，要么套用一个不超过剩余需求的套餐。
ll dfs(ll code) {
    if (code == 0) {
        return 0;
    }
    if (memo[code] != -1) {
        return memo[code];
    }
    ll left[MAXDIM];
    ll rest = code;
    for (ll i = 0; i < species_cnt; i++) {
        left[i] = rest % 6;
        rest = rest / 6;
    }

    ll ans = -1;
    for (ll i = 0; i < species_cnt; i++) {
        if (left[i] > 0) { // 按原价补一件，保证状态一定向 0 收敛
            ll cand = species[i].price + dfs(code - pow6[i]);
            if (ans == -1 || cand < ans) {
                ans = cand;
            }
        }
    }
    for (ll j = 0; j < deal_cnt; j++) {
        bool fit = true;
        for (ll i = 0; i < species_cnt; i++) {
            if (left[i] < deal_digit[j][i]) { // 套餐超过剩余需求，题面禁止多买
                fit = false;
                break;
            }
        }
        if (!fit) {
            continue;
        }
        ll cand = deal_price[j] + dfs(code - deal_code[j]);
        if (ans == -1 || cand < ans) {
            ans = cand;
        }
    }

    memo[code] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();

    ll want[MAXDIM];
    for (ll i = 0; i < species_cnt; i++) {
        want[i] = species[i].num;
    }
    cout << dfs(encode(want)) << endl;

    return 0;
}
