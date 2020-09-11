#include <iostream>

using namespace std;

void printIncreasing(int a, int b)
{
    if (a == b + 1)
    {
        return;
    }
    cout << a << " ";    
    printIncreasing(a + 1, b);
}

void printDecreasing(int a, int b)
{

    if (a == b + 1)
    {
        return;
    }
    printDecreasing(a + 1, b);
    cout << a << " ";
}

void printEvenOdd(int a, int b)
{
    if (a == b + 1)
    {
        return;
    }

    if (a % 2 == 0)
    {
        cout << a << " "; //pre area(upar jate hue)
    }

    printEvenOdd(a + 1, b);

    if (a % 2 != 0)
    {
        cout << a << " "; //post area(neeche aate)
    }
}

int printPower(int a, int b)
{
    if (b == 0)
    {
        return 1;
    }
    int smallAns = printPower(a, b - 1);
    return smallAns * a;
}

void set1()
{

    int a, b;
    cin >> a;
    cin >> b;

    printIncreasing(a, b);

    printDecreasing(a, b);

    printEvenOdd(a, b);

    int res = printPower(a, b);
}

void solve()
{
    set1();
}

int main()
{
    solve();
    return 0;
}