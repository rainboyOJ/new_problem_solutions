#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll l,r;
int main (int argc, char *argv[]) {
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> l >> r;
        ll sum_lr = (l+r) % 9;
        ll len = (r-l+1) % 9;

        ll ans = ( sum_lr * len * 5) %9;
        std::cout << ans << "\n";
    }
    
    return 0;
}
