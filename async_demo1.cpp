#include<iostream>
#include<future>
// three task
// ways of completing it
// 1. sequencially one by one->single thread
// 2. start all tasks simultaneously and keep jugling them based on some criteria->multi threading
// 3. map tasks amongst different workers->parallel execution
// 4. start task and delegate it. then take follow up and wait till completion->asynchornous execution

int square(std::future<int>&ft){
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout<<"\nHello from square\n";
    int number=ft.get();
    return number*number;
}

int factorial(int number){
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    if(number<0)
        throw std::runtime_error("\nNegative numer!!!!");
    if(number==0||number==1)
        return 1;
    return number* factorial(number-1);
}

int main()
{
    // make promise to compiler that i will give value/parameter later
    std::promise<int>pr;

    // a future linked to the promise
    std::future<int> ft=pr.get_future();

    //lauch square if possible as new thread
    std::future<int>result = std::async(std::launch::async,&square,std::ref(ft));
    std::cout<<factorial(7);
    int val=0;
    std::cout<<"Enter value: ";
    std::cin>>val;
    pr.set_value(val);
    std::cout<<"\nResult of square: "<<result.get();

}