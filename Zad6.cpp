#include<iostream>

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int t, startElement, currentElement, previousElement, min, max;
    unsigned int leastJumpRange{1}, widestJumpRange{1}, currentJumpRange{1}, cyclesCounter{0};
    std::cin >> t;

    for(int i = 0; i < t; i++){
        currentElement = time_jump(0);
        min = currentElement;
        max = currentElement;
        startElement = currentElement;
        previousElement = currentElement;
        currentElement = time_jump(currentJumpRange);
        while(true){
            if(currentElement == previousElement){
                break;
            }
            if(currentElement < min){
                min = currentElement;
            }else if(currentElement > max){
                max = currentElement;
            }

            if((currentElement >= startElement && previousElement < startElement) || (currentElement >= startElement && currentElement <= previousElement)){
                cyclesCounter++;
            }

            if(((currentElement > startElement) || (currentElement < startElement && previousElement >= startElement) || (currentElement < startElement && previousElement < currentElement))  && cyclesCounter < 1){
                currentJumpRange *= 2;
                previousElement = currentElement; 
                currentElement = time_jump(currentJumpRange);
            }else{
                leastJumpRange = currentJumpRange;
                widestJumpRange = currentJumpRange * 2;
                currentJumpRange = (leastJumpRange + widestJumpRange) / 2;
                startElement = currentElement;
                previousElement = time_jump(currentJumpRange);
                currentElement = time_jump(currentJumpRange);
                break;
            } 
        }    
        
        while(currentElement != previousElement){
            if(currentElement < min){
                min = currentElement;
            }else if(currentElement > max){
                max = currentElement;
            }else if(previousElement < min){
                min = previousElement;
            }else if(previousElement > max){
                max = previousElement;
            }

            if(previousElement == min){
                startElement = previousElement;
            }else{
                if((currentElement > previousElement && previousElement >= startElement) || (currentElement <= startElement && previousElement > startElement) || (currentElement > previousElement && startElement > currentElement)){
                    startElement = currentElement;
                    widestJumpRange = currentJumpRange;
                }else{
                    startElement = currentElement;
                    leastJumpRange = currentJumpRange;
                }
                currentJumpRange = (leastJumpRange + widestJumpRange) / 2;
            }
            previousElement = time_jump(currentJumpRange);
            currentElement = time_jump(currentJumpRange);
        }

        std::cout << currentJumpRange << " ";
        cyclesCounter = 0;
        currentJumpRange = 1;
        leastJumpRange = 0;
        widestJumpRange = 0;
        
        next_test();
    }

    return 0;
}