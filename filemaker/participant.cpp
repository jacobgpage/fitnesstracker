#include <iostream>
#include "participant.h"

using namespace std;

Participant::Participant() {

	firstName[0] = '\0';
	lastName[0] = '\0';
	height = 0;
	numActivites = 0;
	
}

Participant::Participant( string fN, string lN, double h, int n) {
	
	strcpy( firstName, fN.c_str() );
	strcpy( lastName, lN.c_str() );
	height = h;
	numActivites = n;
	
}

Participant::Participant( const Participant& participant ) {
	
	strcpy( firstName, participant.getFirstName().c_str() );
	strcpy( lastName, participant.getLastName().c_str() );
	height = participant.getHeight();
	numActivites = participant.getNumActivities();
	
	for ( int i = 0; i < numActivites; i++ ) {
		
		activites[i] = participant.getActivity( i );
		
	}
	
}

bool operator<( const Participant& pOne, const Participant& pTwo ) {
	
	string fullNameOne;
	string fullNameTwo;
	
	fullNameOne = pOne.getFirstName() + pOne.getLastName();
	fullNameTwo = pTwo.getFirstName() + pTwo.getLastName();
	
	return ( fullNameOne < fullNameTwo ); 
	
}

bool operator==( const Participant& pOne, const Participant& pTwo ) {
	
	string fullNameOne;
	string fullNameTwo;
	
	fullNameOne = pOne.getFirstName() + pOne.getLastName();
	fullNameTwo = pTwo.getFirstName() + pTwo.getLastName();
	
	return ( fullNameOne == fullNameTwo ); 
	
}

Participant& Participant::operator=( const Participant& pOne ) {
	
	strcpy( this->firstName, pOne.getFirstName().c_str() );
	strcpy( this->firstName, pOne.getLastName().c_str() );
	this->height = pOne.getHeight();
	this->numActivites = pOne.getNumActivities();
	
	for ( int i = 0; i < this->numActivites; i++ ) {
		
		this->activites[i] = pOne.getActivity( i );
		
	}
	
	return *this;
	
}

string Participant::getFirstName() const {
	
	string str( firstName );
	
	return str;
	
}

string Participant::getLastName() const {
	
	string str( lastName );
	
	return str;
	
}