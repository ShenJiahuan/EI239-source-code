#include "stdlib.h"
#include "string.h"
#include <cstdio>
typedef struct PolyNode
{   
    float coef;            //系数
    int exp;               //指数
    struct PolyNode *next;
} PolyNode;
typedef PolyNode *Polynomial;
 
Polynomial CreateList(){
    float co;
    int   ex;
    Polynomial head,p,l;
    head = (Polynomial)malloc(sizeof(PolyNode));    
    p = head;
    scanf("%f%d",&p->coef,&p->exp);         //设置头结点，并且设置第一个节点，为了保证表不为空
    if(head->coef==0&&head->exp==0){        //如果头结点数据元素均为0，则为单节点链表
    head->next=NULL;
    }else{
    p->next=(Polynomial)malloc(sizeof(PolyNode));
    p=p->next;
    while(1){
    scanf("%f%d",&co,&ex);
    if(co==0&&ex==0) break;         // x=0并且y=0 代表结束输出
        p->coef=co;
        p->exp =ex;
        l=p;
        p->next =(Polynomial)malloc(sizeof(PolyNode));
        p=p->next;
    } 
    l->next = NULL;
    }
    return head;
}
void Sortlist(Polynomial L){ // 用冒泡法对链表L中的节点按指数降序排列。
    Polynomial a,b;
    float temp_co;        //设置中间变量来交换链表元素的值；
    int temp_ex;
    b =L;
    a =L;
    for(a;a!=NULL;a=a->next){
        b= L ;
        for(b;b->next!=NULL;b=b->next){
            if(b->exp<b->next->exp){
            temp_co=b->coef;
            temp_ex=b->exp;
            b->coef=b->next->coef;
            b->exp =b->next->exp;
            b->next->coef =temp_co;
            b->next->exp  =temp_ex;
            }
        }
    }   
    return;
}
void Display(Polynomial p){
    Polynomial Pointer;
    Pointer =p;
    do{
    printf("%.2fx^%d  ",Pointer->coef,Pointer->exp);
    Pointer=Pointer->next;
    }while(Pointer!=NULL);
}
Polynomial LinkList(Polynomial A,Polynomial B,int n)  //链接链表A B，在这里设定B的头指针为连接后的头指针 n=1表示加法，n=2表示减法；
    {
    Polynomial tail_b,C,op_pointer;  // op_pointer 用来取反链表B cof 的数值。
    tail_b =B;
    op_pointer =B;
    for(op_pointer;op_pointer!=NULL;op_pointer=op_pointer->next){
        if(n==2){
        op_pointer->coef = -op_pointer->coef;
        //printf("%.2f  %d\n",op_pointer->coef,op_pointer->exp);
        }
    };
 
    for(tail_b;tail_b->next!=NULL;tail_b=tail_b->next);  // 连接 B A 链表，以B链表头为合并后的表头
    tail_b->next=A;
 
    C=B;
    Sortlist(C);
    return C;
    }
void MergeList(Polynomial C){      // 合并C中exp数值相同的节点.
    Polynomial C1,C2;
    C1=C;
    C2=C1->next;
    while(C2!=NULL){
        if(C1->exp == C1->next->exp){
        C1->coef=C1->next->coef+C1->coef;
        C1->next=C1->next->next;
        free(C2);
        C2=C1->next;
        }else{
        C1=C1->next;
        C2=C2->next;
        }
    }
}
 
int main(){
    Polynomial A,B,Com;
    int s;
    printf("\n请输入链表A的数据:格式为 coeffient exp 以空格分开\n");
    A = CreateList();
    Display(A);
    printf("\n请输入链表B的数据:格式为 coeffient exp 以空格分开\n");
    B = CreateList();
    Display(B);
    printf("请选择加法还是减法\n");
    printf("输入1代表加法\n");
    printf("输入2代表减法\n");
    scanf("%d",&s);
    if(s==1||s==2){
        Com = LinkList(A,B,s);  
        MergeList(Com);
        Display(Com);
    }else{
        printf("输入了非法字符\n");
    }
 return 0;
}

