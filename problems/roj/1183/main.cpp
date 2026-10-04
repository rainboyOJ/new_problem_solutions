/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:33
 * update_at: 2026-10-05 04:33
 */
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

// n < 100，开 105 足够。
const ll MAXN = 105;

// 老年人门槛：年龄 >= 60 者优先看病。
const ll ELDERLY_AGE = 60;

// 病人：ID 含前导零，必须用字符串保存，不能转成整数。
struct Patient {
    string id;
    ll age;
    ll idx; // 登记序号，即输入行的先后，用来打破同组内的平局
};

Patient pat[MAXN]; // pat[i] 表示第 i 个登记的病人

ll n;

// 排队规则：老年人优先；老年人按年龄从大到小；其余情况一律按登记先后。
bool cmp_by_visit_order(const Patient &a, const Patient &b) {
    ll group_a = (a.age >= ELDERLY_AGE) ? 0 : 1; // 老年人取 0，排前面
    ll group_b = (b.age >= ELDERLY_AGE) ? 0 : 1;
    if (group_a != group_b) return group_a < group_b;
    // 同组内：老年人比年龄（大的在前），非老年人不比年龄（年龄一律看成 0）
    ll key_a = (a.age >= ELDERLY_AGE) ? -a.age : 0;
    ll key_b = (b.age >= ELDERLY_AGE) ? -b.age : 0;
    if (key_a != key_b) return key_a < key_b;
    return a.idx < b.idx; // 平局由登记序号裁决
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> pat[i].id >> pat[i].age;
        pat[i].idx = i;
    }

    sort(pat + 1, pat + n + 1, cmp_by_visit_order);

    for (ll i = 1; i <= n; i++) {
        cout << pat[i].id << "\n";
    }

    return 0;
}
