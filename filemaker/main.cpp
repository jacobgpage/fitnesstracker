#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "participant.h"
#include "activity.h"

using namespace std;

int main() {
	
	fstream input;
	fstream output;
	
	string line;
	int i = 0;
	
	input.open( "input.csv", ios::in  );
	output.open( "input.bin", ios::out | ios::binary ); 
	
	if ( input.is_open() ) {
		
		while ( !input.eof() ) {
			
			Participant participant;
			
			getline( input, line, ',' );
			participant.setFirstName( line );
			
			getline( input, line, ',' );
			participant.setLastName( line );
			
			getline( input, line, ',' );
			participant.setHeight( atof( line.c_str() ) );
			
			getline( input, line, ',' );
			
			while ( line != "" ) {
				
				Activity activity;
				
				activity.setActivityCode( atoi( line.c_str() ) );
				
				getline( input, line, ',' );
				activity.setMinsDone( atoi( line.c_str() ) );
				
				participant.setActivity( activity, i );
				
				i++;
				getline( input, line, ',' );
	
			}
			
			participant.setNumActivies( i );
			
			cout << "First Name: " << participant.getFirstName() << endl;
			cout << "Last Name: " << participant.getLastName() << endl;
			cout << "Height: " << participant.getHeight() << endl;
			cout << "Num Activites: " << participant.getNumActivities() << endl;
			
			output.write( (char*) &participant, sizeof( Participant ) );
			
			i = 0;
			getline( input, line, '\n' );
			
		}
		
	} else {
		
		cout << "Error opening!" << endl << endl;
		
	}
	 
	  
	  
	output.close(); 
	input.close();
	*/
	input.open( "input.bin", ios::in | ios::binary );
	
	while ( !input.eof() ) {
		
		Participant participant;
		input.read( (char*) &participant, sizeof( Participant ) );
		
		cout << "First Name: " << participant.getFirstName() << endl;
		cout << "Last Name: " << participant.getLastName() << endl;
		cout << "Height: " << participant.getHeight() << endl;
		cout << "Num Activites: " << participant.getNumActivities() << endl;
		
		if ( input.fail() ) {
		
			cout << "The input failed!" << endl;
		
		}	
		
		cout << endl << "--------------------------------" << endl << endl;
		
	}
	
	input.close();
	
	return (0);
	
}