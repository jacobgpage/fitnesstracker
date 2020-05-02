#ifndef NODE_H
#define NODE_H

template<class T> class BinarySearchTree; // declaration for friend statement below
template<class T> class Position; // declaration for friend statement below

template<class T>
class Node {

	public:

		Node(); // default constuctor
		Node( const Node<T>& ); // copy constructor.

		virtual ~Node<T>() {} // destructor

		void setItem( const T& );
		T getItem() const { return item; }
   
		Node<T>& operator=( const Node<T>& );

		friend class BinarySearchTree<T>;
		friend class Position<T>; // Position is an iterator class

	private:

		T item;
		
		Node<T>* leftPtr;
		Node<T>* rightPtr;
		Node<T>* parentPtr;

};

/*

	Name: Node()
	Parameters: N/A
	Node default constructor

*/
template <class T>
Node<T>::Node () {
	
	leftPtr = NULL;
	rightPtr = NULL;
	parentPtr = NULL;
	
}

/*

	Name: Node()
	Parameters: A node
	Node copy constructor

*/
template <class T>
Node<T>::Node ( const Node<T>& node ) {
	
	item = node.item;
	
	leftPtr = NULL;
	rightPtr = NULL;
	parentPtr = NULL;
	
}

/*

	Name: setItem
	Parameters: A item
	Sets the private item equal to the item parameter

*/
template <class T>
void Node<T>::setItem ( const T& i ) {
	
	item = i;
	
}

/*

	Name: operator=
	Parameters: A node
	Sets one node's item equal to another node's item

*/
template <class T>
Node<T>& Node<T>::operator= ( const Node<T>& node ) {
	
	item = node.item;
	
	leftPtr = NULL;
	rightPtr = NULL;
	parentPtr = NULL;
	
	return *this;
	
}

#endif