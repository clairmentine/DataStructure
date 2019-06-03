//
// Created by Apple on 2019-06-03.
//

#include "b_test2.h"
#include "b_test2_2.h"

int main() {
    int select = 0, userData = 0;
    treeNode *root_AVL = NULL;
    root_AVL = NULL;

    //트리의 원소 입력
    root_AVL = insert_AVL_Node(&root_AVL, 50); //AVL트리 생성
    insert_AVL_Node(&root_AVL, 60);
    insert_AVL_Node(&root_AVL, 70);
    insert_AVL_Node(&root_AVL, 90);
    insert_AVL_Node(&root_AVL, 80);
    insert_AVL_Node(&root_AVL, 75);
    insert_AVL_Node(&root_AVL, 73);
    insert_AVL_Node(&root_AVL, 72);
    insert_AVL_Node(&root_AVL, 78);

    //트리의 원소 출력
    printf("AVL 트리: ");
    displayPreorder(root_AVL);

    while (1) {
        printf("\n기능을 선택하시오\n");
        scanf("%d %d", &select, &userData);
        if (select == 1) { //데이터 삽입
            insert_AVL_Node(&root_AVL, userData);
            printf("AVL 트리: ");
            displayPreorder(root_AVL);
        }

        else if (select == 2) { //데이터 삭제
            deleteNode(root_AVL, userData);
            printf("AVL 트리: ");
            displayPreorder(root_AVL);
        }

        else if (select == 3) { //데이터 존재하면 데이터 삭제, 데이터 존재하지 않으면 제곱해서 삽입
            deleteNodeDoubleInsert(root_AVL, userData); //제곱해서 데이터 삽입
            printf("AVL 트리: ");
            displayPreorder(root_AVL);//전위순회
        }

        else if (select == 4) { //자식이 1개 노드값과 주소값 출력
            getChildOneNode(root_AVL);
        }
        else if (select == 5) { //단말노드의 값 출력
            finalNode(root_AVL);
        }
        else if (select == 6)
            break;
    }
}