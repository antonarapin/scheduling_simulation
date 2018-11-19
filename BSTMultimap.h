#ifndef BST_MULTIMAP
#define BST_MULTIMAP

#include <iostream>
#include "BSTNode.h"
#include "BSTForwardIterator.h"

template <class key_t, class val_t>
class BSTMultimap
{
	protected:
		BSTNode<key_t, val_t>* root;
		BSTNode<key_t, val_t>* sentinel;
		int numItems;
		virtual void insertNode(BSTNode<key_t,val_t>* newNode);
	public:
		BSTMultimap();
		virtual ~BSTMultimap();
		virtual void insert(const key_t& key, const val_t& val);
		virtual int getSize();
		virtual bool isEmpty();
		virtual void printTree();
		virtual bool contains(const key_t& key);
		virtual void clear();
		virtual BSTForwardIterator<key_t, val_t> getMin() const;
		virtual BSTForwardIterator<key_t, val_t> getMax() const;
		virtual BSTForwardIterator<key_t, val_t> findFirst(const key_t& key) const;
		virtual BSTForwardIterator<key_t, val_t> findLast(const key_t& key) const;
		virtual BSTForwardIterator<key_t, val_t> remove(const BSTForwardIterator<key_t, val_t>& pos);
		virtual void transplant(BSTNode<key_t, val_t>* node_to_swap, BSTNode<key_t, val_t>* takeover_node);
		virtual BSTNode<key_t, val_t>* minimumInSub(BSTNode<key_t, val_t>* subtreeNode) const;
		virtual BSTNode<key_t, val_t>* findFirstInSub( BSTNode<key_t, val_t>* startNode, const key_t& key) const;



}; 

template <class key_t, class val_t>
BSTMultimap<key_t, val_t>::BSTMultimap(){
	sentinel=0;
	root=sentinel;
	numItems=0;
}
template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::insertNode(BSTNode<key_t,val_t>* newNode){
	BSTNode<key_t, val_t>* start_node=root;
	BSTNode<key_t, val_t>* search_node=sentinel;
	newNode->setLeftChild(sentinel);
	newNode->setRightChild(sentinel);
	while(start_node!=sentinel){
		search_node=start_node;
		if(newNode->getKey() < start_node->getKey()){
			start_node=start_node->getLeftChild();
		} else{
			start_node=start_node->getRightChild();
		}

	}
	newNode->setParent(search_node);
	if(search_node==sentinel){
		root = newNode;
	} else if(newNode->getKey() < search_node->getKey()){
		search_node->setLeftChild(newNode);
	} else{
		search_node->setRightChild(newNode);
	}
	numItems+=1;
}
template <class key_t, class val_t>
int BSTMultimap<key_t, val_t>::getSize(){
	return numItems;
}
template <class key_t, class val_t>
bool BSTMultimap<key_t, val_t>::isEmpty(){
	return (numItems==0);
}
template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::insert(const key_t& key, const val_t& val){
	BSTNode<key_t, val_t>* newnode=new BSTNode<key_t, val_t>(key,val);
	
	this->insertNode(newnode);
	
}
template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::printTree(){
	cout<<"tree"<<endl;
	/*cout<<root->getKey()<<endl;
	cout<<(root->getLeftChild()==sentinel)<<endl;
	cout<<(root->getRightChild()==sentinel)<<endl;
	std::cout<<root->getKey()<<" "<<root->getValue()<<std::endl;
	std::cout<<"left 1 "<<(root->getLeftChild())->getKey()<<std::endl;
	std::cout<<"right 1 "<<(root->getRightChild())->getKey()<<std::endl;
	std::cout<<"ll "<<((root->getLeftChild())->getLeftChild())->getKey()<<std::endl;
	std::cout<<"rr "<<((root->getRightChild())->getRightChild())->getKey()<<std::endl;
	std::cout<<"llr last (6)"<<(((root->getLeftChild())->getRightChild()))->getKey()<<std::endl;*/
}
template <class key_t, class val_t>
bool BSTMultimap<key_t, val_t>::contains(const key_t& key){
	BSTNode<key_t, val_t>* curr_node = root;
	while(curr_node!=sentinel && curr_node->getKey()!=key){
		if (key<(curr_node->getKey())){
			curr_node=curr_node->getLeftChild();
		} else{
			curr_node=curr_node->getRightChild();
		}
	}
	return (curr_node!=sentinel);
	
}
template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::clear(){

	BSTNode<key_t, val_t>* curr_node = root;
	bool done=false;
	if (root==sentinel){
		done=true;
	}
	while(!done){
		if(curr_node->getRightChild()!=sentinel){
			curr_node=curr_node->getRightChild();
		} else if(curr_node->getLeftChild()!=sentinel){
			
			curr_node=curr_node->getLeftChild();
		} else{
			BSTNode<key_t, val_t>* tmp=curr_node;
			if(curr_node->getParent()==sentinel){
				delete curr_node;
				numItems=0;
				root=sentinel;
				done=true;
			} else{
				curr_node=curr_node->getParent();
				if(tmp==curr_node->getRightChild()){
					curr_node->setRightChild(sentinel);
				
				} else{
					curr_node->setLeftChild(sentinel);
				
				}
				delete tmp;
			}
			
			
		}
	}
}
template <class key_t, class val_t>
BSTMultimap<key_t, val_t>::~BSTMultimap(){

	this->clear();

}
template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::getMin() const{
	BSTNode<key_t, val_t>* curr_node = minimumInSub(root);
	return BSTForwardIterator<key_t, val_t>(curr_node,sentinel);
	
}
template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::getMax() const{
	BSTNode<key_t, val_t>* curr_node = root;
	while(curr_node!=sentinel && curr_node->getRightChild()!=sentinel){
		curr_node=curr_node->getRightChild();
	}
	return BSTForwardIterator<key_t, val_t>(curr_node,sentinel);
}
template <class key_t, class val_t>
BSTNode<key_t, val_t>* BSTMultimap<key_t, val_t>::findFirstInSub( BSTNode<key_t, val_t>* startNode, const key_t& key) const{
	BSTNode<key_t, val_t>* curr_node = startNode;
	bool found = false;
	while(!found && curr_node!=sentinel){
		if(curr_node->getKey()==key){
			found=true;
		} else{
			if(curr_node->getKey()>key){
				curr_node=curr_node->getLeftChild();
			} else if(curr_node->getKey()<=key){
				curr_node=curr_node->getRightChild();
			} else{
				curr_node=sentinel;
				found=true;
			}
		}
	}
	return curr_node;
}
template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::findFirst(const key_t& key) const{
	return BSTForwardIterator<key_t, val_t>(this->findFirstInSub(root,key),sentinel);
}
template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::findLast(const key_t& key) const{
	BSTNode<key_t, val_t>* curr_node = this->findFirstInSub(root,key);
	BSTNode<key_t, val_t>* finalNode = curr_node;
	while(curr_node!=sentinel){
		finalNode=curr_node;
		BSTNode<key_t, val_t>* nextNode = curr_node;
		if((curr_node->getKey())>key){
			nextNode=curr_node->getLeftChild();
		} else{
			nextNode=curr_node->getRightChild();
		}
		curr_node=this->findFirstInSub(nextNode,key);
	}
	return BSTForwardIterator<key_t, val_t>(finalNode,sentinel);

}


template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::transplant(BSTNode<key_t, val_t>* node_to_swap, BSTNode<key_t, val_t>* takeover_node){
	if(node_to_swap->getParent()==sentinel){
		root = takeover_node;
	} else if(node_to_swap==((node_to_swap->getParent())->getLeftChild())){
		(node_to_swap->getParent())->setLeftChild(takeover_node);
	} else{
		(node_to_swap->getParent())->setRightChild(takeover_node);
	}
	if(takeover_node!=sentinel){
		takeover_node->setParent(node_to_swap->getParent());
	}
}
template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::remove(const BSTForwardIterator<key_t, val_t>& pos){
	BSTNode<key_t, val_t>* node_to_del=pos.current;
	BSTForwardIterator<key_t, val_t> start_iter(pos.current,sentinel);
	if(node_to_del==sentinel){
		numItems-=1;
		return start_iter;
	}
	if(node_to_del==0){
	}
	start_iter.next();
	if(start_iter.current==sentinel){
		root=sentinel;
		return start_iter;
		numItems-=1;
	}
	if(node_to_del->getLeftChild()==sentinel){
		this->transplant(node_to_del,node_to_del->getRightChild());
	} else if(node_to_del->getRightChild()==sentinel){
		this->transplant(node_to_del,node_to_del->getLeftChild());
	} else{
		BSTNode<key_t, val_t>* search_node = node_to_del->getRightChild();
		while(search_node!=sentinel && search_node->getLeftChild()!=sentinel){
			search_node=search_node->getLeftChild();
		}
		if(search_node->getParent()!=node_to_del){
			this->transplant(search_node,search_node->getRightChild());
			search_node->setRightChild(node_to_del->getRightChild());
			(search_node->getRightChild())->setParent(search_node);
		}
		this->transplant(node_to_del,search_node);
		search_node->setLeftChild(node_to_del->getLeftChild());
		(search_node->getLeftChild())->setParent(search_node);
	}
	if(node_to_del!=(this->sentinel)){
		delete node_to_del;
	}
	numItems-=1;
	return start_iter;
}
template <class key_t, class val_t>
BSTNode<key_t, val_t>* BSTMultimap<key_t, val_t>::minimumInSub(BSTNode<key_t, val_t>* subtreeNode) const{
	
	while(subtreeNode!=this->sentinel && subtreeNode->getLeftChild()!=this->sentinel){
		subtreeNode=subtreeNode->getLeftChild();

	}
	return subtreeNode;
}
#endif




























