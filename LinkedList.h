#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "List.h"
#include "LinkedListNode.h"
#include <iostream>

using namespace std;

template <class item_t>
class LinkedList : public List<item_t>
{
	protected:
		LinkedListNode<item_t>* head;
		LinkedListNode<item_t>* tail;
		int size;
	public:
		LinkedList();
		//An empty virtual destructor for the sake of inheritance
   		virtual ~LinkedList();
		virtual void pushBack(const item_t& item);
   		//Removes, but does not return, the last item
   		virtual void popBack();
   		//Returns a reference to the last item (does not remove it).
   		virtual const item_t& getBack() const;
   
   		//Pushes item to the front of the list
   		virtual void pushFront(const item_t& item);
   		//Removes, but does not return, the first item
   		virtual void popFront();
   		//Returns a reference to the first item (does not remove it).
   		virtual const item_t& getFront() const;

   		//Returns a reference to the item at the given index
   		virtual const item_t& getItem(int index) const;
   		//Sets the item at the given index
   		virtual void setItem(int index, const item_t& item);

   		//Inserts the given item at the given index
   		//(items at index or beyond shift up one position)
   		virtual void insert(int index, const item_t& item);
   		//Removes the item at the given index
   		//(items beyond index shift down one position)
   		virtual void remove(int index);

   		//Returns the number of items in the list
   		virtual int getSize() const;
   		//Returns true if the list is empty (false otherwise)
   		virtual bool isEmpty() const;
   		virtual void printall() const;

};
template <class item_t>
LinkedList<item_t>::LinkedList(){
	head=0;
	tail=head;
	size=0;
}
template <class item_t>
LinkedList<item_t>::~LinkedList(){
	for(int i =0; i<size;i++){
		LinkedListNode<item_t>* tmp = head;
		head=head->getNext();
		delete tmp;
	}
	delete head;
	head=0;
	tail=head;
	size=0;
}
template <class item_t>
void LinkedList<item_t>::pushBack(const item_t& item){
	LinkedListNode<item_t>* node = new LinkedListNode<item_t>(NULL,item);
	if(size==0){
		head=node;
		tail=node;
		tail->setNext(0);

	} else{
		tail->setNext(node);
		tail=node;
		tail->setNext(0);
	}
	size+=1;
}
template <class item_t>
void LinkedList<item_t>::popBack(){
	if(size==0){
		head=0;
		tail=0;
	} else if(size==1){
		delete head;
		head=0;
		tail=0;
		size=0;
	} else{
		LinkedListNode<item_t>* tmp=head;
		for(int i=0;i<size-2;i++){
			tmp = tmp->getNext();
		}
		tmp->setNext(0);
		delete tail;
		tail = tmp;
		size-=1;
	}
	
}
template <class item_t>
const item_t& LinkedList<item_t>::getBack() const{
	return tail->getItem();
}
template <class item_t>
void LinkedList<item_t>::pushFront(const item_t& item){
	LinkedListNode<item_t>* node = new LinkedListNode<item_t>(NULL,item);
	if(size==0){
		head=node;
		tail=node;
		tail->setNext(0);

	} else{
		node->setNext(head);
		head = node;
	}
	size+=1;
}
template <class item_t>
void LinkedList<item_t>::popFront(){
	if(size==1){
		delete head;
		head=0;
		tail=0;
		size=0;
	} else if(size==0){
		head=0;
		tail=0;
	} else{
		LinkedListNode<item_t>* tmp = head;
		head = head->getNext();
		delete tmp;
		size-=1;
	}
	
}
template <class item_t>
const item_t& LinkedList<item_t>::getFront() const{
	return head->getItem();
}
template <class item_t>
const item_t& LinkedList<item_t>::getItem(int index) const{
	LinkedListNode<item_t>* tmp=head;
	for(int i=0; i<index; i++){
		tmp=tmp->getNext();
	}
	return tmp->getItem();
}
template <class item_t>
void LinkedList<item_t>::setItem(int index, const item_t& item){
	LinkedListNode<item_t>* tmp=head;
	for(int i=0; i<index; i++){
		tmp=tmp->getNext();
	}
	tmp->setItem(item);


}
template <class item_t>
void LinkedList<item_t>::insert(int index, const item_t& item){
	if (index==0){
		this->pushFront(item);
	} else if(index==size){
		this->pushBack(item);
	} else{
		LinkedListNode<item_t>* node = new LinkedListNode<item_t>(NULL,item);
		LinkedListNode<item_t>* tmp=head;
		for(int i=0; i<index-1; i++){
			tmp=tmp->getNext();
		}
		node->setNext(tmp->getNext());
		tmp->setNext(node);
		size+=1;

	}
	
	

}
template <class item_t>
void LinkedList<item_t>::remove(int index){
	if(index==0){
		this->popFront();
	} else if(index==size-1){
		this->popBack();
	} else{
		LinkedListNode<item_t>* tmp=head;
		for(int i=0; i<index-1; i++){
			tmp=tmp->getNext();
		}
		LinkedListNode<item_t>* tmp2 = tmp->getNext();
		LinkedListNode<item_t>* tmp3 = tmp2->getNext();
		tmp->setNext(tmp3);
		delete tmp2;
		size-=1;
	}

	

}
template <class item_t>
int LinkedList<item_t>::getSize() const{
	return size;
}
template <class item_t>
bool LinkedList<item_t>::isEmpty() const{
	if(size==0){
		return true;
	} else{
		return false;
	}
}
template <class item_t>
void LinkedList<item_t>::printall() const{
	LinkedListNode<item_t>* tmp=head;
	for(int i =0; i<size;i++){
		cout<<tmp->getItem()<<endl;
		tmp=tmp->getNext();
	}
}

#endif