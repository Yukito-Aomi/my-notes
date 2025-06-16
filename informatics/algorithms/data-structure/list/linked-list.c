#include <stdio.h>
#include <stdlib.h>


/**
 * 連結リストを実現するためのノードを表す構造体
 */
typedef struct node
{
    /* data field */
    int element;
    /* reference */
    struct node *next;
} Node;


/* 関数原型宣言 */
void print_list(Node *head);
Node *free_list(Node *head);
Node *insert(int x, Node *p, Node *head);
Node *delete(Node *p, Node *head);


/**
 * メイン関数
 */
int main(int argc, const char * argv[])
{
    Node *head, *p;
    
    head = NULL;
    p = NULL;
    for (int i = 0; i < 10; i++) {
        head = insert(i + 1, p, head);
    }
    print_list(head);
    
    p = head->next->next;
    for (int i = 0; i < 6; i++) {
        head = delete(p, head);
    }
    print_list(head);
    
    free_list(head);
    
    return 0;
}


/**
 * 連結リストを標準出力する関数
 */
void print_list(Node *head)
{
    printf("head(%p): [\n", head);
    while (head != NULL) {
        printf("(%d,%p),\n", head->element, head->next);
        head = head->next;
    }
    puts("]");
}


/**
 * 連結リストのデータ領域を開放する関数
 */
Node *free_list(Node *head)
{
    Node *p, *q;
    p = head;
    
    while (p != NULL) {
        q = p->next;
        free(p);
        p = q;
    }
    
    return NULL;
}


/**
 * 連結リストにノードを挿入する関数
 */
Node *insert(int x, Node *p, Node *head)
{
    Node *q, *r;
    
    r = (Node *)malloc(sizeof(Node));
    
    if (p == NULL) {
        /* ポインタ p が head を指す場合，先頭にノードを挿入 */
        q = head;
        head = r;
    } else {
        /* ポインタ p が指すノードの次に x のノードを挿入 */
        q = p->next;
        p->next = r;
    }
    
    r->element = x;
    r->next = q;
    
    return head;
}


/**
 * 連結リストからノードを消去する関数
 */
Node *delete(Node *p, Node *head)
{
    Node *q;
    
    if (head == NULL) {
        puts("Error: List is empty.");
        exit(1);
    } else if (p == NULL) {
        /* ポインタ p が head を指す場合，先頭のノードを消去 */
        q = head;
        head = head->next;
        free(q);
    } else {
        /* ポインタ p が指すノードの次のノードを消去 */
        if (p->next == NULL) {
            puts("Error: No node to remove.");
            exit(1);
        } else {
            q = p->next;
            p->next = q->next;
            free(q);
        }
    }
    
    return head;
}
