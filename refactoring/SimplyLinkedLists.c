#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Использовать stdlib.h для malloc, free, и exit

// Структура списка
typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

// Функция для создания связанного списка размером 'n'
ListNode* createList(int n) {
    ListNode* head = NULL;
    ListNode* tail = NULL;

    for (int i = 1; i <= n; i++) {
        ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
        if (newNode == NULL) {
            perror("Не удалось выделить память.");
            ListNode* current = head;
            while (current != NULL) {
                ListNode* next = current->next;
                free(current);
                current = next;
            }
            exit(EXIT_FAILURE); // Закрытие программы, если не удастся выделить память
        }
        newNode->data = i;
        newNode->next = NULL;

        if (head == NULL) {
            // Первый узел
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

// Функция для отображения связанного списка
void displayList(ListNode* head) {
    ListNode* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Функция для вставки нового элемента в заданную позицию
ListNode* insertNode(ListNode* head, int data, int position) {
    if (position <= 0) {
        fprintf(stderr, "Недопустимое положение для вставки.\n");
        return head;
    }

    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        perror("Не удалось выделить память.");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;

    if (position == 1) {
        // Вставка в начало
        newNode->next = head;
        return newNode; // Новый корень списка
    }
    else {
        ListNode* current = head;
        for (int i = 1; i < position - 1 && current != NULL; i++) {
            current = current->next;
        }

        if (current == NULL) {
            fprintf(stderr, "Расположение за пределами списка. Элемент вставляется в конце.\n");
            // Вставка в конец
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

// Функция для удаления элемента в заданном месте
ListNode* deleteNode(ListNode* head, int position) {
    if (head == NULL) {
        return NULL; // Пустой список
    }

    if (position <= 0) {
        fprintf(stderr, "Недопустимая позиция для удаления.\n");
        return head;
    }

    if (position == 1) {
        // Удаление корневого узела
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
            fprintf(stderr, "Позиция за пределами списка. Удаление невозможно.\n");
            return head;
        }
        
        prev->next = current->next;
        free(current);
        return head;
    }
}

// Функция, позволяющая поменять местами два элемента в списке по их позициям
ListNode* swapNodes(ListNode* head, int pos1, int pos2) {
    if (head == NULL || pos1 <= 0 || pos2 <= 0 || pos1 == pos2) {
        return head; // Неверный ввод значений
    }

    // Убедиться, что позиция pos1 всегда является меньшей позицией
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
        fprintf(stderr, "Одна или обе позиции находятся за пределами допустимого диапазона. Перемещение невозможно.\n");
        return head;
    }

    // Настройка указателей
    if (prev1 != NULL) {
        prev1->next = curr2;
    }
    else {
        head = curr2; // Если pos1 равно 1, обновите head
    }

    if (prev2 != NULL) {
        prev2->next = curr1;
    }
    else {
        head = curr1; // Если pos2 равно 1, обновите head
    }

    // Меняем местами следующие указатели
    ListNode* temp = curr1->next;
    curr1->next = curr2->next;
    curr2->next = temp;

    return head;
}

// Функция для удаления всего связанного списка и освобождения памяти
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
    if (n <= 0) { // проверка на корректность значения
        printf("Введённое кол-во элементов списка неверно!");
        return(-1);
    }

    ListNode* list = createList(n);
    printf("Исходный список: ");
    displayList(list);

    int insertPosition = 3;
    int insertValue = 28;
    list = insertNode(list, insertValue, insertPosition);
    printf("Список после вставки элемента: ");
    displayList(list);

    int deletePosition = 7;
    list = deleteNode(list, deletePosition);
    printf("Список после удаления элемента: ");
    displayList(list);

    int swapPos1 = 4;
    int swapPos2 = 5;
    list = swapNodes(list, swapPos1, swapPos2);
    printf("Список после замены элементов %d и %d местами: ", swapPos1, swapPos2);
    displayList(list);

    deleteList(list); // Освобождение выделенной памяти
    
    return 0;
}