#ifndef RBT_MULTIMAP
#define RBT_MULTIMAP

#include "BSTMultimap.h"
#include "RBTNode.h"

#include <string>
#include <fstream>
#include <queue>
#include <iostream>
#include <map>

using namespace std;

template <class key_t, class val_t>
class RBTMultimap : public BSTMultimap<key_t, val_t>
{
  protected:
   //Performs the rotate left operation
   //(assumes node has a right child)
   virtual void rotateLeft(BSTNode<key_t, val_t>* node);

   //Performs the rotate right operation
   //(assumes node has a left child)
   virtual void rotateRight(BSTNode<key_t, val_t>* node);

   //Fix up the tree after an insert
   //(assumes insertedNode is red)
   virtual void insertFixup(RBTNode<key_t, val_t>* insertedNode);

   //Fix up the tree after deleting a node
   //ReplacementNode is the node that replaced the deleted node
   //(possibly the sentinel)
   virtual void deleteFixup(RBTNode<key_t, val_t>* replacementNode);

   //Puts replacementNode in nodeToReplace's position in the tree
   //(replacementNode takes its children along with it)
   //Assumes nodeToReplace is a real node (not the sentinel)
   virtual void transplant(BSTNode<key_t, val_t>* nodeToReplace, BSTNode<key_t, val_t>* replacementNode);

  public:
   //Creates an empty red-black tree
   RBTMultimap();
   virtual ~RBTMultimap();

   //Inserts (key, value) into the multimap
   virtual void insert(const key_t& key, const val_t& value);

   //Removes the key/value pair pointed to by pos
   //(if pos is off the end, does nothing)
   //Returns an iterator pointing to the next node after the
   //deleted node
   virtual BSTForwardIterator<key_t, val_t> remove(const BSTForwardIterator<key_t, val_t>& pos);

   //Prints the tree in the "dot" format for visualization
   //using graphviz
   //NOTE: Requires that keys are streamable (values are not printed)
   virtual void printDOT(std::string filename);
   //virtual BSTNode<key_t, val_t>* minimumInSub(BSTNode<key_t, val_t>* subtreeNode);
};

//////////////////////////////////////////
//RBTMultimap implementation begins here//
//////////////////////////////////////////

template <class key_t, class val_t>
RBTMultimap<key_t, val_t>::RBTMultimap(){
	RBTNode<key_t, val_t>* sentinel_node= new RBTNode<key_t, val_t>(key_t(),val_t(),false);
	this->sentinel = sentinel_node;
	this->root = this->sentinel;
}
template <class key_t, class val_t>
RBTMultimap<key_t, val_t>::~RBTMultimap(){
	this->clear();
	delete this->sentinel;
}

template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::insert(const key_t& key, const val_t& value){
	RBTNode<key_t, val_t>* newnode= new RBTNode<key_t, val_t>(key,value,true);
	this->insertNode(newnode);
	this->insertFixup(newnode);
	
}
template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> RBTMultimap<key_t, val_t>::remove(const BSTForwardIterator<key_t, val_t>& pos){

	BSTForwardIterator<key_t, val_t> return_iter(pos.current,this->sentinel);
	return_iter.next();
	
	RBTNode<key_t, val_t>* nodeToRemove=dynamic_cast<RBTNode<key_t, val_t>* >(pos.current);
	RBTNode<key_t, val_t>* nodeToFix=nodeToRemove;
	RBTNode<key_t, val_t>* originalNode = nodeToRemove;
	bool original_color=originalNode->getColor();
	if(nodeToRemove->getLeftChild()==this->sentinel){

		nodeToFix=nodeToRemove->getRightChild();
		this->transplant(nodeToRemove,nodeToRemove->getRightChild());


	} else if (nodeToRemove->getRightChild()==this->sentinel){
		nodeToFix=nodeToRemove->getLeftChild();
		this->transplant(nodeToRemove,nodeToRemove->getLeftChild());

	} else {


		originalNode=dynamic_cast<RBTNode<key_t, val_t>* >(this->minimumInSub(nodeToRemove->getRightChild()));
		original_color = originalNode->getColor();
		nodeToFix=originalNode->getRightChild();


		if(originalNode->getParent()==nodeToRemove){
			nodeToFix->setParent(originalNode);		
		} else {
			this->transplant(originalNode,originalNode->getRightChild());
			originalNode->setRightChild(nodeToRemove->getRightChild());
			(originalNode->getRightChild())->setParent(originalNode);	
		}

		this->transplant(nodeToRemove,originalNode);
		originalNode->setLeftChild(nodeToRemove->getLeftChild());
		(originalNode->getLeftChild())->setParent(originalNode);
		originalNode->setColor(nodeToRemove->getColor());

	}

	if(original_color==false){
		this->deleteFixup(nodeToFix);
		

	}
	if(nodeToRemove!=(this->sentinel)){
		delete nodeToRemove;
	}
	//delete node_for_deletion;
	this->numItems-=1;
	return return_iter;
}
template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::insertFixup(RBTNode<key_t, val_t>* insertedNode){
	RBTNode<key_t, val_t>* current_node=insertedNode;
	while((current_node->getParent())->getColor()==true){

		if ((current_node->getParent()) == ((current_node->getParent())->getParent())->getLeftChild()){
			RBTNode<key_t, val_t>* uncle_node=((current_node->getParent())->getParent())->getRightChild();
			if(uncle_node->getColor()==true){
				(current_node->getParent())->setColor(false);
				uncle_node->setColor(false);
				((current_node->getParent())->getParent())->setColor(true);
				current_node=((current_node->getParent())->getParent());
			} else{
				if((current_node->getParent())->getRightChild() == current_node){
					current_node=current_node->getParent();
					this->rotateLeft(current_node);
				}
				(current_node->getParent())->setColor(false);
				((current_node->getParent())->getParent())->setColor(true);
				this->rotateRight(((current_node->getParent())->getParent()));
			}
		} else{
			RBTNode<key_t, val_t>* uncle_node=((current_node->getParent())->getParent())->getLeftChild();
			if(uncle_node->getColor()==true){
				(current_node->getParent())->setColor(false);
				uncle_node->setColor(false);
				((current_node->getParent())->getParent())->setColor(true);
				current_node=((current_node->getParent())->getParent());
			} else{
				if((current_node->getParent())->getLeftChild() == current_node){
					current_node=current_node->getParent();
					this->rotateRight(current_node);
				}
				(current_node->getParent())->setColor(false);
				((current_node->getParent())->getParent())->setColor(true);
				this->rotateLeft(((current_node->getParent())->getParent()));

			}
		}
	}
	(dynamic_cast<RBTNode<key_t, val_t>* >(this->root))->setColor(false);
}
template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::deleteFixup(RBTNode<key_t, val_t>* replacementNode){
	

	while(replacementNode!=this->root && replacementNode->getColor()==false){
		if(replacementNode==(replacementNode->getParent())->getLeftChild()){

			RBTNode<key_t, val_t>* brother = (replacementNode->getParent())->getRightChild();
			if(brother->getColor()==true){

				brother->setColor(false);

				(replacementNode->getParent())->setColor(true);

				this->rotateLeft(replacementNode->getParent());

				brother=(replacementNode->getParent())->getRightChild();
			}
			if((brother->getLeftChild())->getColor()==false && (brother->getRightChild())->getColor()==false){
				brother->setColor(true);
				replacementNode=replacementNode->getParent();

			} else{
				if((brother->getRightChild())->getColor()==false){

					(brother->getLeftChild())->setColor(false);
					brother->setColor(true);
					this->rotateRight(brother);
					brother=(replacementNode->getParent())->getRightChild();
				}

				brother->setColor((replacementNode->getParent())->getColor());
				(replacementNode->getParent())->setColor(false);
				(brother->getRightChild())->setColor(false);
				this->rotateLeft(replacementNode->getParent());
				replacementNode=dynamic_cast<RBTNode<key_t, val_t>* >(this->root);
			}

				
		} else{
			RBTNode<key_t, val_t>* brother = (replacementNode->getParent())->getLeftChild();
			if(brother->getColor()==true){
				brother->setColor(false);
				(replacementNode->getParent())->setColor(true);

				this->rotateRight(replacementNode->getParent());
				brother=(replacementNode->getParent())->getLeftChild();

			}
			if((brother->getRightChild())->getColor()==false && (brother->getLeftChild())->getColor()==false){
				brother->setColor(true);
				replacementNode=replacementNode->getParent();

			} else{
				if((brother->getLeftChild())->getColor()==false){
					(brother->getRightChild())->setColor(false);
					brother->setColor(true);
					this->rotateLeft(brother);
					brother =( replacementNode->getParent())->getLeftChild();

				}
				brother->setColor((replacementNode->getParent())->getColor());
				(replacementNode->getParent())->setColor(false);
				(brother->getLeftChild())->setColor(false);
				this->rotateRight(replacementNode->getParent());
				replacementNode=dynamic_cast<RBTNode<key_t, val_t>* >(this->root);

			}

		

		}
		
	
	}
	replacementNode->setColor(false);

}
template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::rotateLeft(BSTNode<key_t, val_t>* node){
	RBTNode<key_t, val_t>* rotate_comp = dynamic_cast<RBTNode<key_t, val_t>* >(node->getRightChild());
	node->setRightChild(rotate_comp->getLeftChild());
	if(rotate_comp->getLeftChild()!=this->sentinel){
		(rotate_comp->getLeftChild())->setParent(node);
	}

	rotate_comp->setParent(node->getParent());
	if(node->getParent()==this->sentinel){
		this->root=rotate_comp;
	} else if (node == ((node->getParent())->getLeftChild())){
		(node->getParent())->setLeftChild(rotate_comp);
	} else{
		(node->getParent())->setRightChild(rotate_comp);
	}
	rotate_comp->setLeftChild(node);
	node->setParent(rotate_comp);

}
template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::rotateRight(BSTNode<key_t, val_t>* node){
	RBTNode<key_t, val_t>* rotate_comp = dynamic_cast<RBTNode<key_t, val_t>* >(node->getLeftChild());
	node->setLeftChild(rotate_comp->getRightChild());
	if (rotate_comp->getRightChild()!=this->sentinel){
		
		(rotate_comp->getRightChild())->setParent(node);
	}
	rotate_comp->setParent(node->getParent());
	if (node->getParent()==this->sentinel){
		this->root = rotate_comp;
	} else if (node == ((node->getParent())->getLeftChild())){
		(node->getParent())->setLeftChild(rotate_comp);
	} else{
		(node->getParent())->setRightChild(rotate_comp);
	}
	rotate_comp->setRightChild(node);
	node->setParent(rotate_comp);
}
template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::transplant(BSTNode<key_t, val_t>* nodeToReplace, BSTNode<key_t, val_t>* replacementNode){
	if (nodeToReplace->getParent() == this->sentinel){
		this->root = replacementNode;
	} else if(nodeToReplace == (nodeToReplace->getParent())->getLeftChild()){
		(nodeToReplace->getParent())->setLeftChild(replacementNode);	
	} else{
		(nodeToReplace->getParent())->setRightChild(replacementNode);
	}
	replacementNode->setParent(nodeToReplace->getParent());
}







template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::printDOT(std::string filename)
{
   using namespace std;
   ofstream fout(filename.c_str());

   long long counter = 1;
   map<RBTNode<key_t, val_t>*, long long> nodeToCounter;
   nodeToCounter[dynamic_cast<RBTNode<key_t, val_t>* >(this->sentinel)] = counter;
   counter++;

   fout << "digraph RBTMultimap {" << endl;

   fout << "\t node" << nodeToCounter[dynamic_cast<RBTNode<key_t, val_t>* >(this->sentinel)] << " [label=\"nil\", style=filled, color=grey, fontcolor=white];" << endl;

   if(this->root != this->sentinel)
   {
      RBTNode<key_t, val_t>* rt = dynamic_cast<RBTNode<key_t, val_t>* >(this->root);
      if(!nodeToCounter[rt])
      {
	 nodeToCounter[rt] = counter;
	 counter++;
      }
      if(!nodeToCounter[rt->getParent()])
      {
	 nodeToCounter[rt->getParent()] = counter;
	 counter++;
      }
      fout << "\t node" << nodeToCounter[rt] << " -> node" << nodeToCounter[rt->getParent()] << " [constraint=false, tailport=n, headport=s";
      if(rt->getParent() == this->sentinel)
      {
	 fout << ", color=grey];" << endl;
      }
      else
      {
	 //The root's parent is something weird!! Make the arrow orange so it sticks out
	 fout << ", color=orange];" << endl;
      }

      map<RBTNode<key_t, val_t>*, bool> printed;
   
      queue<RBTNode<key_t, val_t>* > q;
      q.push(rt);
      while(!q.empty())
      {
	 RBTNode<key_t, val_t>* node = q.front();
	 q.pop();

	 printed[node] = true;
      
	 //Set up node's appearance
	 if(!nodeToCounter[node])
	 {
	    nodeToCounter[node] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " [label=\"k: " << node->getKey() << "\", style=filled, color=";
	 if(node->getColor())
	 {
	    fout << "red";
	 }
	 else
	 {
	    fout << "black, fontcolor=white";
	 }
	 fout << "];" << endl;

	 //Set up child links
	 //First the left node
	 if(!nodeToCounter[node->getLeftChild()])
	 {
	    nodeToCounter[node->getLeftChild()] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " -> node" << nodeToCounter[node->getLeftChild()] << " [tailport=sw";    
	 if(node->getLeftChild() == this->sentinel)
	 {
	    fout << ", color=grey";
	 }
	 else if(printed[node->getLeftChild()])
	 {
	    fout << ", color=orange";
	 }
	 else
	 {
	    q.push(node->getLeftChild());
	 }

	 if(node->getLeftChild() != this->sentinel)
	 {
	    if(node->getLeftChild()->getParent() == node)
	    {
	       //The child's parent pointer points right back,
	       //so draw the second arrow
	       fout << ", dir=both];" << endl;
	    }
	    else
	    {
	       //The child node's parent pointer is not correct!
	       //Draw it in orange so it sticks out
	       fout << "];" << endl;
	       if(!nodeToCounter[node->getLeftChild()->getParent()])
	       {
		  nodeToCounter[node->getLeftChild()->getParent()] = counter;
		  counter++;
	       }
	       fout << "\t node" << nodeToCounter[node->getLeftChild()] << " -> node" << nodeToCounter[node->getLeftChild()->getParent()] << " [tailport=n, color=orange];" << endl;
	    }
	 }
	 else
	 {
	    fout << "];" << endl;
	 }

	 //Now the right node
	 if(!nodeToCounter[node->getRightChild()])
	 {
	    nodeToCounter[node->getRightChild()] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " -> node" << nodeToCounter[node->getRightChild()] << " [tailport=se";    
	 if(node->getRightChild() == this->sentinel)
	 {
	    fout << ", color=grey";
	 }
	 else if(printed[node->getRightChild()])
	 {
	    fout << ", color=orange";
	 }
	 else
	 {
	    q.push(node->getRightChild());
	 }

	 if(node->getRightChild() != this->sentinel)
	 {
	    if(node->getRightChild()->getParent() == node)
	    {
	       //The child's parent pointer points right back,
	       //so draw the second arrow
	       fout << ", dir=both];" << endl;
	    }
	    else
	    {
	       //The child node's parent pointer is not correct!
	       //Draw it in orange so it sticks out
	       fout << "];" << endl;
	       if(!nodeToCounter[node->getRightChild()->getParent()])
	       {
		  nodeToCounter[node->getRightChild()->getParent()] = counter;
		  counter++;
	       }
	       fout << "\t node" << nodeToCounter[node->getRightChild()] << " -> node" << nodeToCounter[node->getRightChild()->getParent()] << " [tailport=n, color=orange];" << endl;
	    }
	 }
	 else
	 {
	    fout << "];" << endl;
	 }
      }
   }
   fout << "}" << endl;
}

#endif
