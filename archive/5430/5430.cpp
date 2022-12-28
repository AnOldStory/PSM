// not safe in memory

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  Node *next, *prev;
} AC;

AC* head;
AC* tail;

int T;           // test case
char P[400001];  // number of operations
int n;           // number of elements
int temp;
int direc;  // 0: left, 1: right

void printList() {
  printf("[");
  while (head != NULL) {
    printf("%d", head->data);
    if (direc == 1) {
      if (head->prev != NULL) printf(",");
      head = head->prev;
    } else {
      if (head->next != NULL) printf(",");
      head = head->next;
    }
  }
  printf("]\n");
}

int main() {
  scanf("%d", &T);

  for (int i = 0; i < T; i++) {
    int flag = 1;
    direc = 0;
    scanf(" %s", P);
    scanf(" %d", &n);
    scanf(" [");
    for (int j = 0; j < n; j++) {
      scanf(" %d", &temp);
      if (j != n - 1) scanf(" ,");

      AC* tempN = (AC*)malloc(sizeof(AC));
      tempN->data = temp;
      tempN->prev = tail;
      if (head == NULL) {
        head = tempN;
        tail = tempN;
      } else {
        tail->next = tempN;
        tail = tempN;
      }
    }
    scanf("]");
    // parse end
    for (int j = 0; j < 100000; j++) {
      if (P[j] == '\0') break;
      if (P[j] == 'R') {
        AC* tempN = head;
        head = tail;
        tail = tempN;
        direc = (direc + 1) % 2;  // switch direction
      } else if (P[j] == 'D') {
        if (head == NULL) {
          printf("error\n");
          flag = 0;
          break;
        } else {
          if (direc == 1) {
            if (head->prev != NULL) {
              head->prev->next = NULL;
              head = head->prev;
            } else {
              head = NULL;
            }
          } else {
            if (head->next != NULL) {
              head->next->prev = NULL;
              head = head->next;
            } else {
              head = NULL;
            }
          }
        }
      }
    }

    if (flag) printList();
    head = NULL;
    tail = NULL;
  }
}
