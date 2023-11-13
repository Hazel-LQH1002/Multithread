#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <condition_variable>//use along with mutex

using namespace std;

//5.1 let ThrdFn wait for var to turn to false then it can stop
//bool var = true;
//
//void ThrdFn(mutex& mtx) {
//    unique_lock<mutex> lock(mtx);
//    while (var) {
//
//    }
//    cout << "End of thread.." << endl;
//}
//int main()
//{
//    mutex mtx;
//    thread th(ThrdFn, ref(mtx));
//    this_thread::sleep_for(chrono::seconds(12));
//    var = false;
//    th.join();
//    cout << "End of Code.." << endl;    
//}


//5.2 take less CPU, wiser way to wake up and stop the thread compared with 5.1


void ThrdFn(mutex& mtx, condition_variable & convar ) {
    unique_lock<mutex> lock(mtx);
    cout << "1 Thread.." << endl;
    convar.wait(lock);//block current thread, wait until notify
    cout << "End of thread.. 4" << endl;
}

int main()
{
    mutex mtx;
    condition_variable convar;
    thread th(ThrdFn, ref(mtx), ref(convar));
    this_thread::sleep_for(chrono::seconds(5)); 
    {
        lock_guard<mutex> lg(mtx);
        convar.notify_all();//wake up all threads, correspondence to .wait() func in ThrdFn, stop wait
        cout << "Now in main stuck 2" << endl;
        this_thread::sleep_for(chrono::seconds(5));
        cout << "Now in main stuck 3" << endl;
    }
    
    th.join();
    this_thread::sleep_for(chrono::seconds(1));
    cout << "End of Code.. 5" << endl;
}

