#pragma once
#include "Includes.h"
#include "Tour.h"


namespace Data_reduction
{
	struct Person
    {
		int PERID;
        list<Activity*> Activities;
        list<Tour*> Tours;
        list<Tour*> Sub_Tours;
		float Time_At_Home;
		set<int> school_locations;
		set<int> work_locations;
		Household* household;

        Person (int id, Activity* a)
        {
            PERID = id;
            Activities.clear();
			Activities.push_back(a);
            Tours.clear();
            Sub_Tours.clear();
			Time_At_Home=0;
        }
		Person()
		{
			PERID = -1;
			Time_At_Home = 0;
		}
        void Process_Tours();
		void Process_Activity_Locations();
        void Print(int HHID, File_Writer& trip_out, File_Writer& tour_out, File_Writer& person_out);
	private:
		void Update_Activity_Purposes();
		void Process_Tours_Initial();
        void Process_Tours_Characteristics();
    };
}