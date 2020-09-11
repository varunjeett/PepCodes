#include <iostream>
using namespace std;

//all are pass by refernce
void f1(int (&b)[5]) //bound is important here
{
    b[0] = 1;
    b[4] = 100;
}

void f2(int b[]) //bound not important here
{
    cout << *b << endl; //(  (*b+i)=b[i], ((b+i)=&b[i]) , both are diittooo same
    b[1] = 2;
}

void f3(int *ptr)
{
    *(ptr + 2) = 12121212;
}

int main()
{
    int *arr = new int[3]{1, 2, 44};
    cout << *(arr + 1) << endl;
    arr = new int[5]{112, 44444, 5, 5, 5};
    cout << *(arr + 1) << endl;

    int a[5] = {1111, -1, -1, -1, -1}
    //a={1001,100,100,100}; reinittalization not allowed;

    int *ptr = a;
    ptr = nullptr; //allowed for pointer

    // int (&ref)[5]=a;
    // //reference to an array , caanot be set to null, or re initialized
    // // int abc[5] = {-1, -1, -1, -1, -1};
    // // (&ref)[5]=a;  //re-initialization is not allowed for references, initialized at declration

    // ref[2]=12121212;
    // cout<<*(ref+2)<<endl; //refernces can follow the syntax of a pointer;
    // // ref=nullptr   not allowed for refernces

    // f1(a);
    // f2(a);
    // f3(a);
    // cout << a[0] << endl;
    // cout << a[1] << endl;
    // cout << a[2] << endl;
    // cout << a[3] << endl;
    // cout << a[4] << endl;
}

 