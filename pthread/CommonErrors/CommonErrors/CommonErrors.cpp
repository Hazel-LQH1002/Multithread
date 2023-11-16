// CommonErrors.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <memory>
using namespace std;


////error 1: use ref(), not to use 1 directly
//
//void foo(int& x) {
//    x += 1;
//}
//
//int main()
//{
//    //wrong:
//    //thread t1(foo, ref(a));
//
//    //correct:
//    int a = 1;
//    thread t1(foo, ref(a));
//
//    t1.join();
//    cout << a << endl;
//    return 0;
//}








//error 2: use ref(), not to use 1 directly


//wrong: a is temporary in test(), so when foo is running, foo does not know the value of a
//thread t;
//
//
//void foo(int& x) {
//    x += 1;
//}
//
//void test() {
//    int a = 1;
//    t = thread(foo, ref(a));
//}
//
//int main()
//{
//    test();
//    t.join();
//    return 0;
//}

//correct: make a as a global variable so foo can obtain its value at anytime
//thread t;
//int a = 1;
//
//void foo(int& x) {
//    x += 1;
//}
//
//void test() {
//    t = thread(foo, ref(a));
//}
//
//int main()
//{
//    test();
//    t.join();
//    cout << a << endl;
//    return 0;
//}








//error 3: refer to something already gone


//wrong: delete pt before t tries to get the value
//thread t;
//int a = 1;
//
//void foo(int* x) {
//    *x += 1;
//    cout << *x << endl;
//}
//
//int main()
//{
//    int* pt = new int(1);
//    thread t(foo, pt);
//    delete pt;  //release the pt address so when foo tries to get the value of this address, the value already gone
//    t.join();
//    return 0;
//}

//correct:
//thread t;
//int a = 1;
//
//void foo(int* x) {
//    *x += 1;
//    cout << *x << endl;
//}
//
//int main()
//{
//    int* pt = new int(1);
//    thread t(foo, pt);
//    t.join();
//    return 0;
//}







//error 4

//wrong: the code is correct actually but do not know when to release a, since it might interfere with thread t
//class A {
//public:
//	void foo() {
//		cout << "Hello" << endl;
//	}
//};
//
//int main() {
//	A a;
//	thread t (&A::foo, a);
//
//	t.join();
//}


//correct:
//class A {
//public:
//	void foo() {
//		cout << "Hello" << endl;
//	}
//};
//
//int main() {
//	shared_ptr<A> a = make_shared<A>();  // the shared ptr can be released automatically as long as it wont be used anymore
//										 // this avoids manually release and cause error
//	thread t(&A::foo, a);
//	t.join();
//}







//error 5
//wrong: foo is private, cannot access it in main
//class A {
//private:
//	void foo() {
//		cout << "Hello" << endl;
//	}
//};
//
//int main() {
//	shared_ptr<A> a = make_shared<A>();  // the shared ptr can be released automatically as long as it wont be used anymore
//										 // this avoids manually release and cause error
//	thread t(&A::foo, a);
//	t.join();
//}


//correct:
class A {
private:
	friend void thread_foo(); //allow thread_foo() to access foo()
	void foo() {
		cout << "Hello" << endl;
	}
};


void thread_foo() {
	shared_ptr<A> a = make_shared<A>();  
	thread t(&A::foo, a);
	t.join();
}


int main() {
	thread_foo();
}

