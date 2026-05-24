#include <iostream>
#include <set>
using namespace std;
const int maxn=2e6+5;
int n;
int a[maxn];

std::set<int> myset;


//暴力枚举以 a[j]为结尾的元素
void work() {
    int ans = 0;

    for(int j = 1;j <= n ;++j ) // j: 1->n
    {
        myset.clear();
        for(int i = j;i >= 1 ;--i ) // i: j->1
        {
            if( myset.find(a[i]) != myset.end() ) break;
            myset.insert(a[i]);
            if( ans < myset.size()) 
                ans = myset.size();
        }
    }
    std::cout << ans << "\n";
}

int main() {
    int T;
    std::cin >> T;
    while (T--) {
        std::cin >> n;
        for(int i = 1;i <= n ;++i ) // i: 1->n
        {
            std::cin >> a[i];
        }
        work();
    }
    
    return 0;
}
