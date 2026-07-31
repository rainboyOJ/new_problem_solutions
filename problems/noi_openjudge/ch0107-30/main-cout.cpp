#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;



char s1[1000];
char s2[1000];
char tmp[1000];
int main(){
    std::cin >> s1+1;
    std::cin >> s2+1;
    int l1  = strlen(s1+1);
    int l2  = strlen(s2+1);
    int i,j;
    for (i=1;i<l1;i++){
        s1[l1+i] = s1[i];
    }
    for (i=1;i<l2;i++){
        s2[l2+i] = s2[i];
    }

    if(l1 < l2){
        swap(s1,s2);
        swap(l1,l2);
    }

    for(i=l2;i>=1;i--){
        for(j=1;j<=l2+l2-i;j++){
            memset(tmp,0,sizeof(tmp));
            strncpy(tmp,s2+j,i);
            //std::cout << i << " " << tmp << "\n";
            if( strstr(s1+1,tmp)!=NULL){
                //std::cout << s2+j;
                std::cout << i;
                return 0;
            }
        }
    }
    std::cout << "0";
    return 0;
}
