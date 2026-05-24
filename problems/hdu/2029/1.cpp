/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-24 15:55:42
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,m;
char a[maxn];

void check(){
    int i = 0;
    int j = strlen(a) - 1;

    while (i < j) {
        if( a[i] != a[j]) 
        {
            std::cout << "no" << "\n";
            return;
        }
        i++;
        j--;
    }
    std::cout << "yes" << "\n";
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    std::cin >> n;

    while (n--) {
        std::cin >> a;
        check();
    }

    
    return 0;
}
