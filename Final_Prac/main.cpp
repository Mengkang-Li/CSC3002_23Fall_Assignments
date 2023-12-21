#include <iostream>
#include <string>
using namespace std;

void strPrac(){
    string str1 = "Hello,world";
    string str2 = str1 + " " + string("world");
    cout << str1 << endl;
    cout << str2 << endl;
}

void ptePrac(){
    int m = 2;
    cout << (*&m) << endl;
    int *pm = &m;
    int *pt = new int[m];
    pt[0] = 0;
    pt[1] = 1;
    int *p = &*pt;
    cout << p[0] << endl;
    cout << (&*pt)[1] << endl;
    cout << p << endl;

}

void computePrac(){
    cout << (9 * (8 - 7) / 6 + 5 * 4 % 3 * (2 + 1.0)) << endl;
    cout << 7.0 << endl;
}

void ptrPrac(){
    int i = 2021, *pi = &i, **ppi = &pi;
    cout << i << endl;
    cout << pi << endl;
    cout << &pi << endl;
    cout << ppi << endl;
    cout << *ppi << endl;
    cout << **ppi << endl;

}

class A{
    public:
    int a;
    A(){a = 1;};
    void display(){
        cout << a << endl;
        cout << "AING"  << endl;
    }
};

class B :public A{
    public:
    int b;
    B(){b = 2;};
    void display(){
        cout << a << b << endl;
        cout << "BING" << endl;
    }
};

class C :public B{
    public:
    int c;
    C(){b = 1;c = 3;};
    virtual void display(){
        cout << a << b << c << endl;
        cout << "CING" << endl;
    }
};


void classPrac(){
        C oC;
    B* pb = &oC;
    pb->display();
}

void thirtyPrac(){
    int arr[] = {2, 0, 2, 1};
    int *p = arr;
    int a = *++p;
    int b = *p++;
    int c = ++*p;
    int d = (*p)++;
    cout << arr[0] << arr[1] << arr[2] << arr[3] << endl;
    cout << a << b << c << d << endl;
}

void doubleArrayPrac(){
    double doubleArray[] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18};
    double * doublePointer = doubleArray;
    cout << *++doublePointer << endl;
    cout << *doublePointer << endl;
}
void secondPrac(){
    double doubleArray[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};
    cout << doubleArray << endl;
    cout << *doubleArray << endl;
    cout << &doubleArray << endl;  // 数组本身的地址
    cout << &doubleArray[0] << endl;  // 数组第一个元素的地址
    cout << doubleArray[0] << endl;  // 数组第一个元素的值
    cout << doubleArray + 1 << endl;
    cout << &doubleArray + 1 << endl;
    cout << &doubleArray[1] << endl;
    cout << doubleArray + 9 << endl;
    cout << *doubleArray + 9 << endl;
    cout << *(doubleArray + 9) << endl;
    cout << &doubleArray[9] << endl;
    cout << doubleArray[9] << endl;
}
int main(){
    doubleArrayPrac();
}