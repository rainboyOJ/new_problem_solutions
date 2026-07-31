/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:34
 */
#include <bits/stdc++.h>
using namespace std;

struct Element {
    int index, value;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b;
    cin >> n >> a >> b;
    vector<Element> first(a);
    for (int i = 0; i < a; i++) cin >> first[i].index >> first[i].value;

    long long answer = 0;
    int position = 0;
    for (int i = 0; i < b; i++) {
        Element second;
        cin >> second.index >> second.value;
        while (position < a && first[position].index < second.index) position++;
        if (position < a && first[position].index == second.index) {
            answer += 1LL * first[position].value * second.value;
        }
    }
    cout << answer << '\n';

    return 0;
}
