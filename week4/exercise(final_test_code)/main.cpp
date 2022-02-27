#include <stdio.h>
#include <string>
#include "Stack.h"

//메뉴를 출력하는 함수
void prnMenu(){
    cout<<"*******************************************"<<endl;
    cout<<"* 1. 삽입    2. 삭제    3. 출력   4. 종료 *"<<endl;
    cout<<"*******************************************"<<endl;
    cout<<endl;
    cout<<"원하시는 메뉴를 골라주세요: ";
}

int main(){
        int mode, selectNumber, tmpItem;
        LinkedList<int> *p;
        bool flag = false; //종료 신호를 저장하는 변수

        //사용할 자료구조를 입력받음
        cout<<"자료구조 선택(1: Stack, Other: Linked List): ";
        cin>>mode;
                     
        //Stack
        if(mode == 1)
            p = new Stack<int>(); // 정수를 저장하는 스택
        
        //Linked List
        else
            p = new LinkedList<int>(); //정수를 저장하는 링크드 리스트


        do{
            //삽입-삭제-출력-종료 메뉴 출력
            prnMenu();
            cin>>selectNumber;
            
            switch(selectNumber){
                case 1:
                    //삽입
                    cout<<"원하시는 값을 입력해주세요: ";
                    cin>>tmpItem;
                    p->Insert(tmpItem);
                    cout<<tmpItem<<"가 삽입되었습니다."<<endl;
                    break;
                    
                case 2:
                    //삭제
                    if(p->Delete(tmpItem)==true)
                        cout<<tmpItem<<"가 삭제되었습니다."<<endl;
                        
                    else cout<<"비어있습니다. 삭제 실패"<<endl;
                    
                    break;
                    
                case 3:
                    //출력
                    cout<<"크기: "<<p->GetSize()<<endl;
                    p->Print();
                    break;
                    
                case 4:
                    //종료 (flag을 true로 변경)
                    flag = true;
                    break;
                    
                default:
                    //예외 처리
                    cout<<"잘못 입력하셨습니다."<<endl;
                    break;
            
            }
            
            if(flag) break;
            
        } while(1);
        
        return 0;
}

