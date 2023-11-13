// thread-T2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <initializer_list>
#include <vector>
using namespace std;


//2.1  get id
//
//void threadFn() {
//
//     cout << "I am inside a thread function" << endl;
//     cout << "Thread ID: " << this_thread::get_id() << endl;
//
//}
//
//int main()
//{
//    //thread t1(threadFn);
//
//    thread t1{ threadFn};
//    this_thread::sleep_for(chrono::milliseconds(1000));
//    thread t2{ threadFn};
//
//    cout << "Main branch ID: " << this_thread::get_id() << endl;
//
//    t1.join();
//    t2.join();
//    return 0;
//}



// 2.2
// 
//template<typename Type>
//void threadFn() {
//
//    cout << "Type is => " << typeid(Type).name() << endl;
//}

//int main()
//{
//    //thread t1(threadFn);
//
//    thread t1{ threadFn<int> };
//    this_thread::sleep_for(chrono::milliseconds(1000));
//    thread t2{ threadFn<float> };
//
//    cout << "Main branch ID: " << this_thread::get_id() << endl;
//
//    t1.join();
//    t2.join();
//    return 0;
//}



//2.3 initializer list
 
//void threadFn(initializer_list<int> il) {
//
//    cout << "size of list = >" << il.size() << endl;
// }
//
//int main()
//{
//    initializer_list<int> il = { 1,2,3,4,5,6 };
//
//    thread t1{ threadFn, il };
//
//    t1.join();
//
//    return 0;
//}

//2.4 vector
void threadFn(vector<int> il) {

    cout << "size of list = >" << il.size() << endl;
}

int main()
{
    vector<int> il = { 1,2,3,4,5,6 };

    thread t1{ threadFn, il };

    t1.join();

    return 0;
}

