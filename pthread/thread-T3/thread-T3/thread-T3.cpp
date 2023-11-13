#include <iostream>
#include <thread>
#include <future>


using namespace std;




//3.1

//void asyncFunc() {
//    cout << "Async Thread => " << this_thread::get_id() << endl;
//    cout << "I am inside a async..." << endl;
//}

//void threadFn() {
//    cout << "I am inside thread" << endl;
//}
//
//
//int main()
//{
//    cout << "Main Thread => " << this_thread::get_id() << endl;
//    future<void> fn = async(launch::async, asyncFunc);
//
//    fn.get();//wait until asyncFunc finish
//    return 0;
//
//}


//3.2 defer

//void threadFn() {
//    cout << "I am inside thread" << endl;
//}
//
//
//int main()
//{
//    cout << "Main Thread => " << this_thread::get_id() << endl;
//    future<void> fn = async(launch::deferred, asyncFunc);
//
//    fn.get();//not until when get() is called, asynFunc will run
//    return 0;
//
//}


//3.3 add a parameter
//int asyncFunc(int value) {
//    cout << "Async Thread => " << this_thread::get_id() << endl;
//    cout << "I am inside a async..." << endl;
//    return 100+value;
//}
//
//
//int main()
//{
//    cout << "Main Thread => " << this_thread::get_id() << endl;
//    future<int> fn = async(launch::async, asyncFunc, 200);
//
//    //fn.get() cannot be called twice thus the second time will get Invalid
//    if(fn.valid())  cout << fn.get() << endl;//not until when get() is called, asynFunc will run
//    if (fn.valid()) fn.get();
//    else cout << "Invalid" << endl;
//    
//
//    return 0;
//
//}


//3.4 Promise:container of future

//int main()
//{
//	promise<int> mypromise;
//	future<int> fut = mypromise.get_future();
//	
//	mypromise.set_value(100);
//	cout << fut.get() << endl;
//
//	return 0;
//
//}


//3.4 Promise, pthread
//

//compare reverse the order of a and b
//indicates do not need to wait ThrdFunc finishes, future can still get value in main thread
void ThrdFunc(promise<int> & prom) {
	prom.set_value(200); //a
	this_thread::sleep_for(chrono::seconds(2)); //b
}

int main()
{
	promise<int> mypromise;
	future<int> fut = mypromise.get_future();
	cout << "Main..." << endl;
	thread t1{ ThrdFunc, ref(mypromise) };
	cout << "Main Thread => " << fut.get() << endl;

	t1.join();
	return 0;

}

