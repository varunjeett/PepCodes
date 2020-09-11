#include <iostream>
#include <vector>
#include <stack>

using namespace std;

//here the x and y are newly created on the stack and copy the values from the function call
void foo_1(int x, int y) // call by value , we have to pass the value from function call
{
    cout << &x << "," << &y << endl;
    cout << x << "," << y << endl; //changes done here are not reflected
    x = 111;
    y = 222;
    return;
}

void foo_2(int *x, int *y) //call by reference, it expect the address of variable from the calling function
{
    cout << &x << "," << &y << endl; //pointer ka address
    cout << x << "," << y << endl;   //content of the pointer (it will print the address received)

    //changing the values at the address, hence changes will be reflected down
    *x = 111;
    *y = 222;

    return;
}

//here the x and y are not again created on the stack instead they are reference to the variable on the function call
void foo_3(int &x, int &y) //by ampersand(reference)
{
    cout << &x << "," << &y << endl;
    cout << x << "," << y << endl;
    x = 111;
    y = 222;
    return;
}

void foo_()
{
    int a = 100;
    int b = 200;

    cout << "Before swap, value of a :" << a << endl;
    cout << "Before swap, value of b :" << b << endl;

    cout << &a << "," << &b << endl;

    // calling a function to swap the values.
    foo_1(a, b);
    // foo_2(&a, &b); //address pass kia
    //foo_3(a, b);

    cout << &a << "," << &b << endl;

    cout << "After swap, value of a :" << a << endl;
    cout << "After swap, value of b :" << b << endl;
}

//it is passing by reference
void func1(int *val) //neeche vala address se uthake vo alag array bnaega
{
    cout << val << endl
         << endl; //val pointer ka address hai.

    for (int i = 0; i < 5; i++)
    {
        cout << (val + i) << endl;
        *(val + i) = -(*(val + i)); //since we have passed the address , changes are reflected down
        cout << *(val + i) << endl;
    }

    return;
}

//it is passing by reference
void func2(int val[]) //neeche vala address se uthake vo alag array bnaega
{
    cout << val << endl
         << endl; //val pointer ka address hai.

    for (int i = 0; i < 5; i++)
    {
        cout << (val + i) << endl;
        val[i] = -val[i]; //since we have passed the address , changes are reflected down
        cout << val[i] << endl;
    }

    return;
}

void func3(int (&val)[5])
{
    cout << val << endl << endl; //val pointer ka address hai.

    for (int i = 0; i < 5; i++)
    {
        cout << &val[i] << endl;
        val[i] = -val[i]; //since we have passed the address , changes are reflected down
        cout << val[i] << endl;
    }
    return ;
}

int main()
{
    foo_();

    //for vector
    // int arr[] = {11, 24, 4, 4, 5};
    // int *ptr = arr;
    // int (&ref)[5]=arr;  //ref is a pointer nothing else; which can also be used array like:

    // cout<<*(ref+0)<<","<<ref[1]<<","<<ref[2]<<","<<ref[3]<<","<<ref[4]<<endl;
    // cout<<ptr[0]<<","<<ptr[1]<<","<<ptr[2]<<","<<ptr[3]<<","<<ptr[4]<<endl;

    // cout<<endl;
    // cout << ptr << endl;
    // cout << ptr + 1 << endl;
    // cout << ptr + 2 << endl;
    // cout << ptr + 3 << endl;
    // cout << ptr + 4 << endl
    //      << endl;

    // func3(arr);

    // for (int i = 0; i < 5; i++)
    // {
    //     cout << &arr[i] << endl;
    //     cout << arr[i] << endl;
    // }
}
