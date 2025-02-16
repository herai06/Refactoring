#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // ������������ stdlib.h ��� malloc, free, � exit

// ��������� ������
typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

// ������� ��� �������� ���������� ������ �������� 'n'
ListNode* createList(int n) {
    ListNode* head = NULL;
    ListNode* tail = NULL;

    for (int i = 1; i <= n; i++) {
        ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
        if (newNode == NULL) {
            perror("�� ������� �������� ������.");
            ListNode* current = head;
            while (current != NULL) {
                ListNode* next = current->next;
                free(current);
                current = next;
            }
            exit(EXIT_FAILURE); // �������� ���������, ���� �� ������� �������� ������
        }
        newNode->data = i;
        newNode->next = NULL;

        if (head == NULL) {
            // ������ ����
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

// ������� ��� ����������� ���������� ������
void displayList(ListNode* head) {
    ListNode* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// ������� ��� ������� ������ �������� � �������� �������
ListNode* insertNode(ListNode* head, int data, int position) {
    if (position <= 0) {
        fprintf(stderr, "������������ ��������� ��� �������.\n");
        return head;
    }

    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        perror("�� ������� �������� ������.");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;

    if (position == 1) {
        // ������� � ������
        newNode->next = head;
        return newNode; // ����� ������ ������
    }
    else {
        ListNode* current = head;
        for (int i = 1; i < position - 1 && current != NULL; i++) {
            current = current->next;
        }

        if (current == NULL) {
            fprintf(stderr, "������������ �� ��������� ������. ������� ����������� � �����.\n");
            // ������� � �����
            ListNode* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = NULL;
            return head;
        }

        newNode->next = current->next;
        current->next = newNode;
        return head;
    }
}

// ������� ��� �������� �������� � �������� �����
ListNode* deleteNode(ListNode* head, int position) {
    if (head == NULL) {
        return NULL; // ������ ������
    }

    if (position <= 0) {
        fprintf(stderr, "������������ ������� ��� ��������.\n");
        return head;
    }

    if (position == 1) {
        // �������� ��������� �����
        ListNode* newHead = head->next;
        free(head);
        return newHead;
    }
    else {
        ListNode* current = head;
        ListNode* prev = NULL;

        for (int i = 1; i < position && current != NULL; i++) {
            prev = current;
            current = current->next;
        }

        if (current == NULL) {
            fprintf(stderr, "������� �� ��������� ������. �������� ����������.\n");
            return head;
        }
        
        prev->next = current->next;
        free(current);
        return head;
    }
}

// �������, ����������� �������� ������� ��� �������� � ������ �� �� ��������
ListNode* swapNodes(ListNode* head, int pos1, int pos2) {
    if (head == NULL || pos1 <= 0 || pos2 <= 0 || pos1 == pos2) {
        return head; // �������� ���� ��������
    }

    // ���������, ��� ������� pos1 ������ �������� ������� ��������
    if (pos1 > pos2) {
        int temp = pos1;
        pos1 = pos2;
        pos2 = temp;
    }

    ListNode* prev1 = NULL;
    ListNode* curr1 = head;
    for (int i = 1; i < pos1 && curr1 != NULL; ++i) {
        prev1 = curr1;
        curr1 = curr1->next;
    }

    ListNode* prev2 = NULL;
    ListNode* curr2 = head;
    for (int i = 1; i < pos2 && curr2 != NULL; ++i) {
        prev2 = curr2;
        curr2 = curr2->next;
    }

    if (curr1 == NULL || curr2 == NULL) {
        fprintf(stderr, "���� ��� ��� ������� ��������� �� ��������� ����������� ���������. ����������� ����������.\n");
        return head;
    }

    // ��������� ����������
    if (prev1 != NULL) {
        prev1->next = curr2;
    }
    else {
        head = curr2; // ���� pos1 ����� 1, �������� head
    }

    if (prev2 != NULL) {
        prev2->next = curr1;
    }
    else {
        head = curr1; // ���� pos2 ����� 1, �������� head
    }

    // ������ ������� ��������� ���������
    ListNode* temp = curr1->next;
    curr1->next = curr2->next;
    curr2->next = temp;

    return head;
}

// ������� ��� �������� ����� ���������� ������ � ������������ ������
void deleteList(ListNode* head) {
    ListNode* current = head;
    while (current != NULL) {
        ListNode* next = current->next;
        free(current);
        current = next;
    }
}

int main()
{
    system("chcp 1251>nul");
    int n = 10;
    if (n <= 0) { // �������� �� ������������ ��������
        printf("�������� ���-�� ��������� ������ �������!");
        return(-1);
    }

    ListNode* list = createList(n);
    printf("�������� ������: ");
    displayList(list);

    int insertPosition = 3;
    int insertValue = 28;
    list = insertNode(list, insertValue, insertPosition);
    printf("������ ����� ������� ��������: ");
    displayList(list);

    int deletePosition = 7;
    list = deleteNode(list, deletePosition);
    printf("������ ����� �������� ��������: ");
    displayList(list);

    int swapPos1 = 4;
    int swapPos2 = 5;
    list = swapNodes(list, swapPos1, swapPos2);
    printf("������ ����� ������ ��������� %d � %d �������: ", swapPos1, swapPos2);
    displayList(list);

    deleteList(list); // ������������ ���������� ������
    
    return 0;
}