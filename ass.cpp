#include <iostream>
#include <pthread.h>
#include <vector>
// #include <thread>

std::vector<int> Number_Vector;//this stores all the values of fibonacchi number for the parent thread to print afterward


void* Fibonacchi_Create(void* tid){
    void *ab;
    int a=*((int*)tid)-1;
    std::cout<<"Inside the Child thread. Thread No-> "<<std::this_thread::get_id()<<std::endl;
    Number_Vector.push_back(0);
    Number_Vector.push_back(1);
    if(a==0 || a==1){
        return 0;
    }
    //Calculating the fibonacchi number for a>2
    int res = 0;
    for (int i=2;i<=a;i++){
        res = Number_Vector[i-1]+Number_Vector[i-2];
        Number_Vector.push_back(res);
    }

    std::cout<<"Leaving the child Thread"<<std::endl;
    return 0;
}

int main()
{
    std::cout <<"Initialized The Parent Thread. Thread No-> "<<std::this_thread::get_id()<<std::endl;//Inside the Parent Thread
    std::cout<<"Enter the fibonacchi number order you want to calculate: "<<std::endl;//Prompting the user to enter a number
    int n;
    std::cin>>n;
    pthread_t p;//initializing the child thread
    pthread_create(&p,NULL,&Fibonacchi_Create,&n);//creating the child thread
    pthread_join(p,NULL);//joining the child with the parent. this makes the parent wait till the child finish its process
    
    
    //Returned to the Parent thread
    std::cout<<"Back to the main Thread. Thread No-> "<<std::this_thread::get_id()<<std::endl;
    for (int j=0;j<n;j++){
        std::cout<<Number_Vector[j]<<std::endl;
    }
    pthread_exit(NULL);//terminating the child thread
    return 0;
}