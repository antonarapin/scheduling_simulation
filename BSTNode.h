
#ifndef BSTNODE
#define BSTNODE

template <class key_t, class val_t>
class BSTNode 
{
	protected:
		key_t key;
		val_t val;
		BSTNode* rightChild;
		BSTNode* leftChild;
		BSTNode* parent;
	public:
		BSTNode(const key_t& key_in, const val_t& val_in);
		virtual const val_t& getValue() const;
		virtual void setValue(const val_t& val_in);
		virtual const key_t& getKey() const;
		virtual void setKey(const key_t& key_in);
		virtual BSTNode<key_t, val_t>* getLeftChild();
		virtual void setLeftChild(BSTNode* lchild);
		virtual BSTNode<key_t, val_t>* getRightChild();
		virtual void setRightChild(BSTNode* rchild);
		virtual BSTNode<key_t, val_t>* getParent();
		virtual void setParent(BSTNode* parent_in);
};
template <class key_t, class val_t>
BSTNode<key_t, val_t>::BSTNode(const key_t& key_in, const val_t& val_in){
	key=key_in;
	val=val_in;
	rightChild=0;
	leftChild=0;
	parent=0;
}
template <class key_t, class val_t>
const val_t& BSTNode<key_t, val_t>::getValue() const{
	return val;
}
template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setValue(const val_t& val_in){
	val=val_in;
}
template <class key_t, class val_t>
const key_t& BSTNode<key_t, val_t>::getKey() const{
	return key;
}
template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setKey(const key_t& key_in){
	key=key_in;
}
template <class key_t, class val_t>
BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getLeftChild(){
	return leftChild;
}
template <class key_t, class val_t>
BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getRightChild(){
	return rightChild;
}
template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setLeftChild(BSTNode* lchild){
	leftChild=lchild;
}
template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setRightChild(BSTNode* rchild){
	rightChild=rchild;
}
template <class key_t, class val_t>
BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getParent(){
	return parent;
}
template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setParent(BSTNode* parent_in){
	parent=parent_in;
}
#endif

















