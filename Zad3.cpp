#include <iostream>

struct Customer{
    int p, r;
    long serviceTime{0};
    Customer* next{nullptr};
};

class Queue{
    public:
        long passedTime{0};
        Queue(){}

        void push(Customer customer){
            Customer *newNode = new Customer;
            newNode->p = customer.p;
            newNode->r = customer.r;
            newNode->serviceTime = customer.serviceTime;
            newNode->next = nullptr;
            if(empty()){    
                head = newNode;
                tail = newNode;
            }else{
                tail->next = newNode;
                tail = newNode;
            }
            size++;
            waitingTime += customer.serviceTime;
        }

        void pop(){
            if(empty()){
                return;
            }
            passedTime -= head->serviceTime;
            waitingTime -= head->serviceTime;
            if(head == tail){
                head = tail = nullptr;
                passedTime = 0;
            }else{
                head = head->next;
            }
            size--;
        }

        Customer front(){
            return *head;
        }

        bool empty(){
            return (head == nullptr) && (tail == nullptr);
        }

        long getSize(){
            return size;
        }

        long getWaitingTime(){
            if(empty()){
                return 0;
            }
            return waitingTime - passedTime;
        }
    private:
        Customer *head{nullptr};
        Customer *tail{nullptr};
        long size{0};
        long waitingTime{0};
};

struct Checkout{
    bool isOpen{false};
    Queue queue;
};

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int t, l, s, z, checkoutIndex, firstOpenCheckoutIndex;
    char action;
    Customer customer;
    std::cin >> t >> l >> s >> z;
    Checkout checkouts[l];
    firstOpenCheckoutIndex = l;

    while(t > 0){
        std::cin >> action;
        if(action == 'o'){
            std::cin >> checkoutIndex;
            checkouts[checkoutIndex].isOpen = true;
            if(checkoutIndex < firstOpenCheckoutIndex){
                firstOpenCheckoutIndex = checkoutIndex;
            }

        }else if(action == 'z'){
            std::cin >> checkoutIndex;
            checkouts[checkoutIndex].isOpen = false;
            checkouts[checkoutIndex].queue.pop();

            if(checkoutIndex == firstOpenCheckoutIndex){
                for(int i = 0; i < l; i++){
                    if(checkouts[i].isOpen){
                        firstOpenCheckoutIndex = i;
                        break;
                    }
                }
            }

            while(!(checkouts[checkoutIndex].queue.empty())){
                customer = checkouts[checkoutIndex].queue.front();
                checkouts[checkoutIndex].queue.pop();
                int tempIndex = firstOpenCheckoutIndex;

                for(int i = 0; i < l; i++){
                    if(checkouts[i].isOpen && (checkouts[i].queue.getWaitingTime() < checkouts[tempIndex].queue.getWaitingTime())){
                        tempIndex = i;
                    }
                }
                checkouts[tempIndex].queue.push(customer);
            }

        }else if(action == 'k'){
            std::cin >> customer.p >> customer.r;
            customer.serviceTime = customer.r * s + z;

            if(t < customer.p){
                for(int i = 0; i < l; i++){
                    if(checkouts[i].isOpen && !(checkouts[i].queue.empty())){
                        checkouts[i].queue.passedTime += t;
                        while(checkouts[i].queue.front().serviceTime <= checkouts[i].queue.passedTime){
                            checkouts[i].queue.pop();
                        }
                    }
                }
                break;
            }

            for(int i = 0; i < l; i++){
                if(checkouts[i].isOpen && !(checkouts[i].queue.empty())){
                    checkouts[i].queue.passedTime += customer.p;    
                }
            }

            for(int i = 0; i < l; i++){
                while(checkouts[i].isOpen && !(checkouts[i].queue.empty()) && (checkouts[i].queue.front().serviceTime <= checkouts[i].queue.passedTime)){
                    checkouts[i].queue.pop();
                }
            }

            checkoutIndex = firstOpenCheckoutIndex;
            for(int i = 0; i < l; i++){
                if((checkouts[i].isOpen) && (checkouts[i].queue.getWaitingTime() < checkouts[checkoutIndex].queue.getWaitingTime())){
                    checkoutIndex = i;
                }
            }
            checkouts[checkoutIndex].queue.push(customer);
            
            t -= customer.p;
        }
    }

    for(int i = 0; i < l; i++){
        if(i == l-1){
            if(checkouts[i].isOpen){
                std::cout << "K" << i << ": " << checkouts[i].queue.getSize() << "o " << checkouts[i].queue.getWaitingTime() << "s";
            }else{
                std::cout << "K" << i << ": z";
            }
        }else{
            if(checkouts[i].isOpen){
                std::cout << "K" << i << ": " << checkouts[i].queue.getSize() << "o " << checkouts[i].queue.getWaitingTime() << "s, ";
            }else{
                std::cout << "K" << i << ": z, ";
            }
        }
        
    }
    
    return 0;
}