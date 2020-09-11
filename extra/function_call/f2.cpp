#include <iostream>
using namespace std;

double vals[] = {10.1, 12.6, 33.1, 24.1, 50.0};

double &setValues(int i)
{
    static double x = i;
    double &y = x; // return a reference to the ith element
    return y;
    //vals[i] = *(vals+i)
}

void fun3()
{

    cout << "Value before change" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "vals[" << i << "] = ";
        cout << vals[i] << endl;
    }

    setValues(1) = 20.23; // change 2nd element
    setValues(3) = 70.8;  // change 4th element

    //also does the same as above two lines:
    *(vals + 1) = 20.23; // change 2nd element
    *(vals + 3) = 70.8;  // change 4th elementI

    cout << "Value after change" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "vals[" << i << "] = ";
        cout << vals[i] << endl;
    }
}

void fun2()
{
    int arr[5] = {1, 2, 4, 5, 6};
    int(&val)[5] = arr; //refernces to an array can be used a pointer, but have to follow the rules of references.
    cout << val + 1 << endl;
    cout << *(val + 2) << endl;
    cout << val[2] << endl;


    int i;
    double d;

    // declare reference variables
    int &r = i;
    double &s = d;

    i = 5;
    cout << "Value of i : " << i << endl;
    cout << "Value of i reference : " << r << endl; //*r is not allowed, but reference of an array can be deferenced using * operator

    d = 11.7;
    cout << "Value of d : " << d << endl;
    cout << "Value of d reference : " << s << endl;

    // cout << "addr of i : " << &i << endl;
    // cout << "addr of i reference : " << &r << endl; //*r is not allowed, but reference of an array can be deferenced using * operator

    // cout << "addr of d : " << &d << endl;
    // cout << "addr of d reference : " << &s << endl;
}

int main()
{
    // fun2();
    fun3();
}