#include <iostream>

int n;
char name[10];
float w;
int k;

void init(){
    std::cin >> n;
}

bool jia_liu(float w,bool ke_sou){
    if ( w >= 37.5 && ke_sou){
        return true;
    }
    return false;
}
int main(){
    init();
    int i,cnt = 0;
    for (i=1;i<=n;i++){
        std::cin >> name;
        std::cin >> w;
        std::cin >> k;
        if( jia_liu(w,k)){
            std::cout << name << "\n";
            cnt++;
        }
    }
    std::cout << cnt << "\n";
    return 0;
}
