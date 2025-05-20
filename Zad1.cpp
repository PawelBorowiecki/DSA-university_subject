#include <iostream>
#include <vector>

struct Worker{
    long C, K, daysWithPositiveResult;    
};

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    unsigned short t, n;
    unsigned int d, m, days, dayCounter{0};
    long result{0};
    std::cin >> t;

    for(size_t i = 0; i < t; i++){            
        std::cin >> n >> d >> m;
        std::vector<Worker> employees(n);

        for(size_t j = 0; j < n; j++){
            std::cin >> employees[j].C >> employees[j].K;
            if(employees[j].C % employees[j].K == 0){
                employees[j].daysWithPositiveResult = employees[j].C / employees[j].K;
            }else{
                employees[j].daysWithPositiveResult = employees[j].C / employees[j].K + 1;
            }
        }

        for(size_t j = 0; j < d; j++){
            std::cin >> days;
            for(size_t k = 0; k < n; k++){
                if(days >= employees[k].daysWithPositiveResult){
                    result += (2*employees[k].C - employees[k].K*(employees[k].daysWithPositiveResult-1)) * employees[k].daysWithPositiveResult / 2;
                }else{
                    result += (2*employees[k].C - employees[k].K*(days-1)) * days / 2;
                }
            }

            if(result >= m){
                dayCounter++;
            }

            std::cout << result << "\n";
            result = 0;
        }
            
        std::cout << dayCounter << "\n";
        dayCounter = 0;
    }

    return 0;
}