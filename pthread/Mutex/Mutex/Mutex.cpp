// Mutex.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

//Basic use of mutex
//int a = 0;
//mutex mtx;
//void func() {
//    for (int i = 0; i < 1000; i++) {
//        mtx.lock();
//        a += 1;
//        mtx.unlock();
//    }
//}
//int main()
//{
//    thread t1(func);
//    thread t2(func);
//
//    t1.join();
//    t2.join();
//
//    cout << a << endl;
//    return 0;
//
//}



///Example of Deadlock, avoid this
//M1 wait for M2, M2 wait for M1

//int a = 0;
//mutex m1, m2;
//
//
//void func1() {
//    for (int i = 0; i < 50; i++) {
//        m1.lock();
//        m2.lock();
//        m1.unlock();
//        m2.unlock();
//    }
//
//}
//
//void func2() {
//
//    for (int i = 0; i < 50; i++) {
//        m2.lock();
//        m1.lock();
//        m1.unlock();
//        m2.unlock();
//    }
//}
//
//int main()
//{
//    thread t1(func1);
//    thread t2(func2);
//
//    t1.join();
//    t2.join();
//
//    cout << "over" << endl;
//    return 0;
//
//}


//can change to this:

//int a = 0;
//mutex m1, m2;
//
//
//void func1() {
//    for (int i = 0; i < 50; i++) {
//        m1.lock();
//        m2.lock();
//        m1.unlock();
//        m2.unlock();
//    }
//
//}
//
//void func2() {
//
//    for (int i = 0; i < 50; i++) {
//        m1.lock();
//        m2.lock();
//        m1.unlock();
//        m2.unlock();
//    }
//}
//
//int main()
//{
//    thread t1(func1);
//    thread t2(func2);
//
//    t1.join();
//    t2.join();
//
//    cout << "over" << endl;
//    return 0;
//
//}




//lock guard:can lock and unlock automatically, once the function finished, it will unlock automatically

//int shared_data = 0;
//mutex mtx;
//
//
//void func() {
//
//    for (int i = 0; i < 50; i++) {
//        lock_guard<mutex> lg(mtx);
//        shared_data++;
//        
//    }
//
//}
//
//
//int main()
//{
//    thread t1(func);
//    thread t2(func);
//
//    t1.join();
//    t2.join();
//
//    cout << shared_data << endl;
//    return 0;
//
//}


//unique lock:same as lock guard, can lock and unlock automatically

//int shared_data = 0;
//mutex mtx;
//
//
//void func() {
//
//    for (int i = 0; i < 50; i++) {
//        unique_lock<mutex> lg(mtx);
//        shared_data++;
//
//    }
//
//}
//
//
//int main()
//{
//    thread t1(func);
//    thread t2(func);
//
//    t1.join();
//    t2.join();
//
//    cout << shared_data << endl;
//    return 0;
//
//}



//try_lock_for: also unique lock but can set to force to unlock after a certain period, do not need to wait to get the ownership of the mutex
int shared_data = 0;
timed_mutex mtx;


void func() {

    for (int i = 0; i < 3; i++) {
        unique_lock<timed_mutex> lg(mtx, defer_lock);
        if (lg.try_lock_for(chrono::seconds(2))) { //try lock for means it will wait 2 sec, if after 2 sec the thread still does not get the access, then return false and do not add lock
            this_thread::sleep_for(chrono::seconds(1));
            shared_data++;
        }

    }

}


int main()
{
    thread t1(func);
    thread t2(func);

    t1.join();
    t2.join();

    cout << shared_data << endl;
    return 0;

}

