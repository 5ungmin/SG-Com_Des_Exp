#include <stdio.h>
#include <string>
#include "Stack.h"

int main() {
    double dVal;
    string strVal;
    
    LinkedList<double> dList;
    LinkedList<string> strList;
    
    /* double 자료형 링크드리스트*/
    //삽입
    dList.Insert(3.14);
    dList.Insert(123456);
    dList.Insert(-0.987654);
    //출력
    dList.Print();
    //삭제 및 확인
    dList.Delete(dVal);
    cout<<"삭제된 마지막 원소: "<<dVal<<endl;
    //출력
    dList.Print();
    //삽입
    dList.Insert(777.777);
    //출력
    dList.Print();
    //삭제 및 확인
    dList.Delete(dVal);
    cout<<"삭제된 마지막 원소: "<<dVal<<endl;
    //삭제 및 확인
    dList.Delete(dVal);
    cout<<"삭제된 마지막 원소: "<<dVal<<endl;
    dList.Print();
    //삭제 및 확인
    dList.Delete(dVal);
    cout<<"삭제된 마지막 원소: "<<dVal<<endl;
    dList.Print();

    /* string 자료형 링크드리스트*/
    //삽입
    strList.Insert("This");
    strList.Insert("is a");
    strList.Insert("Template");
    strList.Insert("Example");
    //출력
    strList.Print();
    //삭제 및 확인
    strList.Delete(strVal);
    cout<<"삭제된 마지막 원소: "<<strVal<<endl;
    //삽입
    strList.Insert("Class");
    //출력
    strList.Print();

    return 0;
}

