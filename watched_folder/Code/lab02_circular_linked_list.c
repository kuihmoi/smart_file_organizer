/*
 * ============================================================
 *  Lab Practice 02 — Circular Linked List
 *  Date : April 2026
 * ============================================================
 *
 *  HOW TO COMPILE & RUN
 *  --------------------
 *  gcc -Wall -o lab02 lab02_circular_linked_list.c
 *  ./lab02
 *
 *  RULES
 *  -----
 *  - Complete every TODO before moving to the next question.
 *  - Do NOT change any function signature.
 *  - Only add code where you see TODO / your code here.
 *  - You may add helper (static) functions inside a question's
 *    section if you need them.
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>

/* ============================================================
 *  SHARED NODE DEFINITION
 *  All questions use this same struct.
 * ============================================================ */
typedef struct Node {
    int data;
    struct Node *next;
} Node;

/* ------------------------------------------------------------
 *  Utility: allocate a new node.
 *  Hint: malloc(sizeof(Node)), set data, point next to itself.
 * ------------------------------------------------------------ */
Node *newNode(int data) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) { fprintf(stderr, "malloc failed\n"); exit(1); }
    n->data = data;
    n->next = n;   /* a single node is its own circle */
    return n;
}

/* Utility: print a circular list starting from 'head'.
   Head is the LAST node; head->next is the logical first.    */
void printList(Node *head) {
    if (!head) { printf("[empty]\n"); return; }
    Node *cur = head->next;   /* start from first node */
    do {
        printf("%d", cur->data);
        if (cur->next != head->next) printf(" -> ");
        cur = cur->next;
    } while (cur != head->next);
    printf("\n");
}

/* ===========================================================
 *  CONVENTION used throughout this file
 *  ---------
 *  'head' points to the LAST node of the circular list.
 *  'head->next' is therefore the FIRST node.
 *  This makes both end-insertions O(1).
 * =========================================================== */


/* ===========================================================
 *  QUESTION 1 — Basic Insert / Delete operations
 * =========================================================== */

/* ----- 1-i. Insert at the beginning ----------------------- */
/*
 * TODO: Create a new node and make it the first node.
 *
 * Hint: After inserting, head->next should be the new node,
 *       and the new node's next should be the old first node.
 *       'head' (last node) does NOT change.
 *       Special case: what if the list is empty?
 */
Node *insertBeginning(Node *head, int data) {
    Node *n = newNode(data);

    if (!head) {
        /* TODO: handle empty list */
        head = n;
        return head;
    }

    /* TODO: link n between head and head->next */
    n->next = head->next;
    head->next = n;

    return head;
}

/* ----- 1-ii. Insert between two nodes --------------------- */
/*
 * TODO: Find the node with value 'after' and insert 'data'
 *       immediately after it.
 *
 * Hint: Traverse with a do-while so you visit every node once.
 *       If 'after' is not found, just print a warning and return.
 */
Node *insertAfter(Node *head, int after, int data) {
    if (!head) return insertBeginning(head, data);

    Node *cur = head->next;   /* start at first node */

    /* TODO: walk the list until cur->data == after
             (or you come full circle)               */
    do {
        if (cur->data == after) {
            Node *n = newNode(data);
            n->next = cur->next;
            cur->next = n;

            if (cur == head) {
                head = n;
            }

            return head;
        }
        cur = cur->next;
    } while (cur != head->next);

    /* TODO: once found, splice new node in */
    printf("Value %d not found.\n", after);
    return head;
}

/* ----- 1-iii. Insert at the end --------------------------- */
/*
 * TODO: Create a new node and make it the last node.
 *
 * Hint: The new node becomes the new 'head' (last node).
 *       Its next must point back to the first node.
 *       Special case: empty list?
 */
Node *insertEnd(Node *head, int data) {
    Node *n = newNode(data);

    if (!head) {
        /* TODO: handle empty list */
        head = n;
        return head;
    }

    /* TODO: link n after current head, then return n as new head */
    n->next = head->next;
    head->next = n;
    head = n;

    return head;
}

/* ----- 1-iv. Delete at the beginning ---------------------- */
/*
 * TODO: Remove the first node (head->next).
 *
 * Hint: Save head->next in a temp pointer, update head->next
 *       to skip it, then free the temp node.
 *       Special case: only one node in the list?
 */
Node *deleteBeginning(Node *head) {
    if (!head) { printf("List is empty.\n"); return NULL; }

    /* TODO: handle single-node case */
    if (head->next == head) {
        free(head);
        return NULL;
    }

    /* TODO: general case — unlink first node and free it */
    Node* temp = head->next;
    head->next = temp->next;
    free(temp);

    return head;
}

/* ----- 1-v. Delete between two nodes ---------------------- */
/*
 * TODO: Find the node with value 'target' and remove it.
 *
 * Hint: You need a pointer to the node BEFORE 'target'.
 *       Keep a 'prev' pointer while traversing.
 */
Node *deleteNode(Node *head, int target) {
    if (!head) { printf("List is empty.\n"); return NULL; }

    Node *prev = head;
    Node *cur  = head->next;

    /* TODO: traverse to find target; track prev */
    do {
        if (cur->data == target) {
            if (cur == prev) {
                free(cur);   /* only one node is in the list */
                return NULL;
            }

            prev->next = cur->next;
            if (cur == head) head = prev;
            free(cur);
            return head;
        }
        prev = cur;
        cur = cur->next;
    } while (cur != head->next);

    /* TODO: unlink cur and free it */
    /*       Don't forget: if cur == head, update head */
    printf("Value %d not found.\n", target);

    return head;
}

/* ----- 1-vi. Delete at the end ---------------------------- */
/*
 * TODO: Remove the last node (head itself).
 *
 * Hint: Traverse to find the node just before head,
 *       make it the new head, update its next.
 *       Special case: single node?
 */
Node *deleteEnd(Node *head) {
    if (!head) { printf("List is empty.\n"); return NULL; }

    /* TODO: handle single-node list */
    if (head->next == head) {
        free(head);
        return NULL;
    }

    /* TODO: find second-to-last node, unlink head, return new head */
    Node* cur = head->next;
    while (cur->next != head) {
        cur = cur->next;
    }

    cur->next = head->next;
    free(head);
    head = cur;

    return head;
}

/* driver for Q1 */
void runQ1(void) {
    printf("\n===== Q1: Insert / Delete =====\n");
    Node *head = NULL;

    /* Build list: 10 -> 20 -> 30 */
    head = insertEnd(head, 10);
    head = insertEnd(head, 20);
    head = insertEnd(head, 30);
    printf("After insertEnd(10,20,30)    : "); printList(head);

    head = insertBeginning(head, 5);
    printf("After insertBeginning(5)     : "); printList(head);

    head = insertAfter(head, 20, 25);
    printf("After insertAfter(20,25)     : "); printList(head);

    head = deleteBeginning(head);
    printf("After deleteBeginning        : "); printList(head);

    head = deleteNode(head, 25);
    printf("After deleteNode(25)         : "); printList(head);

    head = deleteEnd(head);
    printf("After deleteEnd              : "); printList(head);

    /* TODO: free remaining nodes when done (optional cleanup) */
    while (head) head = deleteBeginning(head);
}


/* ===========================================================
 *  QUESTION 2 — Delete node with a specific value
 * ===========================================================
 *
 * TODO: Write deleteValue() — remove the FIRST node whose
 *       data equals 'value'.
 *
 * Hint: This is very similar to deleteNode() above.
 *       Can you reuse that function?  
 *       What should happen if the value doesn't exist?
 */
Node *deleteValue(Node *head, int value) {
    return deleteNode(head, value);
}

void runQ2(void) {
    printf("\n===== Q2: Delete by Value =====\n");
    Node *head = NULL;
    for (int i = 1; i <= 5; i++) head = insertEnd(head, i * 10);
    printf("Original  : "); printList(head);

    head = deleteValue(head, 30);
    printf("Delete 30 : "); printList(head);

    head = deleteValue(head, 10);
    printf("Delete 10 : "); printList(head);

    head = deleteValue(head, 99);  /* value not in list */
    printf("Delete 99 : "); printList(head);
}


/* ===========================================================
 *  QUESTION 3 — Split into two equal halves
 * ===========================================================
 *
 * TODO: Given a circular linked list, split it into two
 *       circular lists of equal length and store them in
 *       *h1 and *h2.
 *
 * Hint — two-pointer (slow/fast) approach:
 *   Move 'slow' one step at a time, 'fast' two steps.
 *   When 'fast' reaches the end, 'slow' is at the midpoint.
 *   Then carefully re-link the two halves into separate circles.
 *
 * Edge case: what if the list has an odd number of nodes?
 *            Put the extra node in the first half.
 */
void splitList(Node *head, Node **h1, Node **h2) {
    *h1 = NULL;
    *h2 = NULL;

    if (!head) return;

    /* TODO: use slow/fast pointers to find the midpoint */
    Node* first = head->next;

    /* TODO: cut the list into two circles */
    if (first == head) {
        *h1 = head;
        *h2 = NULL;
        return;
    }

    Node *slow = first;
    Node *fast = first;

    while (fast->next != first && fast->next->next != first) {
        slow = slow->next;
        fast = fast->next->next;
    }

    if (fast->next->next == first) {
        fast = fast->next;
    }

    *h1 = slow;
    *h2 = fast;

    Node* secondFirst = slow->next;

    slow->next = first;
    fast->next = secondFirst;
}

void runQ3(void) {
    printf("\n===== Q3: Split into Two Halves =====\n");
    Node *head = NULL;
    for (int i = 1; i <= 6; i++) head = insertEnd(head, i * 10);
    printf("Original : "); printList(head);

    Node *h1 = NULL, *h2 = NULL;
    splitList(head, &h1, &h2);
    printf("Half 1   : "); printList(h1);
    printf("Half 2   : "); printList(h2);
}


/* ===========================================================
 *  QUESTION 4 — Merge two sorted singly linked lists
 *               into one sorted circular linked list
 * ===========================================================
 *
 * Input : two singly linked lists (next of last node = NULL),
 *         both sorted in ascending order.
 * Output: one CIRCULAR linked list, sorted ascending.
 *
 * TODO: Implement mergeSortedToCircular().
 *
 * Hint — suggested approach:
 *   Step 1: Merge the two singly linked lists using the classic
 *           merge-sort merge (compare heads, pick smaller).
 *   Step 2: Walk the merged list to find its tail.
 *   Step 3: Point the tail's next back to the head to close
 *           the circle.
 *
 * Remember: the input nodes' 'next' fields already point to
 * the next node; you don't need to allocate new nodes.
 */
Node *mergeSortedToCircular(Node *a, Node *b) {
    /* TODO */
    if (!a && !b) return NULL;

    Node* mergedHead = NULL;
    Node* tail = NULL;

    while (a && b) {
        Node* pick;
        if (a->data <= b->data) {
            pick = a;
            a = a->next;
        }
        else {
            pick = b;
            b = b->next;
        }

        if (!mergedHead) {
            mergedHead = pick;
            tail = pick;
        }
        else {
            tail->next = pick;
            tail = pick;
        }
    }

    if (a) {
        if (!mergedHead) mergedHead = a;
        else tail->next = a;
    }
    else if (b) {
        if (!mergedHead) mergedHead = b;
        else tail->next = b;
    }

    tail = mergedHead;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    tail->next = mergedHead;
    return tail;   /* return last node for circular list convention */
}

/* Helper: build a sorted singly linked list (next of last = NULL) */
static Node *buildSingly(int arr[], int n) {
    if (n == 0) return NULL;
    Node *head = newNode(arr[0]);
    head->next = NULL;
    Node *tail = head;
    for (int i = 1; i < n; i++) {
        tail->next = newNode(arr[i]);
        tail->next->next = NULL;
        tail = tail->next;
    }
    return head;
}

void runQ4(void) {
    printf("\n===== Q4: Merge Two Sorted Lists -> Circular =====\n");
    int a[] = {1, 3, 5, 7};
    int b[] = {2, 4, 6, 8};
    Node *la = buildSingly(a, 4);
    Node *lb = buildSingly(b, 4);

    /* The merge result's 'head' should be the LAST node
       so printList() works correctly (head->next = first).   */
    Node *merged = mergeSortedToCircular(la, lb);
    printf("Merged : "); printList(merged);
}


/* ===========================================================
 *  QUESTION 5 — Verify whether a linked list is circular
 * ===========================================================
 *
 * TODO: Return 1 if the list is circular, 0 otherwise.
 *
 * Hint — Floyd's cycle detection (slow/fast pointers):
 *   Move slow by 1 step, fast by 2 steps each iteration.
 *   If they ever meet -> cycle exists.
 *   If fast reaches NULL -> not circular.
 *
 * Note: the function receives a raw Node* (could be NULL,
 *       a normal singly list, or a circular list).
 */
int isCircular(Node *head) {
    /* TODO */
    if (!head) return 0;

    Node* slow = head;
    Node* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) return 1;
    }
    return 0;
}

void runQ5(void) {
    printf("\n===== Q5: Is Circular? =====\n");

    /* Build a circular list */
    Node *circ = NULL;
    for (int i = 1; i <= 4; i++) circ = insertEnd(circ, i);

    /* Build a singly (non-circular) list */
    int arr[] = {1, 2, 3, 4};
    Node *singly = buildSingly(arr, 4);

    printf("Circular list  -> isCircular = %d (expected 1)\n",
           isCircular(circ->next));   /* pass first node */

    printf("Singly list    -> isCircular = %d (expected 0)\n",
           isCircular(singly));

    printf("NULL           -> isCircular = %d (expected 0)\n",
           isCircular(NULL));
}


/* ===========================================================
 *  QUESTION 6 — Josephus Problem
 * ===========================================================
 *
 * N people numbered 1..N stand in a circle.
 * Starting from person 1, count K people clockwise.
 * The K-th person is eliminated. Repeat from the next person.
 * Continue until one person remains.
 *
 * TODO: Implement josephus(n, k).
 *       Print the elimination order and the survivor.
 *
 * Hint — step by step:
 *   1. Build a circular linked list of N nodes (values 1..N).
 *   2. Start 'current' at node 1.
 *   3. In each round, advance (k-1) steps to reach the node
 *      just BEFORE the one to eliminate.
 *      (Why k-1? Because you delete current->next.)
 *   4. Print the eliminated node's data, then delete it.
 *   5. Repeat until only one node remains.
 *   6. Print the survivor.
 *
 * Example: N=7, K=3 -> elimination: 3 6 2 7 5 1, survivor: 4
 */
void josephus(int n, int k) {
    printf("\n===== Q6: Josephus Problem (N=%d, K=%d) =====\n", n, k);

    /* TODO: Step 1 — build circular list 1..n */
    /* Your code here */

    /* TODO: Steps 2-5 — simulate the counting and elimination */
    /* Your code here */

    /* TODO: Step 6 — print survivor */
    /* Your code here */

    if (n <= 0 || k <= 0) {
        printf("Invalid input.\n");
        return;
    }

    Node* head = NULL;
    for (int i = 1; i <= n; i++) {
        head = insertEnd(head, i);
    }

    Node* prev = head;        /* node before current */
    Node* current = head->next; /* person 1 */

    printf("Elimination order: ");
    while (current->next != current) {
        for (int count = 1; count < k; count++) {
            prev = current;
            current = current->next;
        }

        printf("%d ", current->data);
        prev->next = current->next;

        if (current == head) head = prev;

        free(current);
        current = prev->next;
    }

    printf("\nSurvivor: %d\n", current->data);
    free(current);
}

void runQ6(void) {
    josephus(7, 3);
    josephus(5, 2);  /* extra test case */
}


/* ===========================================================
 *  MAIN
 * =========================================================== */
int main(void) {
    runQ1();
    runQ2();
    runQ3();
    runQ4();
    runQ5();
    runQ6();
    return 0;
}
