class LinkedList *insertAtIndex(class LinkedList *node, int num, int index){
    class LinkedList *ptr;
    ptr = (class LinkedList*)malloc(sizeof(class LinkedList));
    class LinkedList *p = node;
    int i=0;
    while(i!=index-1){
        p = p->next;
        i++;
    }
    ptr->data = num;
    ptr->next = p->next;
    p->next = ptr;
    return node;
}
