#include <stdio.h>
#include <stdlib.h>

// doubly linked list의 노드 구조체 정의
typedef struct _LogNode{
    int base;
    float argument;
    struct _LogNode* prevNode;
    struct _LogNode* nextNode;
} LogNode;

// doubly linked list 구조체 정의
typedef struct _DLList{
    int size;
    LogNode* head;
    LogNode* tail;
} DLList;

// 새로운 doubly linked list 생성
// 리스트의 시작 노드와 끝 노드에 대한 포인터 관리 용이
DLList* createDLList(){                                 
    DLList* list = (DLList *)malloc(sizeof(DLList));
    list -> size = 0;
    list -> head = NULL;
    list -> tail = NULL; 
    return list;                                            // 생성된 list를 가리키는 포인터 반환
}         

// 노드를 더블 링크드 리스트 안에 넣는다.
void addLogNode(DLList* list, int base, float argument){    
    LogNode* newNode = (LogNode *)malloc(sizeof(LogNode));
    newNode -> base = base;                          
    newNode -> argument = argument; 
    newNode -> prevNode = NULL; 
    newNode -> nextNode = NULL; 
    
    if (list->head == NULL) { 
        list->head = newNode;  
        list->tail = newNode; 
    } else {
        newNode->prevNode = list->tail;
        list->tail->nextNode = newNode;
        list->tail = newNode; 
    }
    list->size++;
}

// 더블 링크드 리스트를 print한다.
void printDLList(DLList* list){                                         
    LogNode* current = list -> head;                                    
    while (current != NULL){
        printf("Log%d %.2f", current -> base, current -> argument);
        if (current -> nextNode != NULL){
            printf(" + ");
        }
        current = current -> nextNode;
    }
    
}

// 노드와 더블 링크드 리스트의 메모리를 release 해준다.
void freeDLList(DLList* list){
    LogNode* current = list -> head;
    LogNode* nextNode;

    while (current != NULL){
        nextNode = current -> nextNode;
        free(current);
        current = nextNode;
    }
    free(list);
}

// 기존 로그 노드의 값을 업데이트하거나 해당 base를 가진 노드가 없으면 새 노드 추가
// 노드를 추가하거나 갱신할 때
void updateLogNode(DLList* list, int base, float argument){
    LogNode* current = list->head;
    while (current != NULL) {
        if (current->base == base) {                            // current 노드의 base값과 매개변수 base값 비교
            current->argument *= argument;                      // 같으면 current의 argument와 매개변수 argument 곱함
            return;                                             // 함수 종료
        }
        current = current->nextNode;                            // 다르면 current를 다음 노드
    }
    addLogNode(list, base, argument);                           // 일치하는 base가 없으면 addLogNode 호출
}

// 각 리스트의 합산 결과를 나타내는 DLList 객체 생성 및 반환
DLList* addLog(DLList* one, DLList* two, DLList* three){
    DLList* result = createDLList();
    LogNode* current_one = one -> head;
    LogNode* current_two = two -> head;
    LogNode* current_three = three -> head;

    while (current_one != NULL){
        updateLogNode(result, current_one -> base, current_one -> argument);
        current_one = current_one -> nextNode;
    }

    while (current_two != NULL){
        updateLogNode(result, current_two -> base, current_two -> argument);
        current_two = current_two -> nextNode;
    }

    while (current_three != NULL){
        updateLogNode(result, current_three -> base, current_three -> argument);
        current_three = current_three -> nextNode;
    }
    return result;
}

// 각 리스트의 뺄셈 결과를 나타내는 DLList 객체 생성 및 반환
DLList* subtractLog(DLList* one, DLList* two){
    DLList* result = createDLList();
    LogNode* current_one = one -> head;
    LogNode* current_two = two -> head;

    while (current_one != NULL){
        updateLogNode(result, current_one -> base, current_one -> argument);
        current_one = current_one -> nextNode;
    }

    while (current_two != NULL){
        updateLogNode(result, current_two -> base, 1 / current_two -> argument);
        current_two = current_two -> nextNode;
    }

    return result;
}

int main(void)
{
    // list 생성
    DLList *list1 = createDLList();
    DLList *list2 = createDLList();
    DLList *list3 = createDLList();

    // 새로운 노드 객체 생성 및 추가
    addLogNode(list1, 2, 3);
    addLogNode(list1, 3, 2);
    addLogNode(list2, 2, 6);
    addLogNode(list2, 3, 4);
    addLogNode(list3, 5, 7);

    DLList *multiply_result = addLog(list1, list2, list3);          // 반환된 객체를 multiply_result이라는 DLList 객체에 저장
    DLList *divide_result = subtractLog(list1, list2);              // 반환된 객체를 divide_result이라는 DLList 객체에 저장
    
    // print
    printf("(Log2 3+Log3 2) + (Log2 6 + Log3 4 + Log5 7) = (");
    printDLList(multiply_result);
    printf(")\n");
    printf("(Log2 3+Log3 2) - (Log2 6+Log3 4) = (");
    printDLList(divide_result);
    printf(")\n");

    // 메모리 반환
    freeDLList(list1);
    freeDLList(list2);
    freeDLList(list3);
    freeDLList(multiply_result);
    freeDLList(divide_result);
    
    return 0;
}