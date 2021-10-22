// Transfering_Ownership_of_Thread.cpp : 
// 
// 
//

#include <iostream>
#include<thread>
#include<chrono>


void foo()
{
    printf("foo ");
}

void bar()
{
    printf("bar \n");
}

int main()
{
    std::thread thread_1(foo);

    // the below line of code generates an error
    //std::thread thread_2 = thread_1;

    /*
    E1776	
    function "std::thread::thread(const std::thread &)" 
    (declared at line 110 of "C:\Program Files (x86)\Microsoft Visual Studio\2019
    \Community\VC\Tools\MSVC\14.29.30133\include\thread") 
    cannot be referenced -- it is a deleted function	
    
        thread object are not copy constructors nor are they copy asignable.
    
    */

    std::thread thread_2 = std::move(thread_1);
    // This code explicitly moves one thread to another 
    // thread variable, this avoids the last compile time error,
    // and transfers ownership of a thread which is owned by 
    // thread_1 to take to thread_2 variable
    // 
    // the owner of the thread objectis responsible for managing the 
    // thread objects lifecycle.  after above move call, thread_1 variable
    // does not own any thread object now. 
    //



    // new oibject to thread_1
    thread_1 = std::thread(bar);


    //last time we got an error when we tried to copy one thread to another
    //but theres no error, we have temporary object, not named variable
    //in previous case. Implicit move call happens, so we do not need to explicitly 
    //use std::move(), at the time we perform this, thread_1 didinot own an object.


    //lets try transfering ownership of a thread to another thread variable while it's owning another thread

    //std::thread thread_3(foo);
    //thread_1 = std::move(thread_3);
    //
    //this can't happen because the owner of a thread

    thread_1.join();
    thread_2.join();


}

