/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 08:59
 * update_at: 2026-10-06 08:59
 */

#include <iostream>
#include <string>
#include <map>
using namespace std;

typedef long long ll;

const int MAXN = 25; // 人数上限，n <= 20

string names[MAXN];       // 按输入顺序保存名字
map<string, int> id;      // 名字 -> 下标
ll money[MAXN];           // 每个人的最终钱数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> names[i];
        id[names[i]] = i;
    }

    string giver;
    while (cin >> giver) { // 每条记录以送钱人名字开头，读到 EOF 结束
        ll m;
        int cnt;
        cin >> m >> cnt;

        ll share = 0, left = 0;
        if (cnt != 0) {            // cnt 为 0 时不做除法
            share = m / cnt;
            left = m % cnt;
        }

        int g = id[giver];
        money[g] += left - m;      // 送钱人扣掉真正分出去的部分，余数自留
        for (int i = 0; i < cnt; i++) {
            string receiver;
            cin >> receiver;
            money[id[receiver]] += share;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << names[i] << " " << money[i] << "\n";
    }
    return 0;
}
