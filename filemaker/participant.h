#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <iostream>
#include <string.h>
#include "activity.h"

using namespace std;

class Participant {
	
	private:

		//Name of participant
		char firstName[20];
		char lastName[20];
		
		//Participant's height
		double height;
		
		//Activites of the participant
		Activity activites[365];
		int numActivites; //Number of activites the participant did
	
	public:
		
		//Constructors
		Participant();
		Participant( string, string, double, int n );
		Participant( const Participant& );
		
		//Accessor functions
		string getFirstName() const;
		string getLastName() const;
		double getHeight() const { return height; }
		Activity getActivity( int i ) const { return activites[i]; }
		int getNumActivities() const { return numActivites; }
		
		//Mutator functions
		void setFirstName( string s ) { strcpy( firstName, s.c_str() ); }
		void setLastName( string s ) { strcpy( lastName, s.c_str() ); }
		void setHeight( double d ) { height = d; }
		void setActivity( Activity& a, int i ) { activites[i] = a; }
		void setNumActivies( int i ) { numActivites = i; }
		
		Participant& operator=( const Participant& );
		
		friend bool operator<( const Participant&, const Participant& );
		friend bool operator==( const Participant&, const Participant&);
		
		friend class Activity;
	
};

#endif