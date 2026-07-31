#include <bits/stdc++.h>
using namespace std;
int n;
typedef map<int,int> M;
M m;


void set_m(int cnt,int id){
    int val = m[cnt];
    if(val == 0){
        m[cnt] = id;
    }
    else {
        m[cnt] = min(id,val);
    }


}

int main(){
    std::cin >> n;
    int i,j,t1,t2;
    m[1000000000] = 1;
    M::iterator iter1,iter2;
    for (i=1;i<=n;i++){
        std::cin >> t1 >> t2;
        iter2 = m.lower_bound(t2);

        if( iter2 == m.begin()){
            std::cout << t1 << " " << iter2->second << "\n";
            set_m(t2, t1);
        }
        else if( iter2 == m.end()){
            std::cout << t1 << " " << (--iter2)->second << "\n";
            set_m(t2, t1);
        }
        else {
            int right = iter2->first - t2;
            int left  = t2 - (--iter2)->first;
            if( right < left)
                std::cout << t1 << " " << (++iter2)->second << "\n";
            else if( left < right)
                std::cout << t1 << " " << (iter2)->second << "\n";
            else {
                int a1 = iter2->second;
                int a2 = (++iter2)->second;
                std::cout << t1 << " " << min(a1,a2) << "\n";
            }
            set_m(t2, t1);
        }

    }
    return 0;
}
