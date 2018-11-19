#ifndef BST_FORWARD_ITERATOR
#define BST_FORWARD_ITERATOR

#include "BSTNode.h"
#include <iostream>
using namespace std;
template <class key_t, class val_t>
class BSTForwardIterator
{
  protected:
   //The node the iterator currently points to
   BSTNode<key_t, val_t>* current;
   //The value representing the non-node
   BSTNode<key_t, val_t>* sentinel;
   
  public:
   BSTForwardIterator(BSTNode<key_t, val_t>* node, BSTNode<key_t, val_t>* sentinel);

   //Points the iterator at the successor of its
   //current node (if current is the sentinel,
   //does nothing).
   virtual void next();

   //Returns true if the iterator has moved past
   //the end of the container (if current is sentinel)
   virtual bool isPastEnd() const;

   //Returns the key of the current node
   virtual const key_t& getKey() const;

   //Returns the value of the current node
   virtual const val_t& getValue() const;
   
   //Sets the value of the current node
   virtual void setValue(const val_t& newVal);

   //Declares BSTMultimap as a friend class
   //(so it can access the protected member current)
   template <class k_t, class v_t> friend class BSTMultimap;
   template <class k_t, class v_t> friend class RBTMultimap;
};

////////////////////////////////////////////////////
//Implementation of BSTForwardIterator begins here//
////////////////////////////////////////////////////
template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t>::BSTForwardIterator(BSTNode<key_t, val_t>* node, BSTNode<key_t, val_t>* sentinel){
   this->current=node;
   this->sentinel=sentinel;
   /*std::cout<<"****"<<std::endl;
   std::cout<<(current->getRightChild()==this->sentinel)<<std::endl;
   std::cout<<(current->getRightChild()==sentinel)<<std::endl;
   std::cout<<"****"<<std::endl;*/

}

template <class key_t, class val_t>
void BSTForwardIterator<key_t, val_t>::next(){
   /*std::cout<<"####"<<std::endl;
   std::cout<<(current->getRightChild()==this->sentinel)<<std::endl;
   std::cout<<(current->getRightChild()==sentinel)<<std::endl;
   std::cout<<"####"<<std::endl;
   std::cout<<this->getValue()<<endl;
   std::cout<<"before "<<endl;
   current=current->getParent();
   std::cout<<"after "<<endl;*/
   
   BSTNode<key_t, val_t>* curr_node = this->current;
   if(((this->current)!=(this->sentinel) && (this->current)->getRightChild()!=(this->sentinel))){
      curr_node=curr_node->getRightChild();
      while((curr_node!=(this->sentinel) && curr_node->getLeftChild()!=(this->sentinel))){
         curr_node=curr_node->getLeftChild();

      }
      current=curr_node;
      if(curr_node==(this->sentinel)){

      }


   } else{
      if(curr_node!=(this->sentinel)){
         BSTNode<key_t, val_t>* parent_point = curr_node->getParent();
         while((parent_point!=(this->sentinel)) && curr_node==parent_point->getRightChild()){
            curr_node=parent_point;
            parent_point=parent_point->getParent();
         }
         curr_node=parent_point;
      }
      (this->current)=curr_node;

   }


   
}
template <class key_t, class val_t>
bool BSTForwardIterator<key_t, val_t>::isPastEnd() const{
   return (this->current==this->sentinel);
}
template <class key_t, class val_t>
const key_t& BSTForwardIterator<key_t, val_t>::getKey() const{
   //std::cout<<"===="<<std::endl;
   //std::cout<<(current->getRightChild()==sentinel)<<std::endl;
   //std::cout<<"===="<<std::endl;
   return (this->current)->getKey();
}
template <class key_t, class val_t>
const val_t& BSTForwardIterator<key_t, val_t>::getValue() const{
   return (this->current)->getValue();
}
template <class key_t, class val_t>
void BSTForwardIterator<key_t, val_t>::setValue(const val_t& newVal){
   (this->current)->setValue(newVal);
}


#endif
