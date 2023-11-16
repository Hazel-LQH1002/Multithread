// Basic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <string>

using namespace std;

void printHello(string st) {
    cout << st << endl;
}
int main()
{
    thread t1(printHello, "Hello");

    bool isJoin = t1.joinable();  //check whether t1 can call join()
    if (isJoin) {
        t1.join();
    }


   // t1.join();  //main thread wait for the end of thread
   // 
   // 
   // 
   // t1.detach();  //main thread does not wait for the end of thread, main ends first and t1 will keep running

    return 0;
}

