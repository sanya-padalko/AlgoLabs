#ifndef __BINOM_HEAP__
#define __BINOM_HEAP__

struct Node {
    int value;
    struct Node* parent;
    struct Node* child;
    struct Node* next;
    int degree;
};

struct BinomHeap {
    struct Node* head;
};

static struct BinomHeap* BinomHeap_ctr() {
    struct BinomHeap* Heap = (struct BinomHeap*)calloc(1, sizeof(struct BinomHeap));
    if (!Heap) return NULL;

    Heap->head = NULL;

    return Heap;
}

static struct Node* Node_ctr(int value) {
    struct Node* node = (struct Node*)calloc(1, sizeof(struct Node));
    if (!node) return NULL;

    node->value = value;
    node->parent = NULL;
    node->child = NULL;
    node->next = NULL;
    node->degree = 1;

    return node;
}

static void link_binomial(struct Node* node1, struct Node* node2) {
    assert(node1->degree == node2->degree);

    node1->parent = node2;
    node1->next = node2->child;
    node2->child = node1;
    ++node2->degree;
} 

static struct BinomHeap* merge(struct BinomHeap* Heap1, struct BinomHeap* Heap2) {
    if (Heap1 == NULL)
        return Heap2;
    if (Heap2 == NULL)
        return Heap1;
    
    struct BinomHeap* Heap = BinomHeap_ctr();
    Heap->head = Node_ctr(0);
    
    struct Node* curH = Heap->head;
    struct Node* curH1 = Heap1->head;
    struct Node* curH2 = Heap2->head;

    while (curH1 && curH2) {                    // сливаем корневые списки в один, по возрастанию степеней
        if (curH1->degree < curH2->degree) {
            curH->next = curH1;
            curH1 = curH1->next;
        }
        else {
            curH->next = curH2;
            curH2 = curH2->next;
        }
        curH = curH->next;
    }

    while (curH1) {
        curH->next = curH1;
        curH1 = curH1->next;
        curH = curH->next;
    }

    while (curH2) {
        curH->next = curH2;
        curH2 = curH2->next;
        curH = curH->next;
    }

    Heap->head = Heap->head->next;
    curH = Heap->head;
    struct Node* prev = NULL;

    while (curH && curH->next) {
        struct Node* next = curH->next;
        if (curH->degree != next->degree || (next->next && next->next->degree == curH->degree)) {
            prev = curH;
            curH = next;
        } else if (curH->value < next->value) {
            curH->next = next->next;
            link_binomial(next, curH);
        } else {
            if (prev == NULL) {
                Heap->head = next;
            } else {
                prev->next = next;
            }
            link_binomial(curH, next);
            curH = next;
        }
        next = curH->next;
    }

    return Heap;
}

static struct BinomHeap* build_binom_heap(int* arr, int cnt) {
    struct BinomHeap* Heap = BinomHeap_ctr();

    for (int i = 0; i < cnt; ++i) {
        struct BinomHeap* ElemHeap = BinomHeap_ctr();
        ElemHeap->head = Node_ctr(arr[i]);

        Heap = merge(Heap, ElemHeap);
    }

    return Heap;
}

static struct Node* extract_min(struct BinomHeap** Heap) {
    int min = 2147483647;
    struct Node* curMin = NULL;
    struct Node* beforeMin = NULL;
    struct Node* cur = (*Heap)->head;
    struct Node* before = NULL;

    while (cur) {
        if (cur->value <= min) {            // ищем минимального и предыдущего
            min = cur->value;
            curMin = cur;
            beforeMin = before;
        }
        before = cur;
        cur = cur->next;
    }

    if (!beforeMin)                         // исправили список корней
        (*Heap)->head = curMin->next;
    else
        beforeMin->next = curMin->next;
    
    struct BinomHeap* ChildHeap = BinomHeap_ctr();
    cur = curMin->child;
    ChildHeap->head = curMin->child;
    while (cur != NULL) {
        cur->parent = NULL;
        cur = cur->next;
    }
    *Heap = merge(*Heap, ChildHeap);
    return curMin;
}

static int check_binom_heap(struct BinomHeap* Heap, int cnt) {
    int last = -1;
    for (int i = 0; i < cnt; ++i) {
        struct Node* min_node = extract_min(&Heap);
        if (min_node->value < last)
            return 0;

        last = min_node->value;
    }
    return 1;
}

#endif