#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <sstream>

#include "participant.h"
#include "binarySearchTree.h"
#include "position.h"
#include "node.h"

using namespace std;

/*

	Name: ReadtoTree
	Parameters: a binary search tree
	Inputs data from 'tracking.bin' into a binary search tree

*/
void ReadtoTree( BinarySearchTree<Participant>& tree ) {
	
	Participant participant;
	fstream input;
	
	input.open( "tracking.bin", ios::in | ios::binary );
	
	if ( input.peek() != ifstream::traits_type::eof() ) { //Checks if file is empty
		
		while ( !input.eof() ) { //Goes till the end of file
		
			input.read( (char*) &participant, sizeof( Participant ) );
		
			if ( participant.getHeight() != 0 ) {
			
				tree.insert( participant );
			
			}
	
		}
		
	}
	
	return;
	
}

int main() {
	
	BinarySearchTree<Participant> tree;
	ReadtoTree( tree );

	char input;
	int loop = 1;
	
	while ( loop != 0 ) { //Loops till user enters 6
		
		input = '0';
		
		while ( input == '0' ) { //Makes sure user inputs valid input
			
			cout << "1 Remove participant" << endl;
			cout << "2 Add participant" << endl;
			cout << "3 Add activity" << endl;
			cout << "4 Calculate total miles walked" << endl;
			cout << "5 Pre-order print" << endl;
			cout << "6 Exit and save" << endl;
			cout << "Option> ";
			
			cin >> input;
			
			cout << endl;
			
			if ( input != '1' && input != '2' && input != '3' && input != '4' && input != '5' && input != '6' ) {
				
				cout << "Please input a valid number!" << endl << endl;
				input = '0';
				
			}
		
		}
		
		if ( input == '1' ) { //Remove participant
			
			string userName;
			
			cout << "Enter participants last name: ";
			cin >> userName;
			cout << endl;
			
			if ( tree.erase( tree.findByLast( userName ) ) == false ) { //If user exists
				
				cout << userName << " is not a participant." << endl << endl;
				
			}
			
		} else if ( input == '2' ) { //Add participant
			
			string userName;
			
			cout << "Enter participants last name: ";
			cin >> userName;
			cout << endl;
			
			if ( tree.findByLast( userName ).isExternal() || tree.findByLast( userName ).isSuperRoot() ) { //User doesn't exists
				
				Participant participant;
				
				char temp[15];
				
				strcpy( temp, userName.c_str() );
				
				temp[0] = toupper( temp[0] );
				for ( int i = 1; i < (int) strlen( temp ); i++ ) {
					
					temp[i] = tolower( temp[i] );
					
				}
				
				string tempstr( temp );
				
				participant.setLastName( tempstr );
				
				cout << "Enter participants first name: ";
				cin  >> userName;
				cout << endl;
				
				strcpy( temp, userName.c_str() );
				
				temp[0] = toupper( temp[0] );
				for ( int i = 1; i < (int) strlen( temp ); i++ ) {
					
					temp[i] = tolower( temp[i] );
					
				}
				
				string tempstrTwo( temp );
				
				participant.setFirstName( tempstrTwo );
				
				cout << "Enter participants height: ";
				cin  >> userName;
				cout << endl;
				
				participant.setHeight( atof( userName.c_str() ) );
				
				tree.insert( participant );
				
			} else { //User already exists
				
				cout << tree.findByLast( userName ).getItem().getLastName() << " is already a participant." << endl << endl;
				
			}
			
		} else if ( input == '3' ) { //Add activity
			
			string userName;
			
			cout << "Enter participants last name: ";
			cin >> userName;
			cout << endl;
			
			if ( tree.findByLast( userName ).isInternal() ) { //If the user exists
			
				Participant participant;
				
				participant = tree.findByLast( userName ).getItem();
				
				int actNum, minsDone;
				
				cout << "Activity: "; //Gets activity code from user
				cin >> actNum;
				cout << endl;
				
				cout << "Minutes: "; //Gets mins done from the user
				cin >> minsDone;
				cout << endl;
				
				Activity a; //Creates an activity class and sets the data in it
				
				a.setActivityCode( actNum );
				a.setMinsDone( minsDone );
				
				participant.setActivity( a, participant.getNumActivities() );
				participant.setNumActivities( participant.getNumActivities() + 1 );
				
				tree.findByLast( userName ).editPosition( participant ); //Edits that data for the position on the tree
				
				//Prints out [First Name] [Last Name], [Activity], [Mins Done] = [Total Miles Calc]
				
				cout << "Num Act: " << tree.findByLast( userName ).getItem().getNumActivities() << endl;
				cout << "Act: " << tree.findByLast( userName ).getItem().getActivity( tree.findByLast( userName ).getItem().getNumActivities() - 1 ).getActivityCode() << " Mins: ";
				cout << tree.findByLast( userName ).getItem().getActivity( tree.findByLast( userName ).getItem().getNumActivities() - 1 ).getMinsDone() << endl << endl;
				
				cout << "Added " << tree.findByLast( userName ).getItem().getFirstName() << " " << tree.findByLast( userName ).getItem().getLastName() << ", ";
				cout << tree.findByLast( userName ).getItem().getActivity( 0 ).getActivityName( tree.findByLast( userName ).getItem().getActivity( tree.findByLast( userName ).getItem().getNumActivities() - 1 ).getActivityCode() ) << " , ";
				cout << tree.findByLast( userName ).getItem().getActivity( tree.findByLast( userName ).getItem().getNumActivities() - 1 ).getMinsDone() << " minutes = ";
				
				double milesWalked = tree.findByLast( userName ).getItem().getActivity( tree.findByLast( userName ).getItem().getNumActivities() - 1 ).calcMiles( tree.findByLast( userName ).getItem().getHeight() );
				
				cout << fixed << setprecision( 2 ) << milesWalked << " miles" << endl << endl;
				
			} else { //User doesn't exists
				
				cout << userName << " is not a participant." << endl << endl;
				
			}
			
		} else if ( input == '4' ) { //Calculate total miles walked
			
			double miles = 0;
			tree.calcTotalMiles( tree.root(), miles ); //Calcs total miles using a preorder traversal
			
			cout << fixed << setprecision( 2 );
			cout << "Total miles walked by *everyone* =  " << miles << endl << endl;
			
		} else if ( input == '5' ) { //Pre-order print
			
			cout << "Participant   Miles" << endl;
			cout << "-------------------" << endl << endl;
			tree.traverseAndPrint( tree.root(), PREORDER); //Prints [Name] [Miles walked] in a preorder traversal
			cout << endl;
			
		} else if ( input == '6' ) { //Exit and save
			
			ofstream out;
			
			out.open( "tracking.bin", ios::out | ios::binary );
			tree.saveTree( tree.root(), out ); //Writes the tree to the file in a preorder traversal
			
			out.close(); //Saves file
			
			loop = 0; //Ends loop
			
		}
		
	}
	
	cout << "Data has been saved!" << endl;
	cout << "Thank you for using the program!" << endl << endl;
	
	return (0);
	
}