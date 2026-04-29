#include "LinkedList.h"
LinkedList::LinkedList()
{

}
LinkedList::~LinkedList()
{

}
ListNode* LinkedList::MakeNode(ListNode** head, SceneObject* object)
{
	ListNode* NewNode = new ListNode();
	ListNode* last = *head;
	NewNode->data = object;
	NewNode->next = nullptr;
	if (*head == nullptr)
	{
		*head = NewNode;
		return NewNode;
	}
	while (last->next != nullptr)
	{
		last = last->next;
	}
	last->next = NewNode;
	return NewNode;

}
ListNode* LinkedList::InsertFirst(ListNode** head, SceneObject* object)
{
	ListNode* NewNode = new ListNode();
	NewNode->data = object;
	NewNode->next = *head;
	*head = NewNode;
	return NewNode;
}
void LinkedList::InsertAfter(ListNode* lastnode, SceneObject* object)
{
	if (lastnode == nullptr)
	{
		std::cout << "lastnode cannot be null";
		return;
	}
	ListNode* NewNode = new ListNode();
	NewNode->data = object;
	NewNode->next = lastnode->next;
	lastnode->next = NewNode;
}
void LinkedList::Deletelist(ListNode** node)
{
	ListNode* ptemp = *node;
	ListNode* next;
	while (ptemp != nullptr)
	{
		next = ptemp->next;
		delete ptemp;
		ptemp = next;
	}
	*node = nullptr;
}
void LinkedList::DeleteAfter(ListNode* node)
{
	ListNode* ptemp;
	if (node != nullptr && node->next != nullptr)
	{
		ptemp = node->next;
		node->next = ptemp->next;
		delete ptemp;
	}
}
ListNode* LinkedList::GetNode(int pos)
{
	int count = 0;
	ListNode* node = nullptr;
	while (node != nullptr)
	{
		if (count == pos)
		{
			return node;
		}
		count++;
		node = node->next;
	}
	return nullptr;
}
ListNode* LinkedList::Find(ListNode* node, SceneObject* object)
{
	while (node != nullptr)
	{
		if (object == node->data)
		{
			return node;
		}
		node = node->next;
	}
	return nullptr;
}
ListNode* LinkedList::DeleteNode(ListNode* node, int pos)
{
	int count = 0;
	ListNode* ptemp;
	while (node != nullptr)
	{
		if (count == (pos - 1))
		{
			ptemp = node->next;
			node->next = ptemp->next;
			delete ptemp;
		}
		count++;
		node = node->next;
	}
	return nullptr;

}


