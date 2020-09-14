#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (also duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "TimeCode.h" // for timecode's (duh)

using namespace std;




struct DryingSnapShot {
	string name;
	time_t startTime;
	TimeCode *timeToDry;
};


long long int get_time_remaining(DryingSnapShot dss){
  time_t end = time(0);
  return (dss.timeToDry->GetTimeCodeAsSeconds() - (end - dss.startTime)); //computs difference between time(0) created in main and time(0) created now
}


string drying_snap_shot_to_string(DryingSnapShot dss){
  string output;
  output = "Batch-";
  output.insert(output.size(), dss.name);
  output.insert(output.size(), " (takes ");
  output.insert(output.size(), dss.timeToDry->ToString());
  output.insert(output.size(), " to dry) time remaining: ");
  output.insert(output.size(), to_string(get_time_remaining(dss)));		
  return output;
}


double get_sphere_sa(double rad){
  return (4*(3.1415926)*(rad*rad));
}


TimeCode *compute_time_code(double surfaceArea){
  TimeCode * temp = new TimeCode; //creates new timecode for return value
  temp->SetSeconds(surfaceArea); 
  return temp;
  delete temp;
}


/*void tests(){
	// get_time_remaining
	DryingSnapShot dss;
	dss.startTime = time(0);
	TimeCode tc = TimeCode(0, 0, 7);
	dss.timeToDry = &tc;
	long long int ans = get_time_remaining(dss);
	assert(ans > 6 && ans < 8);
	cout << "Passed" << endl;
	// add more tests here
	

	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);
	cout << "Passed" << endl;
	// add more tests here

	
	// compute_time_code
	tc = *compute_time_code(1.0);
	assert(tc.GetTimeCodeAsSeconds() == 1);
	cout << "Passed" << endl;
	// add more tests here

	
	cout << "ALL TESTS PASSED!" << endl;

	}*/

int main() {
  vector <DryingSnapShot> dss; //timecode vector to store information
  int acc = 0; //accumulates how many timecodes there are
  char ans = 'y'; //initialized to non q value
  while (ans != 'q' && ans != 'Q') {
    cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
    cin >> ans;

    if (ans == 'a' || ans == 'A') {
      cout << "Radius: ";
      double radius;
      cin >> radius;
      DryingSnapShot temp;
      temp.name = to_string(acc);
      temp.startTime = time(0);
      temp.timeToDry = compute_time_code(get_sphere_sa(radius));
      dss.push_back(temp);
      cout << "Batch-" << acc << " will dry in: " << dss[acc].timeToDry->ToString() << endl;
      acc += 1;
    }
    
    else if (ans == 'v' || ans == 'V') {
      for (int i = 0; i < acc; i++) {
	if (get_time_remaining(dss[i]) > 0) cout << drying_snap_shot_to_string(dss[i]) << endl; //if theres time remaining it is displayed
	else { //otherwise remove the finished timer and resize vector
	  dss.erase(dss.begin()+i);
	  acc -= 1;
	  dss.shrink_to_fit();
	  for (unsigned int i = 0; i < dss.size(); i++) dss[i].name = to_string(i); //renames vectors 
	}
      }
      cout << acc << " item(s) being tracked" << endl;
    }
    
    else if (ans == 'q' || ans == 'Q') cout << "Goodbye" << endl;
    
    else cout << "Response not supported, A, V, and Q are accepted" << endl;
  }
  return 0;
}
