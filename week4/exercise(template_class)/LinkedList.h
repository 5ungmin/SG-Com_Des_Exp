#ifndef __LINKEDLIST__
#define __LINKEDLIST__

#include <iostream>
using namespace std;

//LinkedList Node
//다양한 자료형에 대해 사용 가능하도록 템플릿 클래스로 작성
template <typename T>
class Node{
    public:
        T data; //데이터를 저장할 변수
        Node *link; //노드 구조체 이용; 다음 노드의 주소를 저장할 포인터

        //생성자, 초기화
        Node(T element){
          data = element;
          link = 0;
        }
    };

//LinkedList Class
//다양한 자료형에 대해 사용 가능하도록 템플릿 클래스로 작성
template <typename T>
class LinkedList{
    protected:
        Node<T> *first; //첫번째 노드의 주소를 저장할 포인터
        int current_size; //링크드리스트의 크기를 저장할 변수
    public:
        //생성자, 초기화
        LinkedList(){
            first = 0;
            current_size = 0;
        };

        //노드 개수를 리턴
        int GetSize(){
            return current_size;
        };

        //맨 앞에 원소를 삽입, LinkedList와 Stack 둘 다 같다
        void Insert(T element);
        
        //맨 뒤의 원소를 삭제, 제일 나중에 들어온 원소 삭제  - LinkedList
        virtual bool Delete(T &element);

        //리스트 출력
        void Print();
};


//새 노드를 맨 앞에 붙이고 값을 넣음
template <typename T>
void LinkedList<T>::Insert(T element){
    Node<T> *newnode = new Node<T>(element); //노드 생성

    //newnode는 포인터이기 때문에 -> 를 사용해 함수, 변수를 불러옴
    //newnode.link와 뜻은 같음
    newnode -> link = first; //새 노드가 첫번째 노드를 가리킴
    first = newnode; //새 노드를 첫번째 노드로 만듦(맨 앞에 추가함)
    current_size++; //링크드리스트 크기를 1 증가
}

//마지막 노드의 값을 리턴하면서 메모리에서 할당 해제
template <typename T>
bool LinkedList<T>::Delete(T &element){
    //링크드리스트가 비어있다면(first가 0이라면) false를 반환
    if (first == 0)
        return false;
    
    Node<T> *current = first; //current를 첫번째 요소로 설정
    Node<T> *previous = 0; //previous는 0으로 초기화
    
    //마지막 노드까지 찾아가는 반복문
    while(1){
        //current가 마지막 노드라면, previous의 존재 유무에 따라 다른 실행을 하고 루프 종료
        if (current->link == 0){
            //previous가 있다면, previous가 마지막 요소가 될 것이므로 previous->link를 current->link로 설정
            if (previous)
                previous -> link = current -> link;
            //previous가 없다면, current가 유일한 요소이므로 first를 first->link로 리셋
            else
                first = first -> link;
            break;
        }
        //다음 노드로 넘어감
        previous = current;
        current = current -> link;
    }
    element = current -> data; //전달받은 인자에 삭제 대상 노드의 데이터를 저장
    delete current; //노드 메모리 할당 해제
    current_size--; //링크드리스트 크기 1 감소

    return true;
}

//리스트를 출력하는 Print 함수
template <typename T>
void LinkedList<T>::Print(){
    Node<T> *i;
    int index = 1;

    //링크드리스트에 있는 노드가 1개 이상일 때만 출력
    if (current_size != 0){
        for( i = first; i != NULL; i=i->link){
            //마지막 노드는 "]"까지 출력
            if (index == current_size){
                cout << "[" << index << "|";
                cout << i -> data <<"]";
            }
            //마지막 노드가 아닌 노드들은 "]->"까지 출력
            else {
                cout << "[" << index << "|";
                cout << i -> data << "]->";
                index++;
            }
        }
        cout << endl;
    }

}


#endif
