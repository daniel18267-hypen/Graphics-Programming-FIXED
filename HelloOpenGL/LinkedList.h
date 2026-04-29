#pragma once
#include "Structures.h"
#include "SceneObject.h"
class LinkedList
{
public: 
	
	LinkedList();
	~LinkedList();
	ListNode* MakeNode(ListNode** head, SceneObject* object);
	ListNode* InsertFirst(ListNode** head, SceneObject* object);
	void InsertAfter(ListNode* lastnode, SceneObject* object);
	void Deletelist(ListNode** node);
	void DeleteAfter(ListNode* node);
	ListNode* GetNode(int pos);
	ListNode* DeleteNode(ListNode* node, int pos);
	ListNode* Find(ListNode* node, SceneObject* object);
	ListNode* head = new ListNode();
	ListNode* next = nullptr;

	

};

