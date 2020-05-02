#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <algorithm>
#include <iostream>
#include <iomanip>
#include "node.h"

using namespace std;

// declaration for friend statement below
template<class T> class Position;

const int PREORDER = 1;

template<class T>
class BinarySearchTree {

	public:

		BinarySearchTree();
		BinarySearchTree( const BinarySearchTree& );

		// returns num nodes in tree
		int size() const { return numNodes; }

		// returns true if tree empty of real nodes
		bool empty() const { return numNodes == 0; }

		// superroot right pointer always points to real root node
		Position<T> root() const {
	   
			return Position<T>( superRootPtr->rightPtr );
	  
		}
		
		Position<T> superRoot() const {
	   
			return Position<T>( superRootPtr );
	  
		}

		void traverseAndPrint( const Position<T>& p, int type )const;
		void calcTotalMiles( const Position<T>&, double& ) const;
		
		void saveTree( const Position<T>&, ofstream& );

		int depth( const Position<T>& ) const;
		int height( const Position<T>& ) const;

		Position<T> begin() const;

		// returns NULL iterator
		Position<T> end() const { return Position<T>( ); }
		Position<T> find( const T& ) const;
		Position<T> insert( const T& );
		Position<T> findByLast( const string& ) const;
	
		bool erase( const T& );
		bool erase( const Position<T>& );

		virtual ~BinarySearchTree() { deleteUtility(superRootPtr); }

		friend class Position<T>;

	private:

		Node<T>* superRootPtr;
		// number real nodes in tree, not including fake super
		// root and fake ends nodes
		
		int numNodes;

		void preorderTraverseAndPrint( const Position<T>& ) const;

		// finds item in tree starting at position
		Position<T> findUtility( const T& item, const Position<T>& )const;
		Position<T> findUtilityLast( const string& item, const Position<T>& )const;

		// inserts item into tree
		Position<T> insertUtility( const T& item );

		// deletes all nodes in the tree
		void deleteUtility( Node<T>* );

		// erases just one node from the tree at position p
		Position<T> eraseUtility( const Position<T>& p);

		// insert item data at position p
		void expandExternal( const T& item, Position<T>& p);

		// remove node above fake leaf node at position p
		Position<T> removeAboveExternal( const Position<T>& p );

};

/*

	Name: BinarySearchTree()
	Parameters: N/A
	BinarySearchTree Default Constructor

*/
template<class T>
BinarySearchTree<T>::BinarySearchTree () {

            superRootPtr = new Node<T> ();
            superRootPtr->rightPtr = new Node<T> ();
            superRootPtr->rightPtr->parentPtr = superRootPtr;
            superRootPtr->leftPtr = NULL;
            numNodes = 0;

}

/*

	Name: depth
	Parameters: A position
	Calculates the depth of the given node position

*/
template<class T>
int BinarySearchTree<T>::depth( const Position<T>& p ) const {

   if ( p.isSuperRoot()) return -1;

   if ( p.isRoot()) return 0;

   else {

      return 1+depth( p.parent() );

   }

}

/*

	Name: height
	Parameters: A position
	Calculates the height of the given node position

*/
template<class T>
int BinarySearchTree<T>::height( const Position<T>& p ) const {

   // if leaf
   if ( p.isExternal() ) return 0;

   int h = 0;

   // h = max of 0 and height of left subtree
   h= max( h, height( Position<T>( p.nodePtr->leftPtr )));

   // h = max of height of left subtree and
   // height of right subtree
   h = max( h, height( Position<T>( p.nodePtr->rightPtr )));

   return 1 + h;

}

/*

	Name: begin
	Parameters: N/A
	Returns the begining position of the tree

*/
template<class T>
Position<T> BinarySearchTree<T>::begin() const {

   if ( numNodes > 0 ) {
	   
      Position<T> p = root();

      while (p.isInternal()) {

         p = p.left();

      }

      return p.parent();

   }

   else return Position<T>( superRootPtr );

}

/*

	Name: findUtility
	Parameters: An item and a position
	Finds and returns the position that is equal to the item returns an external node if it doesn't find anything

*/
template <class T>
Position<T> BinarySearchTree<T>::findUtility( const T& i, const Position<T>& p ) const {
	
	if ( p.isExternal() ) {
		
		return p;
		
	} else if ( i == p.nodePtr->item ) {
		
		return p;
		
	} else if ( i < p.nodePtr->item ) {
		
		return findUtility ( i, p.left() );
		
	} else {
		
		return findUtility( i, p.right() );
		
	}
	
}

/*

	Name: deleteUtility
	Parameters: A node
	Deletes a node

*/
template <class T>
void BinarySearchTree<T>::deleteUtility ( Node<T>* node ) {
	
	if ( node != NULL ) {
		
		deleteUtility ( node->leftPtr );
		deleteUtility ( node->rightPtr );
		
		delete ( node );
		
	}
	
}

/*

	Name: findUtilityLast
	Parameters: A string and a position
	Finds and returns the position that is equal to the string which is a persons last name

*/
template <class T>
Position<T> BinarySearchTree<T>::findUtilityLast( const string& i, const Position<T>& p )const {
	
	char item[15];
	char pItem[15];
	
	strcpy( item, i.c_str() );
	strcpy( pItem, p.nodePtr->getItem().getLastName().c_str() );
	
	int length = strlen( item );
	for ( int i = 0; i < length ; i++ ) {
		
		item[i] = tolower( item[i] );
		
	}
	
	length = strlen( pItem );
	for ( int i = 0; i < length; i++ ) {
		
		pItem[i] = tolower( pItem[i] );
		
	}
	
	string str( item );
	string pstr( pItem );
	
	
	if ( p.isExternal() ) {
		
		return p;
		
	} else if ( str == pstr ) {
		
		return p;
		
	} else if ( str < pstr ) {
		
		return findUtilityLast ( i, p.left() );
		
	} else {
		
		return findUtilityLast ( i, p.right() );
		
	}

}

/*

	Name: findByLast
	Parameters: A string
	Finds a position of a user by their last name

*/
template <class T>
Position<T> BinarySearchTree<T>::findByLast( const string& item ) const {
	
	if ( numNodes > 0 ) {

		Position<T> v = findUtilityLast( item, root());
	  
		return v;

	} else {
		
		return Position<T>(superRootPtr);
		
	}
	
}

/*

	Name: find
	Parameters: An item
	Finds and returns the position that is equal to the item returns an external node if it doesn't find anything

*/
template <class T>
Position<T> BinarySearchTree<T>::find( const T& item ) const {

   if ( numNodes > 0 ) {

      Position<T> v = findUtility( item, root());
	  
      return v;

   }

   else return Position<T>(superRootPtr);
   
}

/*

	Name: expandExternal
	Parameters: item to be inserted and p fake node where item will be inserted
	Inserts item by copying its data to position p and setting position's left and right ptrs to end nodes

*/
template <class T>
void BinarySearchTree<T>::expandExternal( const T& item, Position<T>& p) {
	
	Node<T>* right, *left;
	
	left = new Node<T>();
	right = new Node<T>();
	
	p.nodePtr->leftPtr = left;
	p.nodePtr->rightPtr = right;
	
	left->parentPtr = p.nodePtr;
	right->parentPtr = p.nodePtr;
	
	p.nodePtr->item = item;
	
	numNodes++;
	
}

/*

	Name: insert
	Parameters: An item
	Inserts the item into the tree

*/
template<class T>
Position<T> BinarySearchTree<T>::insert( const T& item ) {

   // root() = superroot's right ptr
   Position<T> p = insertUtility( item );
   // return iterator to position where new node inserted

   return p;

}

/*

	Name: insertUtility
	Parameters: An item
	Expands the tree if needed otherwise it inserts the item in the correct position

*/
template <class T>
Position<T> BinarySearchTree<T>::insertUtility( const T& item ) {
	
	Position<T> foundPosition = findUtility( item, root() );
	
	if ( foundPosition.isExternal() ) {
		
		expandExternal( item, foundPosition );
		return foundPosition; 
		
	} else {
		
		return Position<T> ( superRootPtr );
		
	}
	
}

/*

	Name: erase
	Parameters: A position
	Erases a position from the tree and prints out the data of the item at that position

*/
template<class T>
bool BinarySearchTree<T>::erase( const Position<T>& p ) {

   // can't remove superroot or fake external node
	if ( !p.isSuperRoot() && !p.isExternal() ) {

	   	double miles;
	
		for ( int i = 0; i < p.nodePtr->getItem().getNumActivities(); i++ ) { //Calcs miles walked by user
			
				miles = miles + p.nodePtr->getItem().getActivity( i ).calcMiles( p.nodePtr->getItem().getHeight() );
			
		}
	
		cout << "Last Name: " << p.nodePtr->getItem().getLastName() << endl;
		cout << "First Name: " << p.nodePtr->getItem().getFirstName() << endl;
	
		cout << "Participant " << p.nodePtr->getItem().getFirstName() << " " << p.nodePtr->getItem().getLastName() << ", ";
		cout << fixed << setprecision( 2 );
		cout << miles << " total miles walked removed." << endl << endl;
	   
		eraseUtility( p );
	  
		return true;

	} else {

		return false;

	}

}

/*

	Name: erase
	Parameters: An item
	Erases the position of the item from the tree

*/
template <class T>
bool BinarySearchTree<T>::erase( const T& i ) {
	
	Position<T> foundPosition = findByLast( i );
	
	return erase( foundPosition );
	
}

/*

	Name: removeAboveExternal
	Parameters: A position
	Correctly deletes a node if the node is not external

*/
template <class T>
Position<T> BinarySearchTree<T>::removeAboveExternal( const Position<T>& p ) {
	
	Node<T>* w = p.nodePtr;
	Node<T>* v = p.nodePtr->parentPtr;
	
	Node<T>* siblingPtr, *grandparentPtr;
	
	if ( w == w->parentPtr->leftPtr ) {
		
		siblingPtr = v->rightPtr;
		
	} else {
		
		siblingPtr = v->leftPtr;
		
	}
	
	if ( v == superRootPtr->rightPtr ) {
		
		superRootPtr->rightPtr = siblingPtr;
		siblingPtr->parentPtr = superRootPtr;
		
	} else {
		
		grandparentPtr = v->parentPtr;
		
		if ( grandparentPtr->leftPtr == v ) {
			
			grandparentPtr->leftPtr = siblingPtr;
			
		} else {
			
			grandparentPtr->rightPtr = siblingPtr;
			
		}
		
		siblingPtr->parentPtr = grandparentPtr;
		
	}
	
	delete ( w );
	delete ( v );
	
	--numNodes;
	
	return Position<T> ( siblingPtr );
	
}

/*

	Name: eraseUtility
	Parameters: A position
	Correctly erases a position depending on where it is

*/
template <class T>
Position<T> BinarySearchTree<T>::eraseUtility( const Position<T>& p ) {
	
	Position<T> w( p.nodePtr );
	Position<T> u( p.nodePtr );
	
	if ( p.left().isExternal() ) {
		
		w = p.left();
	
	} else if ( p.right().isExternal() ) {
		
		w = p.right();
		
	} else {
		
		w = p.right();
		
		do {
			
			w = w.left();
			
		} while ( w.isInternal() );
		
		u = w.parent();
		p.nodePtr->setItem( u.getItem() );
		
		return removeAboveExternal( w );
		
	}
	
	return removeAboveExternal( w );
	
}

/*

	Name: traverseandPrint
	Parameters: A postion and integer
	Does the correct type of traverse and prints the data as it traverses the tree

*/
template <class T>
void BinarySearchTree<T>::traverseAndPrint( const Position<T>& p, int i ) const {
	
	if ( i == PREORDER ) {
		
		preorderTraverseAndPrint( p );
		
	}
	
	return;
	
}

/*

	Name: preorderTraverseAndPrint
	Parameters: A position
	Prints the data in the preorder style

*/
template <class T>
void BinarySearchTree<T>::preorderTraverseAndPrint( const Position<T>& p ) const {
	
	if ( !p.isExternal() ) {
		
		double milesWalked = 0;
		
		for ( int i = 0; i < p.nodePtr->getItem().getNumActivities(); i++ ) { //Calcs miles walked by each user
			
			milesWalked = milesWalked + p.nodePtr->getItem().getActivity( i ).calcMiles( p.nodePtr->getItem().getHeight() );
			
		}
		
		string fullName = p.nodePtr->getItem().getFirstName() + " " + p.nodePtr->getItem().getLastName();
		
		cout << left << setw( 20 ) << fullName << fixed << setprecision( 2 ) << right << setw( 6 ) << milesWalked << endl;
		
		preorderTraverseAndPrint( p.left() );
		preorderTraverseAndPrint( p.right() );
		
	}
	
	return;
	
}

/*

	Name: saveTree
	Parameters: A positon and an ofstream file
	Writes the data to the file using a preorder traversal

*/
template <class T>
void BinarySearchTree<T>::saveTree( const Position<T>& p, ofstream& out ) {
	
	if ( !p.isExternal() ) {
		
		Participant participant( p.nodePtr->getItem() );
		
		out.write( (char*) &participant, sizeof( Participant ) );
		
		saveTree( p.left(), out );
		saveTree( p.right(), out );
		
	}
	
	return;
	
}

/*

	Name: calcTotalMiles
	Parameters: A position and integer
	Goes through the tree using a preorder tranversal and calculates the total miles walked by everyone

*/
template <class T>
void BinarySearchTree<T>::calcTotalMiles( const Position<T>& p, double& miles ) const {
	
	if ( !p.isExternal() ) {
		
		for ( int i = 0; i < p.nodePtr->getItem().getNumActivities(); i++ ) { //Calcs miles walked by user and adds to the total of everyone
			
			miles = miles + p.nodePtr->getItem().getActivity( i ).calcMiles( p.nodePtr->getItem().getHeight() );
			
		}
		
		calcTotalMiles( p.left(), miles );
		calcTotalMiles( p.right(), miles );
		
	}
	
	return;
	
}

#endif