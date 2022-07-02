#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

FILE *in;
FILE *out;


typedef struct Node{
    int data;
    struct Node* next;
} Node;


typedef struct Kingdom {
    int kingdomNumber;
    int numMonsters;
    int kill;
    int numSave;
    Node* node;
    Node* head;
} Kingdom;

typedef struct KingdomIndex {
    int key;
    int data;
} KingdomIndex;



Node* add(Node* last, int data) {
    Node* newNode = malloc(sizeof(Node));

    // If the list is currently NULL
    if (last == NULL) {
        // Populate the node
        newNode->data = data;
        // Set the new node as the last node
        last = newNode;
        last->next = last;
        return last;
    }

    // Populate the node with the data to be inserted
    newNode->data = data;
    // Connect newNode to the next node from the original last node
    newNode->next = last->next;
    // Connect the original last node to newNode
    last->next = newNode;
    // Set the newNode as the last node
    last = newNode;
    return last;
}

void traverse(struct Node* last) {
  struct Node* p = last;

  if (last == NULL) {
  printf("The list is empty");
  return;
  }

  p = last->next;

  do {
    printf("%d ", p->data);
    p = p->next;

  } while (p != last->next);
}



Node* reverse(Node* last) {
    
    Node* prev = NULL;
    

    Node* cur = last;
    Node* next;
    
    do {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    } while(cur != last);

    last->next = prev;
    last = prev;

    return last;
}

void SortByNumber (Kingdom* kingdom, int n) {
    int i, j;
    Kingdom temp;

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (kingdom[i].kingdomNumber > kingdom[j].kingdomNumber){
                temp = kingdom[i];
                kingdom[i] = kingdom[j];
                kingdom[j] = temp;
            }
        }
    }
}


void SortBySequence (Kingdom* kingdom, int n) {
    int i, j;
    Kingdom temp;

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (kingdom[i].node->data == kingdom[j].node->data) {
                if (kingdom[i].kingdomNumber > kingdom[j].kingdomNumber){
                    temp = kingdom[i];
                    kingdom[i] = kingdom[j];
                    kingdom[j] = temp;
                }
            }

            else if (kingdom[i].node->data < kingdom[j].node->data){
                temp = kingdom[i];
                kingdom[i] = kingdom[j];
                kingdom[j] = temp;
            }
        }
    }
}


Node* traverse_k(Node* cur, int k) {
    int i;
    for (i = 1; i < k; i++) {
        cur = cur->next;
    }

    return cur;
}

/* Function to delete a given node from the list */
Node* deleteNode(struct Node* head, int key)
{
    if (head == NULL)
        return NULL;
  
    // Find the required node
    struct Node *curr = head, *prev;
    while (curr->data != key) 
    {
        if (curr->next == head)
        {
            printf("\nGiven node is not found"
                   " in the list!!!");
            break;
        }
  
        prev = curr;
        curr = curr->next;
    }
  
    // Check if node is only node
    if (curr->next == head) 
    {
        head = NULL;
        free(curr);
        return NULL;
    }
  
    // If more than one node, check if
    // it is first node
    if (curr == head) 
    {
        prev = head;
        while (prev->next != head)
            prev = prev->next;
        head = curr->next;
        prev->next = head;
        free(curr);
    }
  
    // check if node is last node
    else if (curr->next == head && curr == head) 
    {
        prev->next = head;
        free(curr);
    }
    else 
    {
        prev->next = curr->next;
        free(curr);
    }

    return head;
}



void printList(struct Node *head)
{
    struct Node *temp = head;
    if (head != NULL)
    {
        do
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        while (temp != head);
    }
}


int main() {
    in = fopen("in.txt", "r");
    
    if(in == NULL) {
        printf("File not found");
        exit(1);
    }


    int i, j;
    int numKingdoms;
    fscanf(in, "%d", &numKingdoms);

    Kingdom* kingdom = malloc(numKingdoms * sizeof(Kingdom));
    for (i = 0; i < numKingdoms; i++){
        int kingdomNumber;
        int numMonsters;
        int kill;
        int numSave;


        fscanf(in, "%d %d %d %d", &kingdomNumber, &numMonsters, &kill, &numSave);
        kingdom[i].kingdomNumber = kingdomNumber;
        kingdom[i].numMonsters = numMonsters;
        kingdom[i].kill = kill;
        kingdom[i].numSave = numSave;



        //printf("%d %d %d %d\n", kingdomNumber, numMonsters, kill, numSave);

        // Inserting to Node
        kingdom[i].node = NULL;
        for (j = numMonsters; j > 0; j--){
            kingdom[i].node = add(kingdom[i].node, j);
            if (j == numMonsters) kingdom[i].head = kingdom[i].node;
        }
    }

    // Sort by kingdom number
    SortByNumber(kingdom, numKingdoms);
    printf("Initial nonempty lists status\n");
    for (i = 0; i < numKingdoms; i++){
        printf("%d ", kingdom[i].kingdomNumber);
        traverse(kingdom[i].node);
        printf("\n");
    }

    // Sort each kingdom in increasing order by reversing it
    printf("\nAfter ordering nonempty lists status\n");
    for (i = 0; i < numKingdoms; i++){
        printf("%d ", kingdom[i].kingdomNumber);

        kingdom[i].node = reverse(kingdom[i].head);

        printList(kingdom[i].node);
        printf("\n");
    }

    printf("\nPhase1 execution\n\n");
    int totalSaved = 0;
    for (i = 0; i < numKingdoms; i++){
        int index = kingdom[i].kill;
        int save = kingdom[i].numSave;
        int numKill = kingdom[i].numMonsters - save;

        printf("Line# %d\n", kingdom[i].kingdomNumber);
        Node* cur = kingdom[i].node;
        for (j = 0; j < numKill; j++) {
            cur = traverse_k(cur, index);
            int killNode = cur->data;
            cur = deleteNode(cur, cur->data);

            printf("Monster# %d executed\n", killNode);
        }
        printf("\n");
        kingdom[i].node = cur;
        kingdom[i].numMonsters = save;
        totalSaved = totalSaved + save;
    }

    SortBySequence(kingdom, numKingdoms);
    for (i = 0; i < numKingdoms; i++) {
        

        while (kingdom[i].node != NULL)
        {
            if (totalSaved == 1) {
                printf("\nMonster %d from line %d will survive\n", kingdom[i].node->data, kingdom[i].kingdomNumber);
                break;
            }
            kingdom[i].node = traverse_k(kingdom[i].node, 1);
            int killNode = kingdom[i].node->data;
            kingdom[i].node = deleteNode(kingdom[i].node, kingdom[i].node->data);
            printf("Executed Monster %d from line %d\n", killNode, kingdom[i].kingdomNumber);

            totalSaved--;
        }
    }

}