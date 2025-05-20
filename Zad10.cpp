#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n, o, p, t, x, result{0};
    char sign;
    std::string input;
    std::cin >> n;

    for(int i = 0; i < n; i++){
        std::vector<int> prices(0);
        std::vector<int> taxes(0);
        std::cin >> o;
        for(int j = 0; j < o; j++){
            std::cin >> sign;            
            if(sign == 'a'){
                std::cin >> p >> t;
                taxes.resize(taxes.size() + 1, t);
                if(taxes.size() > 1){
                    for(int k = taxes.size() - 1;;){
                        if(taxes[k] < taxes[(k - 1) / 2]){
                            std::swap(taxes[k], taxes[(k - 1) / 2]);
                            k = (k - 1) / 2;
                        }else{
                            break;
                        }
                    }
                }
                prices.resize(prices.size() + 1, p);
                if(prices.size() > 1){
                    for(int k = prices.size() - 1;;){
                        if(prices[k] > prices[(k - 1) / 2]){
                            std::swap(prices[k], prices[(k - 1) / 2]);
                            k = (k - 1) / 2;
                        }else{
                            break;
                        }
                    }
                }        
            }else{
                std::cin >> x;
                if(!prices.empty()){
                    if(prices[0] + x >= 0){
                        prices[0] += x;
                    }
                    for(int k = 0; ((2 * k + 1) < prices.size() && prices[k] < prices[2 * k + 1]) || ((2 * k + 2) < prices.size() && prices[k] < prices[2 * k + 2]);){
                        if((2 * k + 1) < prices.size() && (2 * k + 2) < prices.size()){
                            if(prices[2 * k + 1] >= prices[2 * k + 2] && prices[k] < prices[2 * k + 1]){
                                std::swap(prices[k], prices[2 * k + 1]);
                                k = 2 * k + 1;
                            }else if(prices[2 * k + 1] < prices[2 * k + 2] && prices[k] < prices[2 * k + 2]){
                                std::swap(prices[k], prices[2 * k + 2]);
                                k = 2 * k + 2;
                            }
                        }else if((2 * k + 1) < prices.size() && (2 * k + 2) >= prices.size() && prices[k] < prices[2 * k + 1]){
                            std::swap(prices[k], prices[2 * k + 1]);
                            k = 2 * k + 1;
                        }else if((2 * k + 1) >= prices.size() && (2 * k + 2) < prices.size() && prices[k] < prices[2 * k + 2]){
                            std::swap(prices[k], prices[2 * k + 2]);
                            k = 2 * k + 2;
                        }
                    }
                }                 
            }
        }

        x = taxes.size();

        for(int j = 0; j < x; j++){
            result += prices[0] * taxes[0];
            prices[0] = prices[prices.size() - 1];
            prices.pop_back();
            taxes[0] = taxes[taxes.size() - 1];
            taxes.pop_back();
            for(int k = 0; ((2 * k + 1) < prices.size() && prices[k] < prices[2 * k + 1]) || ((2 * k + 2) < prices.size() && prices[k] < prices[2 * k + 2]);){
                if((2 * k + 1) < prices.size() && (2 * k + 2) < prices.size()){
                    if(prices[2 * k + 1] >= prices[2 * k + 2] && prices[k] < prices[2 * k + 1]){
                        std::swap(prices[k], prices[2 * k + 1]);
                        k = 2 * k + 1;
                    }else if(prices[2 * k + 1] < prices[2 * k + 2] && prices[k] < prices[2 * k + 2]){
                        std::swap(prices[k], prices[2 * k + 2]);
                        k = 2 * k + 2;
                    }
                }else if((2 * k + 1) < prices.size() && (2 * k + 2) >= prices.size() && prices[k] < prices[2 * k + 1]){
                    std::swap(prices[k], prices[2 * k + 1]);
                    k = 2 * k + 1;
                }else if((2 * k + 1) >= prices.size() && (2 * k + 2) < prices.size() && prices[k] < prices[2 * k + 2]){
                    std::swap(prices[k], prices[2 * k + 2]);
                    k = 2 * k + 2;
                }
            }

            for(int k = 0; ((2 * k + 1) < taxes.size() && taxes[k] > taxes[2 * k + 1]) || ((2 * k + 2) < taxes.size() && taxes[k] > taxes[2 * k + 2]);){
                if((2 * k + 1) < taxes.size() && (2 * k + 2) < taxes.size()){
                    if(taxes[2 * k + 1] <= taxes[2 * k + 2] && taxes[k] > taxes[2 * k + 1]){
                        std::swap(taxes[k], taxes[2 * k + 1]);
                        k = 2 * k + 1;
                    }else if(taxes[2 * k + 1] > taxes[2 * k + 2] && taxes[k] > taxes[2 * k + 2]){
                        std::swap(taxes[k], taxes[2 * k + 2]);
                        k = 2 * k + 2;
                    }
                }else if((2 * k + 1) < taxes.size() && (2 * k + 2) >= taxes.size() && taxes[k] > taxes[2 * k + 1]){
                    std::swap(prices[k], prices[2 * k + 1]);
                    k = 2 * k + 1;
                }else if((2 * k + 1) >= taxes.size() && (2 * k + 2) < taxes.size() && taxes[k] > taxes[2 * k + 2]){
                    std::swap(taxes[k], taxes[2 * k + 2]);
                    k = 2 * k + 2;
                }
            }
        }

        std::cout << result << "\n";
        result = 0;
    }

    return 0;
}