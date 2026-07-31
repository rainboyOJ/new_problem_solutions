/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:28
 */
// brute.cpp：顺次跳过每一段相同数字。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; i++) cin >> numbers[i];
    int answer = 0;
    int position = 0;
    while (position < n) {
        answer++;
        int next = position + 1;
        while (next < n && numbers[next] == numbers[position]) next++;
        position = next;
    }
    cout << answer << '\n';
    return 0;
}
