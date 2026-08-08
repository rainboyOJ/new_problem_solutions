#include <bits/stdc++.h>
using namespace std;

int n, m, c, k;
vector<unsigned long long> animals;
vector<int> rule_p;
vector<int> rule_q;
unordered_set<unsigned long long> exist_animal;
unordered_set<int> current_feed;

// 小数据直接判断二进制位。
bool has_bit(unsigned long long x, int p) {
    return (x >> p) & 1ULL;
}

void build_current_feed() {
    current_feed.clear();

    // 朴素做法：枚举每只当前动物，再检查每一条规则是否触发。
    for (int i = 0; i < n; i++) {
        unsigned long long x = animals[i];
        for (int j = 0; j < m; j++) {
            if (has_bit(x, rule_p[j])) {
                current_feed.insert(rule_q[j]);
            }
        }
    }
}

bool can_add(unsigned long long x) {
    // 直接模拟：如果 x 会触发某条“当前还没买过”的饲料规则，
    // 那么加入它后清单就会变化，这种动物不能算。
    for (int i = 0; i < m; i++) {
        if (has_bit(x, rule_p[i]) && current_feed.find(rule_q[i]) == current_feed.end()) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> c >> k;

    animals.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> animals[i];
        exist_animal.insert(animals[i]);
    }

    rule_p.resize(m);
    rule_q.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> rule_p[i] >> rule_q[i];
    }

    build_current_feed();

    unsigned long long limit = 1ULL << k;
    unsigned long long ans = 0;
    for (unsigned long long x = 0; x < limit; x++) {
        if (exist_animal.find(x) != exist_animal.end()) {
            continue;
        }
        if (can_add(x)) {
            ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}
