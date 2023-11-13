#include <iostream>
#include <thread>
using namespace std;


void threadFn(int & value) {
	cout << "I am inside" << endl;
	cout << "Value => " << value++ << endl;
}
int main()
{
	int localvalue = 100;
	int value2 = 200;
	//lamda function

	//lamda 1
	//thread t1([](int & value){	
	//	cout << "I am inside" << endl;
	//    cout << "Value => " << value++ << endl; }, 
	//	ref(localvalue));


	//lamda 2
	//& refers to local value
	thread t1([&](){
		cout << "I am inside" << endl;
		cout << "Value => " << localvalue++ << endl; 
		value2++;
		});

	t1.join();
	cout << "Main Value: " << localvalue << endl;
	cout << "Main Value2: " << value2 << endl;
	return 0;
}