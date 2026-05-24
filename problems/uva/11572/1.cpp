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
    myset.clear();

    int i = 1;
    for(int j = 1;j <= n ;++j ) // j: 1->n
    {
        while( myset.find(a[j]) != myset.end() )
        {
            myset.erase(a[i]);
            i++;
        }
        myset.insert(a[j]);
        if( ans < myset.size())
            ans = myset.size();
        
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
