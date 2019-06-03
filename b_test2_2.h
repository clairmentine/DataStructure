//
// Created by Apple on 2019-06-03.
//

#ifndef DATASTRUCTURE_CLION_CLANGUAGE_B_TEST2_2_H
#define DATASTRUCTURE_CLION_CLANGUAGE_B_TEST2_2_H

//노드 삭제
//: 루트 노드부터 탐색하여 키값과 같은 노드를 찾아 삭제하는 연산
void deleteNode(treeNode *root, element key){
    treeNode *parent, *p, *succ, *succ_parent;
    treeNode *child;
    parent= NULL;
    p= root;

    //p가 존재하고 p의 키값이 찾으려는 키값이 아닌 경우
    while((p != NULL) && (p-> key != key)){
        parent= p;
        if(key< p-> key) p= p-> left; //현재 키값이 찾으려는 키보다 크면-> 왼쪽으로 이동
        else p= p-> right;
    }

    //삭제할 노드가 없는 경우
    if(p== NULL){
        printf("\n 찾는 키가 이진 트리에 없습니다!");
        return;
    }

    //삭제할 노드가 단말 노드인 경우
    if((p-> left== NULL) && (p-> right== NULL)){
        if(parent != NULL){
            if(parent-> left== p) parent-> left= NULL;
            else parent-> right= NULL;
        }
    }

        //삭제할 노드가 자식노드를 한개 가진 경우
    else if((p-> left== NULL) || (p-> right== NULL)){
        if (p-> left != NULL) child= p-> left; //p의 자식노드: 왼쪽 노드
        else child= p-> right;

        //부모노드가 존재할 경우
        if(parent != NULL){
            if(parent-> left== p) parent-> left= child;
                //p의 노드위치: 왼쪽 -> p의 노드 위치(왼쪽)에 child 연결
            else parent-> right= child;
        }
            //부모노드가 존재하지 않을 경우 (p의 level: 0== root인 경우)
        else root= child;
    }

        //(어려움 주의)
        //삭제할 노드가 자식 노드를 두개 가진 경우
    else {
        succ_parent= p;
        succ= p-> left; //p의 왼쪽 서브 트리
        while (succ-> right != NULL){
            //왼쪽 서브 트리에서 후계자 찾기
            //: 왼쪽 서브트리 중 가장 큰 수를 찾음 (오른쪽 링크값이 없는 노드)
            //왜냐하면 이진 탐색 노드는 root의 크기가 왼쪽 서브트리와 오른쪽 서브트리의 중간이여야함
            //그래서 root이 삭제되고나면 root이 될 수 있는 건 왼쪽 서브트리 중 가장 큰값이나 오른쪽 서브트리 중 가장 작은 값임
            succ_parent= succ; //왼쪽 서브트리 중 가장 큰 값을 부모로 설정
            succ= succ-> right;
            // 후계자인 succ-> right= NULL인 애 찾기 위해서 succ에 succ-> right을 삽입해 주는 것
            // 후계자 찾기 전노드에서 후계자를 succ으로 초기화해줌
        }//후계자: succ

        if(succ_parent-> left== succ)
            succ_parent-> left= succ-> left; //succ의 위치에 succ의 자손 삽입하여 succ_parent와 연결
        else succ_parent-> right= succ-> left;
        p-> key= succ-> key; //후계자succ이 root가 되기 전 원래 있던 succ을 삭제하기 위해 p에 데이터 저장
        p= succ;
    }
    free(p);
}

//입력값의 두배인 값 삽입 (AVL트리)
treeNode *doubleInsert(treeNode **root, element x){
    element xx= x*x;
    if(*root== NULL){
        *root= (treeNode *)malloc(sizeof(treeNode));
        (*root)-> key= xx;
        (*root)-> left= NULL;
        (*root)-> right= NULL;
    }
    else if(xx< (*root)-> key){
        (*root)-> left= insert_AVL_Node(&((*root)-> left), xx);
        *root= rebalance(root);
    }
    else if(xx> (*root)-> key){
        (*root)-> right= insert_AVL_Node(&((*root)-> right), xx);
        *root= rebalance(root);
    }
    else {
        printf("\n이미 같은 키가 있습니다.\n");
    }
    return *root;
}

//노드 삭제
//: 루트 노드부터 탐색하여 키값과 같은 노드를 찾아 삭제하는 연산
treeNode* deleteNodeDoubleInsert(treeNode *root, element key){
    treeNode *parent, *p, *succ, *succ_parent;
    treeNode *child;
    parent= NULL;
    p= root;

    //p가 존재하고 p의 키값이 찾으려는 키값이 아닌 경우
    while((p != NULL) && (p-> key != key)){
        parent= p;
        if(key< p-> key) p= p-> left; //현재 키값이 찾으려는 키보다 크면-> 왼쪽으로 이동
        else p= p-> right;
    }

    //삭제할 노드가 없는 경우
    if(p== NULL){
        doubleInsert(&root, key);
    }

    //삭제할 노드가 단말 노드인 경우
    if((p-> left== NULL) && (p-> right== NULL)){
        if(parent != NULL){
            if(parent-> left== p) parent-> left= NULL;
            else parent-> right= NULL;
        }
    }

        //삭제할 노드가 자식노드를 한개 가진 경우
    else if((p-> left== NULL) || (p-> right== NULL)){
        if (p-> left != NULL) child= p-> left; //p의 자식노드: 왼쪽 노드
        else child= p-> right;

        //부모노드가 존재할 경우
        if(parent != NULL){
            if(parent-> left== p) parent-> left= child;
                //p의 노드위치: 왼쪽 -> p의 노드 위치(왼쪽)에 child 연결
            else parent-> right= child;
        }
            //부모노드가 존재하지 않을 경우 (p의 level: 0== root인 경우)
        else root= child;
    }

        //(어려움 주의)
        //삭제할 노드가 자식 노드를 두개 가진 경우
    else {
        succ_parent= p;
        succ= p-> left; //p의 왼쪽 서브 트리
        while (succ-> right != NULL){
            //왼쪽 서브 트리에서 후계자 찾기
            //: 왼쪽 서브트리 중 가장 큰 수를 찾음 (오른쪽 링크값이 없는 노드)
            //왜냐하면 이진 탐색 노드는 root의 크기가 왼쪽 서브트리와 오른쪽 서브트리의 중간이여야함
            //그래서 root이 삭제되고나면 root이 될 수 있는 건 왼쪽 서브트리 중 가장 큰값이나 오른쪽 서브트리 중 가장 작은 값임
            succ_parent= succ; //왼쪽 서브트리 중 가장 큰 값을 부모로 설정
            succ= succ-> right;
            // 후계자인 succ-> right= NULL인 애 찾기 위해서 succ에 succ-> right을 삽입해 주는 것
            // 후계자 찾기 전노드에서 후계자를 succ으로 초기화해줌
        }//후계자: succ

        if(succ_parent-> left== succ)
            succ_parent-> left= succ-> left; //succ의 위치에 succ의 자손 삽입하여 succ_parent와 연결
        else succ_parent-> right= succ-> left;
        p-> key= succ-> key; //후계자succ이 root가 되기 전 원래 있던 succ을 삭제하기 위해 p에 데이터 저장
        p= succ;
    }
    free(p);
}

//자식 노드 1개인 노드 찾기
treeNode *getChildOneNode(treeNode *root) {
    treeNode *p = root;
    if(root){
        if(!((p-> left== NULL) && (p-> right== NULL))){ //단말 노드가 아니고
            if ((p->left == NULL) || (p->right == NULL)) { //자식이 하나인 노드
                printf("%3d %3d\n", p->key, &(p->key));
            }
        }
        getChildOneNode(root->left);
        getChildOneNode(root->right);
    }

}

//단말 노드 찾기 
treeNode *finalNode(treeNode *root){
    treeNode *p = root;
    if(root){
        if((p-> left== NULL) && (p-> right== NULL)){ //단말 노드인 경우
            printf("%3d", p->key);
        }
        //순회하기 위해
        finalNode(root->left);
        finalNode(root->right);
    }
}




#endif //DATASTRUCTURE_CLION_CLANGUAGE_B_TEST2_2_H
