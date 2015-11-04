#include <iostream>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include <string>

// Number of floors in the building.
int numFloors = 0;
// Number of elevators in the building.
int numElevators = 0;
// Number of simulations the user requests.
int numSimulations = 0;

using namespace std;

enum Direction
  {
    IDLE = 0,
    UP = 1,
    DOWN = 2,
  };

struct elevator
{
  int currentFloor;
  int destinationFloor;
  int direction;
} elevator; 

// What floor are you calling the elevator from?
int currentFloor()
{
  int floorCall = 0;
  cout << "What floor are you on? ";
  cin >> floorCall;
  if( floorCall < numFloors+1 && floorCall > 0 )
    {
      return floorCall;
    }
  else
    {
      cout << "Please enter a valid floor." << endl;
      return currentFloor();
    }
}

// From your floor, which floor would you like to go to?
int currentDesired()
{
  int desiredCall = 0;
  cout << "What floor would you like to go to? ";
  cin >> desiredCall;
  if( desiredCall == elevator.currentFloor )
    {
      elevator.direction = 0;
      return desiredCall;
    }
  if( desiredCall > elevator.currentFloor )
    {
      if( desiredCall < numFloors+1 )
	{
	  elevator.direction = 1;
	  return desiredCall;
	}
      if( desiredCall > numFloors )
	{
	  elevator.direction = 0;
	  cout << "Please enter a valid floor." << endl;
	  return currentDesired(); // ERROR
	}
    }
  if( desiredCall < elevator.currentFloor )
    {
      if( desiredCall > 0 )
	{
	  elevator.direction = 2;
	  return desiredCall;
	}
      if( desiredCall < 1 )
	{
	  elevator.direction = 0;
	  cout << "Please enter a valid floor." << endl;
	  return currentDesired(); // ERROR
	}
    }
  else
    {
      elevator.direction = 0;
      cout << "How the Hell did you get here?" << endl;
      return currentDesired(); // ERROR
    }
}

int main()
{
  cout << "\n";
  cout << "How many floors? ";
  cin >> numFloors;

  bool floors[numFloors]; // Floors to visit.

  cout << "How many elevators? ";
  cin >> numElevators;
  int elevators[numElevators]; // Elevators we have.

  cout << "How many simulations? ";
  cin >> numSimulations;

  cout << "BEGINNING SIMULATION" << endl;
  sleep( 1 );
  cout << '.' << endl;
  sleep( 1 );
  cout << '.' << endl;
  sleep( 1 );
  cout << '.' << endl;

  // Default elevator position is floor 1.
  elevator.currentFloor = 1;

  for( int i = 0; i < numSimulations; i++ )
    {
      cout << "Elevator beginning at floor " << elevator.currentFloor << '.' << endl;

      // What floor are you calling the elevator from?
      elevator.destinationFloor = currentFloor();
      // Add this value to floors[].

      // If there are floors[] to visit between currentFloor and destinaitonFloor,
      // then stop at those floors. Assuming they are going the same direction.
     
      if( elevator.destinationFloor != elevator.currentFloor )
	{
	  sleep( 1 ); // Elevator moving.
	  
	  // Elevator is now where currentFloor came from.
	  elevator.currentFloor = elevator.destinationFloor; 
	  // Remove this value from floors[].
	  
	  cout << "Elevator is now on floor " << elevator.currentFloor << '.' << endl;
	}
      
      // What floor would you like to go to?      
      elevator.destinationFloor = currentDesired();
      // Add this value to floor[].

      if( elevator.currentFloor != elevator.destinationFloor )
	{
	  if( elevator.direction == 1 ) // UP
	    {
	      cout << "Elevator going up from floor " << elevator.currentFloor << " to floor " << elevator.destinationFloor << '.' << endl;
	    }
	  if( elevator.direction == 2 ) // DOWN
	    {
	      cout << "Elevator moving down from floor " << elevator.currentFloor << " to floor " << elevator.destinationFloor << '.' << endl;
	    }

	  sleep( 1 ); // Elevator moving.

	  // Elevator is now where currentDesired came from.
	  elevator.currentFloor = elevator.destinationFloor;
	  // Remove this value from floors[].

	  cout << "Elevator is now on floor " << elevator.currentFloor << '.' << endl;
	}

      else
	{
	  cout << "You're already on floor " << elevator.currentFloor << " genius!" << endl;
	}

      cout << "END SIMULATION " << i+1 << '.' << endl;
      sleep( 1 );
      cout << "\n";
    } 
  cout << "Thanks for playing!" << endl;    
  cout << "\n";
  return 0;
}
