#include <iostream>
#include "participant.h"

using namespace std;

/*

	Name: Participant()
	Parameters: N/A
	Default constructor for Participant class

*/
Participant::Participant() {

	firstName[0] = '\0';
	lastName[0] = '\0';
	height = 0;
	numActivites = 0;
	
}

/*

	Name: Participant()
	Parameters: A participant
	Copy constructor for Participant class

*/
Participant::Participant( const Participant& participant ) {
	
	strcpy( firstName, participant.getFirstName().c_str() );
	strcpy( lastName, participant.getLastName().c_str() );
	height = participant.getHeight();
	numActivites = participant.getNumActivities();
	
	for ( int i = 0; i < numActivites; i++ ) {
		
		activites[i] = participant.getActivity( i );
		
	}
	
}

/*

	Name: operator<
	Parameters: two participants
	Appends the first name onto the back of the last name and compares if the first name is less than the second name

*/
bool operator<( const Participant& pOne, const Participant& pTwo ) {
	
	string fullNameOne;
	string fullNameTwo;
	
	fullNameOne = pOne.getLastName() + pOne.getFirstName();
	fullNameTwo = pTwo.getLastName() + pTwo.getFirstName();
	
	return ( fullNameOne < fullNameTwo ); 
	
}

/*

	Name: operator==
	Parameters: two participants
	Appends the first name onto the back of the last name and compares if the first name is equal to the second name

*/
bool operator==( const Participant& pOne, const Participant& pTwo ) {
	
	string fullNameOne;
	string fullNameTwo;
	
	fullNameOne = pOne.getFirstName() + pOne.getLastName();
	fullNameTwo = pTwo.getFirstName() + pTwo.getLastName();
	
	return ( fullNameOne == fullNameTwo ); 
	
}

/*

	Name: operator=
	Parameters: A participant
	Sets a participant's data equal to another participant's data

*/
Participant& Participant::operator=( const Participant& pOne ) {
	
	strcpy( this->firstName, pOne.getFirstName().c_str() );
	strcpy( this->lastName, pOne.getLastName().c_str() );
	this->height = pOne.getHeight();
	this->numActivites = pOne.getNumActivities();
	
	for ( int i = 0; i < this->numActivites; i++ ) {
		
		this->activites[i] = pOne.getActivity( i );
		
	}
	
	return *this;
	
}

/*

	Name: getFirstName
	Parameters: N/A
	Returns the private first name data

*/
string Participant::getFirstName() const {
	
	string str( firstName );
	
	return str;
	
}

/*

	Name: getLastName
	Parameters: N/A
	Returns the private last name data

*/
string Participant::getLastName() const {
	
	string str( lastName );
	
	return str;
	
}