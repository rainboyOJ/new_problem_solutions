#include <cstring>
#include <iostream>

int n;
char src[20][20];
char tmp[20][20];
char dst[20][20];

void clock_op(){
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            tmp[j][n-i+1] = src[i][j];
        }
    }
}

void p_t(){
    int i,j;
    std::cout << "=====================\n";
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            std::cout << (char)(tmp[i][j]) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "=====================\n";
}

void anti_clock_op_op(){
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            tmp[n-j+1][i] = src[i][j];
        }
    }
}

void trans(){
    anti_clock_op_op();
    //p_t();
    memcpy(src,tmp,sizeof(tmp));
    anti_clock_op_op();
    //p_t();
}

bool cmp(){
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            if( tmp[i][j] != dst[i][j])
                return 0;
        }
    }
    return 1;
}

void init(){
    std::cin >> n;
    char t[20];
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            std::cin >> t;
            src[i][j] = t[0];
        }
    }
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            std::cin >> t;
            dst[i][j] = t[0];
        }
    }
}
int main(){
    init();
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            tmp[i][j] = src[i][j];
        }
    }
    if( cmp() ){
        std::cout << "4";
        return 0;
    }


    clock_op();
    if( cmp() ){
        std::cout << "1";
        return 0;
    }

    anti_clock_op_op();
    if( cmp() ){
        std::cout << "2";
        return 0;
    }

    trans();
    if( cmp() ){
        std::cout << "3";
        return 0;
    }
    std::cout << "5";
    return 0;
}
