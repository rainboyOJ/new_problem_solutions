#include <iostream>


int main(){
    int h,w,flag;
    char c;
    std::cin >> h >> w;
    std::cin >> std::noskipws >> c;
    std::cin >> std::noskipws >> c;
    std::cin >> flag;
    int i,j,k;

    // line 1
    for (i=1;i<=w;i++){
        std::cout << (char)(c);
    }
    std::cout << "\n";


    for (i=1;i<=h-2;i++){
        std::cout << (char)(c);
        for (j=1;j<=w-2;j++){
            if(flag)
                std::cout << (char)(c);
            else 
                std::cout << " ";
        }
        std::cout << (char)(c) << "\n";
    }




    // line last
    for (i=1;i<=w;i++){
        std::cout << (char)(c);
    }
    return 0;
}
