/**
*  	第一次题目	：构建二叉树(链表存储方式)，空格表示空树，实现二叉树的基本操作:创建，遍历（先，中，后，按层）二叉树
*  	提交邮箱 		：510495266@qq.com   to  learn_algorithm@163.com
*  	邮件题目		：第一期第一次作业
**/

#include <stdlib.h>
#include <stdio.h>
typedef struct BiTNode{
	char item;
	struct BiTNode *lChild,*rChild;

}BiTNode,*BiTree;
#define OK 1
#define ERROR 0
typedef int bool;
typedef BiTree ElemType ; // 也可能是一个复杂的复合类型
typedef int Status;
//队列的顺序存储
typedef struct Node{
    ElemType *elem;
    ElemType *head;
    ElemType *tail;
    int length;   // 当前队列的长度
    int size;     // 队列容器的长度，在队列慢得时候可以扩容
}SqQueue;
typedef struct QNode{
    struct QNode *next;
    ElemType elem;
}LinkQueue;
typedef struct{
    LinkQueue *head;
    LinkQueue *tail;
    int length;
}Queue;
Status initQueue(Queue *queue);// 带头结点,没有引用传值，就用指针的指针吧
bool isEmpty(Queue *q);
int length(Queue *q);
Status getHead(Queue *q,ElemType *e);
Status enQueue(Queue *q,ElemType e);
Status deQueue(Queue *q,ElemType *e);
void traveser(Queue *q);
Status initQueue(Queue *queue){// 带头结点,没有引用传值，就用指针的指针吧
    LinkQueue *lq = (LinkQueue *)malloc(sizeof(LinkQueue));
    if (!lq) {
        return ERROR;
    }
    lq->elem = NULL;
    lq->next = NULL;
    (queue)->head = (queue)->tail = lq; // -> 优先级高于 * ,老老实实打上括号
    (queue)->length = 0;
    return OK;
}
bool isEmpty(Queue *q){
    return (q->head == q->tail);
}
int length(Queue *q){   
//    int ret;
//    LinkQueue *p = q->head;
//    while (p != q->tail) {
//        ret++;
//        p = p->next;
//        
//    }
    return q->length;
}
Status getHead(Queue *q,ElemType *e){
    LinkQueue *p = q->head->next;
    if (!p) {
       	*e=NULL;
        return ERROR;
    }
    *e = p->elem;
    return OK;
    
}
// 入队(将当前要插入的数加入到整个二叉树的最低层)
Status enQueue(Queue *q,ElemType e){

    LinkQueue *newNode = (LinkQueue *)malloc(sizeof(LinkQueue));
    if (!newNode) {
        return ERROR;
    }
    newNode->elem = e;
    newNode->next = NULL;
    q->tail->next = newNode;
    q->tail = newNode;
    
    q->length++;
    
    return OK;
    
}
//出队（队头）可能只有一个元素或多个元素，如果是一个元素会造成指针丢失 
Status deQueue(Queue *q,ElemType *e){
    LinkQueue *p = q->head->next;
    if (!p) {// 队列空
        return ERROR;
    }
    if (e) {
         *e = p->elem ;
    }
    LinkQueue *temp = p->next;
    q->head->next = temp;
    if (p == q->tail) {
        q->tail = q->head;
    }
    free(p);
    q->length--;
    return OK;
}
//最后整个就是从父亲节点到子节点，并在int mian里面输出 
void traveser(Queue *q){
    
    LinkQueue *p = q->head->next;
    while (NULL != p) {
        //printf("%d\n",p->elem);
        p=p->next;
    }
    
}


// ==================================================



/*
int CreateBiTree(BiTree *T)
{
	*T = (BiTNode *)malloc(sizeof(BiTNode));
	if (*T==NULL)
	{
		printf("memery malloc failure !\n");
		return -1;
	}
	printf("enter data to create node:\n");
	scanf("%c",&((*T)->item));
	if((*T)->item=='#'){
		*T=NULL;
	} 
	if(*T){
		printf("创建左子树:\n");
		CreateBiTree( &((*T)->lChild) );
		printf("创建右子树:\n");
		CreateBiTree( &((*T)->rChild) );
	}
	return 0;
}
*/
// BiTree CreateBiTree()
// 用前序遍历或后序遍历创建有个二叉树 
BiTree CreateBiTree(){
	char c;
	BiTNode *tree;
	// 过滤回车键
	scanf("%c",&c);
	if (c==' ')
	{
		printf("创建空节点\n");
		tree = NULL;
	}else{
		printf("创建节点 %c\n",c);
		tree = (BiTNode *)malloc(sizeof(BiTNode));
		tree->item = c;
		tree->lChild = CreateBiTree();
		tree->rChild = CreateBiTree();
	}
	return tree;
}
//将二叉树从父亲节点遍历到子节点，将其输出，并还原成最开始的节点，从新遍历以此类推，直到父亲节点比字节点大，上层字节点比下层字节点大，方可输出。
int PreOrderTraverse(BiTree T){

	if(T){
		printf("%c\n",T->item );
		PreOrderTraverse(T->lChild);
		PreOrderTraverse(T->rChild);
	}
	return 0;
}
//将二叉树从父亲节点遍历到子节点，将其输出，并还原成最开始的节点，从新遍历以此类推，直到父亲节点比字节点大，上层字节点比下层字节点大，方可输出。
int InOrderTraverse(BiTree T){
	if (T){
		InOrderTraverse(T->lChild);
		printf("%c\n", T->item);
		InOrderTraverse(T->rChild);
	}
	return 0;
}
//将二叉树从父亲节点遍历到子节点，将其输出，并还原成最开始的节点，从新遍历以此类推，直到父亲节点比字节点大，上层字节点比下层字节点大，方可输出。
int PostOrderTraverse(BiTree T){

	if (T)
	{
		PostOrderTraverse(T->lChild);
		PostOrderTraverse(T->rChild);
		printf("%c\n",T->item );
	}
	return 0;
}
// 用搜索中的广度优先遍历（可用多种方式，建议使用队列实现）
int LevelOrderTraverse(BiTree T){
	if (T)
	{
		Queue queue;
		initQueue(&queue);
		BiTree u;   
    	u=(BiTree)malloc(sizeof(BiTNode));   
   		enQueue(&queue, T);   
     	 while(!isEmpty(&queue))   
		{    
       		 deQueue(&queue, &u);   
        	 printf("%c",u->item);   
			if(u->lChild)   
    			enQueue(&queue, u->lChild);   
			if(u->rChild)   
       			enQueue(&queue, u->rChild);   
		}  
	} 
	return 0;
}
//将上面的函数合并到int main()中输出前序遍历，中序遍历，后序遍历，层序遍历；
 int main(int argc, char const *argv[])
{
	/* code */
	BiTree binaryTree;
	printf("创建二叉树，输入\"空格\"创建空节点（先序方式建立二叉树）:\n");
	binaryTree =  CreateBiTree();
	if(binaryTree==NULL){
		printf("创建空的二叉树\n");
	}
	printf("前序遍历:\n");
	PreOrderTraverse(binaryTree);
	printf("\n\n");
	printf("中序遍历:\n");
	InOrderTraverse(binaryTree);
	printf("\n\n");
	printf("后序遍历:\n");
	PostOrderTraverse(binaryTree);
	printf("\n\n");
	printf("层序遍历:\n");
	LevelOrderTraverse(binaryTree);
	printf("\n\n");
	return 0;
}





