#include<iostream>
#include <math.h>

using namespace std;

struct node {
	node* parent; // указатель на родительский узел
	node* child; // указатель на один из дочерних узлов
	node* left; // указатель на левый узел того же предка
	node* right; // указатель на правый узел того же предка
	int key; // ключ
	int degree; // Степень узла
	char mark; // Отметка узла
	char c; // Флаг для помощи в функции поиска узла
};
 
struct node* mini = NULL; //Создание указателя на мин значение
int size = 0; //Объявить целое число для количества узлов в куче
 
void insertion(int val) //Функция для вставки числа в кучу
{
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	new_node->key = val;
	new_node->parent = NULL;
	new_node->child = NULL;
	new_node->left = new_node;
	new_node->right = new_node;
	if (mini != NULL) {
		(mini->left)->right = new_node;
		new_node->right = mini;
		new_node->left = mini->left;
		mini->left = new_node;
	if (new_node->key < mini->key)
		mini = new_node;
	} else {
		mini = new_node;
	}
	size++;
}
 
void Fibonnaci_link(struct node* ptr2, struct node* ptr1) //настройка связи между родителем и дочерним узл.
{
	(ptr2->left)->right = ptr2->right;
	(ptr2->right)->left = ptr2->left;
	if (ptr1->right == ptr1)
		mini = ptr1;
	ptr2->left = ptr2;
	ptr2->right = ptr2;
	ptr2->parent = ptr1;
	if (ptr1->child == NULL)
		ptr1->child = ptr2;
	ptr2->right = ptr1->child;
	ptr2->left = (ptr1->child)->left;
	((ptr1->child)->left)->right = ptr2;
	(ptr1->child)->left = ptr2;
	if (ptr2->key < (ptr1->child)->key)
		ptr1->child = ptr2;
	ptr1->degree++;
}

void Consolidate() //Объединение кучи
{
	int temp1;
	float temp2 = (log(size)) / (log(2));
	int temp3 = temp2;
	struct node* arr[temp3];
	for (int i = 0; i <= temp3; i++)
		arr[i] = NULL;
	node* ptr1 = mini;
	node* ptr2;
	node* ptr3;
	node* ptr4 = ptr1;
	do {
		ptr4 = ptr4->right;
		temp1 = ptr1->degree;
		while (arr[temp1] != NULL) {
			ptr2 = arr[temp1];
			if (ptr1->key > ptr2->key) {
				ptr3 = ptr1;
				ptr1 = ptr2;
				ptr2 = ptr3;
			}
			if (ptr2 == mini)
				mini = ptr1;
			Fibonnaci_link(ptr2, ptr1);
			if (ptr1->right == ptr1)
				mini = ptr1;
			arr[temp1] = NULL;
			temp1++;
		}
		arr[temp1] = ptr1;
		ptr1 = ptr1->right;
	} while (ptr1 != mini);
	mini = NULL;
	for (int j = 0; j <= temp3; j++) {
		if (arr[j] != NULL) {
			arr[j]->left = arr[j];
			arr[j]->right = arr[j];
			if (mini != NULL) {
				(mini->left)->right = arr[j];
				arr[j]->right = mini;
				arr[j]->left = mini->left;
				mini->left = arr[j];
				if (arr[j]->key < mini->key)
					mini = arr[j];
			} else {
				mini = arr[j];
			}
			if (mini == NULL)
				mini = arr[j];
			else if (arr[j]->key < mini->key)
				mini = arr[j];
		}
	}
}
 
void Extract_min() //Функция для извлечения минимального узла в куче
{
	if (mini == NULL)
		cout << "The heap is empty" << endl;
	else {
		node* temp = mini;
		node* pntr;
		pntr = temp;
		node* x = NULL;
		if (temp->child != NULL) {
			x = temp->child;
			do {
				pntr = x->right;
				(mini->left)->right = x;
				x->right = mini;
				x->left = mini->left;
				mini->left = x;
				if (x->key < mini->key)
					mini = x;
				x->parent = NULL;
				x = pntr;
			} while (pntr != temp->child);
		}
		(temp->left)->right = temp->right;
		(temp->right)->left = temp->left;
		mini = temp->right;
		if (temp == temp->right && temp->child == NULL)
			mini = NULL;
		else {
			mini = temp->right;
			Consolidate();
		}
		size--;
	}
}

void display(struct node* mini) //Показывает всю кучу
{
	node* ptr = mini;
	if (ptr == NULL)
		cout << "The Heap is Empty" << endl; 
	else {
		cout << "The root nodes of Heap are: " << endl;
		do {
			cout << ptr->key;
			ptr = ptr->right;
			if (ptr != mini) {
				cout << "-->";
			}
		} while (ptr != mini && ptr->right != NULL);
		cout << endl << "The heap has " << size << " nodes" << endl;
	}
}

int find_min(struct node* mini) //Функция для поиска минимального узла в куче
{
	cout << "min of heap is: " << mini->key << endl;
}

int interview(void) {
	int answer;
	int number;
	string bas[7] = {"What do you want?", "1)Add", "2)Find min", "3)Delete min " ,"4)Show all", "5)Exit"};
	for (int i = 0; i < 7; i++) {
		cout << bas[i] << endl;
        }
	cin >> answer;
	switch (answer)
	{
		case 1: 
			cout << "What number do you want to add?" << endl;
			cin >> number;
			insertion(number);
			break;
		
		case 2:
			find_min(mini);
			break;

		case 3:
			Extract_min();
			break;
		case 5:
			cout << "Goodbye))" << endl;
			return 0;

		case 4:
			display(mini);
			break;
	}
}

int main()
{
	while (1) {
		if (interview() == 0){ 
			return 0;}
	}
}
