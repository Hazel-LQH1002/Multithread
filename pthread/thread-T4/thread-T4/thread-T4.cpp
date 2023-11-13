//mutex

#include <iostream>
#include <thread>
#include <mutex>


using namespace std;

void ThreadFn(mutex & mtx) {
    lock_guard<mutex> lock(mtx); //automatically lock and unlock
    cout << "I locked Mutex" << endl;
    this_thread::sleep_for(chrono::seconds(3));


}


int main()
{

    mutex mtx;
    thread th(ThreadFn, ref(mtx));
    this_thread::sleep_for(chrono::seconds(1));
    unique_lock<mutex> lock(mtx);//manually lock and unlock

    cout << "I am inside the Main.." << endl;
    lock.unlock();
    th.join();
    return 0;
}

