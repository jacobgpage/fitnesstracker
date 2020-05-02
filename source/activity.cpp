#include <iostream>
#include "activity.h"

using namespace std;

const string Activity::ACTIVITY_NAME[27] = { "Assembly Line", "Shooting Baskets", "Basketball Game", "Bicycling under 10 mph", 
								   "Bicycling", "Cooking", "Dance", "Football", "Hiking", "House Cleaning", "Gardening", 
								   "Minature Golf", "Racquetball", "Rowing", "Running 6 mph", "Running 7 mph", 
								   "Running 8 mph", "Shopping", "Soccer", "Softball", "Stairs", "Swimming Laps", 
								   "Tennis", "Walking 3 mph", "Walking 4 mph", "Weight Lifting", "Yoga" };
								   
const int Activity::STEPS[27] = { 85, 136, 242, 121, 242, 61, 167, 242, 182, 91, 99, 91, 212, 212, 303, 348, 409, 70, 
							212, 152, 273, 212, 212, 100, 152, 121, 76 };

/*

	Name: Activity()
	Parameters: N/A
	Default constructor for Activity class

*/
Activity::Activity() {
	
	activityCode = 0;
	minsDone = 0;
	
}

/*

	Name: Activity()
	Parameters: An Activity class object
	Copy constructor for Activity class

*/
Activity::Activity( const Activity& activity ) {
	
	activityCode = activity.getActivityCode();
	minsDone = activity.getMinsDone();
	
	
}

/*

	Name: calcMiles
	Parameters: A users height
	Calc miles for the Activity data stored in the class

*/
double Activity::calcMiles( double height ) {
	
	int codeSteps = getSteps( getActivityCode() );
	int minutesDone = getMinsDone();
	
	double miles = codeSteps * minutesDone;
	miles = miles * ( ( 0.413 * height ) / 12 );
	
	miles = miles / 5280;
	
	return ( miles );
	
}

/*

	Name: operator=
	Parameters: An Activity class
	Overloaded = operator for Activity class

*/
Activity& Activity::operator=( const Activity& aOne ) {
	
	this->activityCode = aOne.activityCode;
	this->minsDone = aOne.minsDone;
	
	return *this;
	
}