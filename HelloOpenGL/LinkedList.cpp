#include "LinkedList.h"
// note, most functions here are not used in the final project, however I think it's good to keep them included in the case I expand this simulation for portfolio purposes.
LinkedList::LinkedList()
{

}
LinkedList::~LinkedList()
{

}
/// <summary>
/// makes node and puts it at end of list.
/// </summary>
/// <param name="head"></param>
/// <param name="object"></param>
/// <returns></returns>
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
/// <summary>
/// creates node and puts it at start of the list
/// </summary>
/// <param name="head"></param>
/// <param name="object"></param>
/// <returns></returns>
ListNode* LinkedList::InsertFirst(ListNode** head, SceneObject* object)
{
	ListNode* NewNode = new ListNode();
	NewNode->data = object;
	NewNode->next = *head;
	*head = NewNode;
	return NewNode;
}
/// <summary>
/// makes a new node and inserts it after a given node
/// </summary>
/// <param name="lastnode"></param>
/// <param name="object"></param>
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
/// <summary>
///traverses list and deletes everything
/// </summary>
/// <param name="node"></param>
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
/// <summary>
/// deletes node after given node.
/// </summary>
/// <param name="node"></param>
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
/// <summary>
/// traverses list until gets to given position
/// </summary>
/// <param name="pos"></param>
/// <returns></returns>
ListNode* LinkedList::GetNode(int pos)
{
	int count = 0;
	ListNode* node = head;
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
/// <summary>
/// pass in object, finds node with that object in it
/// </summary>
/// <param name="node"></param>
/// <param name="object"></param>
/// <returns></returns>
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
/// <summary>
/// deletes node that is passed in via function
/// </summary>
/// <param name="node"></param>
/// <param name="pos"></param>
/// <returns></returns>
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


