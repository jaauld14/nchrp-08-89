#pragma once
#include "Includes.h"
#include "Person.h"

namespace Data_reduction
{
	struct Household
    {
		int ID;
		Household(){}
        map<int, Person*> Persons;
        Household(int id, Person* p)
        {
			
            this->ID = id;
            //Persons = map<int, Person>();
            Persons.insert(pair<int,Person*>(p->PERID, p));
        }
        void Process()
        {
			for (map<int, Person*>::iterator itr = Persons.begin(); itr != Persons.end(); ++itr)
            {
                itr->second->Process_Activity_Locations();
            }
			for (map<int, Person*>::iterator itr = Persons.begin(); itr != Persons.end(); ++itr)
            {
                itr->second->Process_Tours();
            }
        }
        void Print(File_Writer& trip_out, File_Writer& tour_out, File_Writer& person_out)
        {
			for (map<int,Person*>::iterator itr = Persons.begin(); itr != Persons.end(); ++itr)
			{
				itr->second->Print(ID, trip_out, tour_out, person_out);
			}
        }
    };
	
	struct Household_List
    {
        map<int, Household*> Households;

		void Add_Item(int HHID, int PERID, int ACTID, string PURPOSE, int LOCID, int MODE, float ACT_DUR, float TRIP_DUR)
        {
            Activity* a = new Activity(ACTID, PURPOSE, LOCID, MODE,ACT_DUR,TRIP_DUR);

			// Household already exists, add activity to it
            if (Households.find(HHID) != Households.end())
            {
                Household* h = Households[HHID];

				// Person already exists, add activity
                if (h->Persons.find(PERID) != h->Persons.end())
                {
                    Person* p = h->Persons[PERID];
                    p->Activities.push_back(a);
                }
				// this is a new person, create and add to household
                else
                {
                    Person* p = new Person(PERID, a);
					p->household = h;
                    h->Persons.insert(pair<int,Person*>(PERID, p));
                }
            }
			// This is a new household, create hh and person and add activity
            else
            {
                Person* p = new Person(PERID, a);
                Household* h = new Household(HHID, p);
				p->household = h;
                Households.insert(pair<int,Household*>(HHID, h));

            }

        }
    };
}