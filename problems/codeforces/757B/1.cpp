#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int cnt[maxn];
int n;

void init(){
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int t;
        std::cin >> t;
        cnt[t]++;
    }
}


int main (int argc, char *argv[]) {
    init();
    int ans = 1;
    for(int g = 2;g < maxn ;++g ) // g: 1->maxn
    {
        int now_sum = 0;
        for(int i = g ; i < maxn ;i+=g) {
            now_sum += cnt[i];
        }
        ans = max(ans,now_sum);
    }
    std::cout << ans << "\n";

    return 0;
}
