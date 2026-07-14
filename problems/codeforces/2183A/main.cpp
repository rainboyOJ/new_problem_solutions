/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-14 23:50
 * update_at: 2026-07-14 23:50
 */
#include <bits/stdc++.h>
using namespace std;

std::vector<int> a;
int T;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    std::cin >> T;
    while (T--) {
        int n;
        std::cin >> n;
        a.clear();
        for(int i = 1;i <= n ;++i ) // i: 1->n
        {
            int t;
            std::cin >> t;
            a.push_back(t);
        }
        if(a[0] == 1 || a[a.size() - 1])
            std::cout << "Alice" << "\n";
        else
            std::cout << "Bob" << "\n";
    }

    return 0;
}
