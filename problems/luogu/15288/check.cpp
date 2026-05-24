//随机数据生成
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int maxn = 1e6;
int n,k;
std::vector<int> a;
std::vector<int> b;

std::random_device rd;
std::default_random_engine __rnd(rd());

// 预先定义的随机数生成器 https://en.cppreference.com/w/cpp/numeric/random
std::mt19937 mtrnd(rd());

// 每一次产生指定范围内的随机数
// std::uniform_int_distribution
// https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution

//生成[l,r]之间的随机整数
int rnd(int l,int r) {
    return __rnd() % (r-l+1) + l;
}

// 洗牌,用于产生n个不重复的随机数
// 例如： [1,n] 区间随机排列
struct myShuffle {
    int a[maxn];
    int idx;
    myShuffle(int n) :idx(0)
    {
        for(int i = 0;i<=n;i++) a[i] = n;
        std::shuffle(a+1,a+n+1,mtrnd);
    }

    int get() {
        return a[++idx];
    }
};

// 从i开始求长度为看的元素的和
int sum(int st,int k) {
    int t= 0 ;
    for(int i = st;i <= st+k-1;i++)
    {
        int idx= i ;
        if( idx >= n)  {
            idx %= n;
        }
        t += a[ b[idx] ];
    }
    return t;
}

//检查是否成立
bool check() {
    int tot = sum(0,k);
    for(int i = 1;i <n;i++) {
        if( sum(i,k) != tot)
            return 0;   
    }
    return 1;
}

//满足\beta n % k ==0 && n/k=t c_a /t + cb / t + cc/t = k && diff_cnt <=k
bool check2(){
    if( n % k != 0 ) return 0;
    int diff_cnt = 0;
    std::map<int,int> m;
    for( auto i : a) {

        if( m[i] == 0) {
            diff_cnt++;
        }
        m[i]++;
    }
    if( diff_cnt > k) return 0;

    int t = n / k;

    int sum_t = 0;
    for(auto i : m) {
        sum_t += i.second / t;
    }
    return sum_t == k;
}

int main() {
    int T;
    std::cin >> T;
    std::cin >> n;
    std::cin >> k;

    for(int i = 0;i < n ;++i ) // i: 1->n
    {
        int t;
        std::cin >> t;
        a.push_back(t);
        b.push_back(i);
    }

    do {
        if( check())  {
            for( auto i : b) {
                std::cout << a[i] << " ";
            }
            std::cout << " yes1 ";
            std::cout << "check2->"<<  check2() <<  "\n";
            std::cout << "\n";
            break;
        }
    } while( std::next_permutation(b.begin(),b.end()));

    return 0;
}
