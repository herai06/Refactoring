#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct ListValues
{
    int a;
    struct ListValues* next;
};
typedef struct ListValues List;

List* creatingList(int n)
{
    List* list = malloc(sizeof(List));
    list->a = 1;
    list->next = NULL;
    List* p, * q;
    p = list;
    for (size_t i = 0; i < n - 1; i++)
    {
        q = malloc(sizeof(List));
        q->a = p->a + 1;
        p->next = q;
        p = q;
    }
    p->next = NULL;
    return list;
}

void show(List* list)
{
    while (list)
    {
        printf("%d ", list->a);
        list = list->next;
    }
    printf("\n");
}

List* insertNewEl(List* list, List item, int number)
{
    List* lst = malloc(sizeof(List));
    lst->a = item.a;
    if (number == 1)
    {
        lst->next = list;
        list = lst;
    }
    else
    {
        List* newList = list;
        for (size_t i = 2; i < number; i++)
        {
            list = list->next;
            if (!(list->next))
                break;
        }
        List* nextEl = list->next;
        list->next = lst;
        lst->next = nextEl;
        list = newList;
    }
    return list;
}

List* deleteEl(List* list, int number)
{
    if (number <= 1)
    {
        List* newList = list->next;
        free(list);
        return newList;
    }
    else
    {
        List* newList = list;
        List* lst = list;
        for (int i = 1; i < number; i++)
        {
            if (list->next != NULL)
                list = list->next;
        }
        while (lst->next != list)
            lst = lst->next;
        lst->next = list->next;
        free(list);
        return newList;
    }
}

List* replacingEl(List* list, int num1, int num2)
{
    List* newList = list;
    List* list1 = malloc(1 * sizeof(List));
    List* list2 = malloc(1 * sizeof(List));
    List* prev1 = list;
    List* prev2 = list;
    List* next1, * next2;
    int n = 0;
    if (num1 == num2)
        return list;
    if (num2 < num1)
    {
        int buf = num1;
        num1 = num2;
        num2 = buf;
    }
    if (num1 <= 1)
    {
        list1 = list;
        prev1 = list1;
    }
    else
    {
        for (size_t i = 1; i < num1; i++)
        {
            if (list->next != NULL)
            {
                list = list->next;
                n++;
            }
            else
                break;
        }
        list1 = list;
        if (prev1 == list1)
            prev1 = NULL;
        else
        {
            while (prev1->next != list1)
                prev1 = prev1->next;
        }
    }
    for (size_t i = n; i < num2 - 1; i++)
    {
        if (list->next != NULL)
            list = list->next;
        else
            break;
    }
    list2 = list;
    if (prev2 == list2)
        prev2 = NULL;
    else
    {
        while (prev2->next != list2)
            prev2 = prev2->next;
    }
    next1 = list1->next;
    next2 = list2->next;
    if (list2 == next1)
    {
        list2->next = list1;
        list1->next = next2;
        if (list1 != newList)
            prev1->next = list2;
    }
    else
    {
        if (list1 != newList)
            prev1->next = list2;
        list2->next = next1;
        if (list2 != newList)
            prev2->next = list1;
        list1->next = next2;
    }
    if (list1 == newList)
        return list2;
    if (list2 == newList)
        return list1;
    return newList;
}

List* deleteList(List* list)
{
    while (list->next != NULL)
    {
        List* lst = list;
        list = list->next;
        free(lst);
    }
    free(list);
}

int main()
{
    system("chcp 1251>nul");
    int n = 10;
    List* list = creatingList(n);
    show(list);
    int number = 3, value = 28;
    List item = { value, NULL };
    list = insertNewEl(list, item, number);
    show(list);
    number = 7;
    list = deleteEl(list, number);
    show(list);
    list = replacingEl(list, 4, 5);
    show(list);
    list = deleteList(list);
    show(list);
}