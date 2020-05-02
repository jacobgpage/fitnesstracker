#ifndef POSITION_H
#define POSITION_H

template<class T> class BinarySearchTree; // declaration for friend statement below

template<class T>
class Position {

	public:  

		Node<T>& operator*() { return *nodePtr; }

		Position parent() const {
			return Position<T>( this->nodePtr->parentPtr ); }

		Position left() const {
			return Position<T>( nodePtr->leftPtr ); }

		Position right() const {
			return Position<T>( nodePtr->rightPtr ); }

			bool isRoot( ) const { // does this iterator point to real root?
			return this->nodePtr->parentPtr->parentPtr == NULL; }

		bool isSuperRoot() const{ // does this iterator point to fake superroot?
			return this->nodePtr->parentPtr == NULL; }

		bool isExternal() const { // is it a fake end node?
			return this->nodePtr->leftPtr == NULL && this->nodePtr->rightPtr == NULL; }

		bool isInternal() const { return !(isExternal() ); }

		bool operator==( const Position& p ) {
			return this->nodePtr == p.nodePtr; }

		Position& operator++( ); // inorder traversal
		
		void editPosition( T& );
		
		T getItem() { return nodePtr->item; }

		friend class BinarySearchTree<T>;

	private:

		// only friends like BST can create positions from its nodes
		Position( Node<T>* );
		Node<T>* nodePtr;

};

/*

	Name: Position()
	Parameters: A node
	Constructor for position and inserts a node into that position

*/
template <class T>
Position<T>::Position( Node<T>* node ) {
	
	nodePtr = node;
	
}

/*

	Name: operator++
	Parameters: N/A
	Overloaded ++ operator for iteratoring the position

*/
template <class T>
Position<T>& Position<T>::operator++( ) {
	
	Position w = this.right();
	
	if ( w.isInternal() ) {
		
		do {
			
			*this = w;
			w = w.left();
			
		} while ( w.isInternal() );
		
	} else {
		
		w = this.parent();
		
		while ( *w != NULL ) {
			
			*this = w;
			w = w.parent();
			
		}
		
		*this = w;
		
	}
	
	return *this;
	
}

/*

	Name: editPosition
	Parameters: A item
	Changes the item data in the current position

*/
template <class T>
void Position<T>::editPosition(  T& participant ) {
	
	this->nodePtr->item = participant;
	
}
#endif