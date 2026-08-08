/* author: Rainboy email: rainboylvx@qq.com  time: 2022年 12月 10日 星期六 10:10:31 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const long long maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

long long k,n,m;
/* 定义全局变量 */
long long e,d;

#define fenc cout << "\n=================\n";

#define log(args...) { cout << "LINE:" << __LINE__ << " ";string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " = " << a << endl;
	err(++it, args...);
}

int main(){
    std::cin >> k;
    for(long long i=1;i<=k;++i){
        std::cin >> n >> e >> d;
        m = n- e*d+2;
        // log(m);


        //b^2-4ac
        //a = 1
        //b = -m
        //c = n
        long long dlte = m*m-4*n;
        // log(dlte);
        if( dlte < 0){
            std::cout << "NO\n" ;
        }
        else {
            long long q = (m + (long long)sqrt(dlte)) / 2;
            long long p = m-q;
            if(q > p)
                std::swap(q,p);
            if( p+q == m && p*q == n){
                std::cout << q <<" "<< p << "\n";
            }
            else
                std::cout << "NO\n" ;

        }
    }
    return 0;
}
