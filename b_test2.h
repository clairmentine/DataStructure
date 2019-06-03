//
// Created by Apple on 2019-06-03.
//

#ifndef DATASTRUCTURE_CLION_CLANGUAGE_TEST2_H
#define DATASTRUCTURE_CLION_CLANGUAGE_TEST2_H


#define Max(a,b) ((a>b)? a: b)//삼항연상자 (조건식? true, false)
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>



//트리 생성
typedef int element; //이진 탐색 트리 element의 자료형 char
typedef struct treeNode{ //연결 자료구조를 구성하기 위해 트리의 노드 정의
    element key;
    struct treeNode *left; //왼쪽 서브 트리에 대한 링크 필드
    struct treeNode *right; //오른쪽 서브 트리에 대한 링크 필드
}treeNode;

//LL회전
treeNode *LL_rotate(treeNode *parent){
    treeNode *child= parent-> left;
    parent-> left= child-> right;
    child-> right= parent;
    return child;
}

//RR회전
treeNode *RR_rotate(treeNode *parent){
    treeNode *child= parent-> right;
    parent-> right= child-> left;
    child-> left= parent;
    return child;
}

//LR회전
treeNode *LR_rotate(treeNode *parent){
    treeNode *child= parent-> left;
    parent-> left= RR_rotate(child);
    return LL_rotate(parent);
}

//RL회전
treeNode *RL_rotate(treeNode *parent){
    treeNode *child= parent-> right;
    parent-> right= LL_rotate(child);
    return RR_rotate(parent);
}

//서브트리 높이 연산
int getHeight(treeNode *p){
    int height= 0;
    if(p!= NULL)
        height= Max(getHeight(p-> left), getHeight(p-> right))+1;
    return height;

}

//균형인수(BF) 구하는 연산
//: 서브트리 높이르 이용하여 균형인수 구하는 연산
int getBF(treeNode *p){
    if(p== NULL) return 0;
    return getHeight(p-> left)- getHeight(p-> right);
}

//BF를 검사하여 불균형이 발생한 경우, 회전 연산 호출
treeNode *rebalance(treeNode **p){
    int BF= getBF(*p);
    if(BF> 1){ //균형인수가 2가 될때
        if (getBF((*p)-> left)>0) //LL유형
            *p= LL_rotate(*p);
        else *p= LR_rotate(*p); //LR유형
    }
    else if(BF< -1){ //균형인수가 -2가 될때
        if (getBF((*p)-> right)<0) //RR유형
            *p= RR_rotate(*p);
        else *p= RL_rotate(*p); //RL유형
    }
    return *p;
}

//노드 삽입 (AVL트리)
//AVL트리에 노드를 삽입하는 연산 : 이진 탐색 연산처럼 삽입 후 rebalance()호출
treeNode *insert_AVL_Node(treeNode **root, element x){
    if(*root== NULL){
        *root= (treeNode *)malloc(sizeof(treeNode));
        (*root)-> key= x;
        (*root)-> left= NULL;
        (*root)-> right= NULL;
    }
    else if(x< (*root)-> key){
        (*root)-> left= insert_AVL_Node(&((*root)-> left), x);
        *root= rebalance(root);
    }
    else if(x> (*root)-> key){
        (*root)-> right= insert_AVL_Node(&((*root)-> right), x);
        *root= rebalance(root);
    }
    else {
        printf("\n이미 같은 키가 있습니다.\n");
    }
    return *root;
}


//노드 삽입 (이진 탐색 트리)
//: 포인터 p가 가르키는 노드와 비교하여 노드 x를 삽입하는 연산
treeNode* insert_BST_Node(treeNode *p, char x){
    treeNode *newNode;
    if(p== NULL){ //p가 가르키는 노드가 존재하지 않을 경우
        //노드 생성
        newNode= (treeNode *)malloc(sizeof(treeNode)); //동적할당
        newNode-> key= x;
        newNode-> left= NULL;
        newNode-> right= NULL;
        return newNode;
    }

        //p가 가르키는 노드가 존재하는 경우
    else if(x< p-> key) p-> left= insert_BST_Node(p-> left, x); //현재 키값이 찾으려는 키보다 크면-> 왼쪽에 노드 삽입
    else if(x> p-> key) p-> right= insert_BST_Node(p-> right, x); //현재 키값이 찾으려는 키보다 작으면-> 오른쪽에 노드 삽입
    else printf("\n이미 같은 키가 있습니다! \n"); //x= p-> key (찾는 키가 p의 키값과 일치할 경우)

    return p;
}

//이진 탐색트리 출력
//: 이진 탐색트리를 전위 순회하면서 출력하는 연산
void displayPreorder (treeNode *root) {
    if (root) {
        printf("%10d", root->key);
        displayPreorder(root->left);
        displayPreorder(root->right);
    }
}

//키값 x 탐색 (이진 탐색 트리, AVL트리)
//: 이진 탐색 트리와 AVL트리에서 키값 x를 탐색하는 연산
treeNode *searchTree(treeNode *root, element x){
    treeNode *p;
    int count= 0;
    p= root;
    while (p!= NULL){
        count++;
        if(x< p-> key) p= p-> left; //현재 키값이 찾으려는 키값보다 크면 왼쪽으로 이동
        else if(x== p-> key){
            printf("%3d번쨰 탐색 성공", count);
            return p;
        }
        else p= p-> right;
    }
    count++;
    printf("%3d번쨰 탐색 실패! 찾는 키가 없습니다. ",count);
    return p;
}



#endif //DATASTRUCTURE_CLION_CLANGUAGE_TEST2_H
