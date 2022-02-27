#include "LinkedList.h"

//1. 템플릿 클래스로 확장해야함
//2. Stack형식으로 Delete 함수 재정의해야함
//주의: first, current_size는 class의 멤버 변수이기 때문에 this 포인터를 사용하여 가져와야함

//LinkedList class를 상속받음
//다양한 자료형에 대해 사용 가능하도록 템플릿 클래스로 작성
template <typename T>
class Stack : public LinkedList<T>{
    public:
        //Stack은 LinkedList와 달리 가장 첫 요소를 삭제하므로 delete() 함수만 overriding
        bool Delete (T &element){
            //스택이 비어있다면(first가 0이면) false반환
            if(this->first == 0) {
                return false;
            }
            
            Node<T> *current = this->first; //current를 스택의 첫 요소로 설정
            
            this->first = current->link; //스택의 첫 요소를 첫 요소의 link로 설정
            
            
            element = current->data; //전달받은 인자에 삭제 대상 요소의 데이터를 저장
            delete current; //메모리 할당 해제
            this->current_size--; //스택 크기 1 감소

            return true;
            }
};
