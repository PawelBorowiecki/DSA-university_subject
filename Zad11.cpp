#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int partition(std::vector<int>& array, int left, int right) {
    int index = left;

    for (int j = left; j <= right - 1; j++) {
        if(array[j] <= array[right]) {
            std::swap(array[index], array[j]);
            index++;
        }
    }
    std::swap(array[index], array[right]);
    return index;
}

int selectElement(std::vector<int>& array, int left, int right, int k){
    
    int index = partition(array, left, right);
    
    if (index - left == k - 1) {
        return array[index];
    }
   
     if (index - left > k - 1) {
        return selectElement(array, left, index - 1, k);
    }

    return selectElement(array, index + 1, right, k - index + left - 1);
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int t, n, k, c, isFirstIteration{0}, square, day, tempDay, resultDay, primeFactorsQuantity{0};
    std::vector<bool> sieve(1000001, false);
    std::vector<int> primeNumbers(0);
    sieve[2] = sieve[3] = true;
    for (int i = 1; i * i < 1000001; i++) {
		for (int j = 1; j * j <= 1000001; j++) {
			c = (4 * i * i) + (j * j);
			if (c < 1000001 && (c % 12 == 1 || c % 12 == 5)){
                sieve[c] = sieve[c] ^ true;
            }	

			c = (3 * i * i) + (j * j);
			if (c < 1000001 && c % 12 == 7){
                sieve[c] = sieve[c] ^ true;
            }	

			c = (3 * i * i) - (j * j);
			if (i > j && c < 1000001 && c % 12 == 11){
                sieve[c] = sieve[c] ^ true;
            }	
		}
	}

    for(int i = 5; i * i < 1000001; i++){
        if(sieve[i]){
            for(int j = i * i; j < 1000001; j += i * i){
                sieve[j] = false;
            }
        }
    }

    for(int i = 0; i < sieve.size(); i++){
        if(sieve[i]){
            primeNumbers.resize(primeNumbers.size() + 1, i);
        }
    }

    std::cin >> t;

    for(int i = 0; i < t; i++){
        std::cin >> n;
        std::vector<int> daysWithEvenQuantityOfPrimeFactors(0);        
        for(int j = 0; j < n; j++){
            std::cin >> day;
            tempDay = day;
            square = std::sqrt(day);

            for(int w = 0; primeNumbers[w] <= square;){
                if(tempDay % primeNumbers[w] == 0){
                    if(isFirstIteration == 0){
                        primeFactorsQuantity++;
                        isFirstIteration++;
                    }
                    tempDay /= primeNumbers[w];
                }else{
                    isFirstIteration = 0;
                    w++;
                } 
            }

            if(tempDay > 1){
                primeFactorsQuantity++;
            }

            if(primeFactorsQuantity % 2 == 0){
                daysWithEvenQuantityOfPrimeFactors.resize(daysWithEvenQuantityOfPrimeFactors.size() + 1, day);
            }
            primeFactorsQuantity = 0;
        }
        std::cin >> k;

        if(k >= daysWithEvenQuantityOfPrimeFactors.size()){
            std::cout << "BRAK DANYCH\n";
        }else{
            resultDay = selectElement(daysWithEvenQuantityOfPrimeFactors, 0, daysWithEvenQuantityOfPrimeFactors.size() - 1, k+1);
            std::cout << resultDay << "\n";
        }
    }

    return 0;
}