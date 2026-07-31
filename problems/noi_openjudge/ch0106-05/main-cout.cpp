#include <iomanip>
#include <iostream>
int n;
int age[205]={0};
int main(){
    int i,t;
    std::cin >> n;
    for (i=1;i<=n;i++){
        std::cin >> t;
        age[t]++;
    }
    int a,b,sum;
    a = 0,b=18,sum=0;
    for(i=a;i<=b;i++){
        sum += age[i];
    }
    std::cout << std::setw(0) << std::fixed << std::setprecision(2) << sum*1.0 / n * 100 << "%\n";
    a = 19,b=35,sum=0;
    for(i=a;i<=b;i++){
        sum += age[i];
    }
    std::cout << std::setw(0) << std::fixed << std::setprecision(2) << sum*1.0 / n * 100 << "%\n";
    a = 36,b=60,sum=0;
    for(i=a;i<=b;i++){
        sum += age[i];
    }
    std::cout << std::setw(0) << std::fixed << std::setprecision(2) << sum*1.0 / n * 100 << "%\n";
    a = 61,b=200,sum=0;
    for(i=a;i<=b;i++){
        sum += age[i];
    }
    std::cout << std::setw(0) << std::fixed << std::setprecision(2) << sum*1.0 / n * 100 << "%\n";
    return 0;
}
