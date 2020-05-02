#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <iostream>

using namespace std;

class Activity {
	
	private:
		
		static const string ACTIVITY_NAME[27];
		static const int STEPS[27];
		
		int activityCode;
		int minsDone;
								   	
	public:
	
		Activity();
		Activity( const Activity& );
		
		//Accessor functions
		string getActivityName( int i ) const { return ACTIVITY_NAME[ i ];  }
		int getSteps( int i ) const { return STEPS[ i ]; }
		int getActivityCode() const { return activityCode; }
		int getMinsDone() const { return minsDone; }
		
		//Mutator functions
		void setActivityCode( int i ) { activityCode = i; }
		void setMinsDone( int i ) { minsDone = i; }
		
		//Calculates miles with activity code and minutes
		double calcMiles( double );
		
		Activity& operator=( const Activity& );
	
};

#endif