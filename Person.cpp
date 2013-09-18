#include "Person.h"
#include "Household.h"


namespace Data_reduction
{
    
	void Person::Process_Activity_Locations()
	{
		//---------------------------------------------------------------------------------------------
		// get the school location
		for (list<Activity*>::iterator aitr = Activities.begin(); aitr != Activities.end(); ++aitr)
        {
			// if simple activity type is school, set the school location and ignore for further calculation
			if ((*aitr)->Purpose == "School")
			{
				this->school_locations.insert((*aitr)->Loc_ID);
				break;
			}
		}

		//---------------------------------------------------------------------------------------------
		// build the count of locations and time spent at locations
		map<int,pair<int,int>> location_count_duration_container;
		map<int,pair<int,int>>::iterator loc_itr;
		for (list<Activity*>::iterator aitr = Activities.begin(); aitr != Activities.end(); ++aitr)
        {
			// if simple activity type is school, set the school location and ignore for further calculation
			if ((*aitr)->Purpose == "School") continue;
			// if it is home, ignore for further calculations
			else if ((*aitr)->Purpose == "Home") continue;


			// Otherwise, update the count-duration totals for the location
			// new location
            if ((loc_itr = location_count_duration_container.find((*aitr)->Loc_ID)) == location_count_duration_container.end())
			{
				location_count_duration_container.insert(pair<int,pair<int,int>>((*aitr)->Loc_ID,pair<int,int>(1,(*aitr)->Act_Dur)));
			}
			// otherwise, update existing location with new activity info
			else
			{
				loc_itr->second.first++;
				loc_itr->second.second+=(*aitr)->Act_Dur;
			}
		}

		//---------------------------------------------------------------------------------------------
		// evaluate each non-home/non-school activity to determine if it is a workplace - using estimated decision rules
		for (loc_itr = location_count_duration_container.begin(); loc_itr != location_count_duration_container.end(); ++loc_itr)
		{
			if (loc_itr->second.first > 4 * SURVEY_DAYS) this->work_locations.insert(loc_itr->first);
			else if (loc_itr->second.second > 250 * SURVEY_DAYS) this->work_locations.insert(loc_itr->first);
			else if (loc_itr->second.first > 3 * SURVEY_DAYS && loc_itr->second.second > 120 * SURVEY_DAYS) this->work_locations.insert(loc_itr->first);
		}
	}
    void Person::Print(int HHID, File_Writer& trip_out, File_Writer& tour_out, File_Writer& person_out)
    {
		for (list<Tour*>::iterator t = Tours.begin(); t != Tours.end(); ++t)
        {
            (*t)->Print(HHID,PERID,tour_out);
            (*t)->Print_Activities(HHID, PERID, trip_out);
        }
        for (list<Tour*>::iterator s = Sub_Tours.begin(); s != Sub_Tours.end(); ++s)
        {
            (*s)->Print(HHID,PERID,tour_out);
            (*s)->Print_Activities(HHID, PERID, trip_out);
        }

        int num_tours = Tours.size();
        int num_subtours = Sub_Tours.size();
        int work_tours = 0;
        int disc_tours = 0;
        int maint_tours = 0;
        int other_tours = 0;
        int school_tours = 0;
        int disc_subtours = 0;
        int maint_subtours = 0;
        int other_subtours = 0;
        int work_subtours = 0;
        int school_subtours = 0;
        float num_stops = 0;
        float num_stops_work = 0;
        float num_stops_school = 0;
        float num_stops_pickdrop = 0;
        float num_stops_other = 0;

        float num_acts = 0;
        float num_acts_work = 0;
        float num_acts_school = 0;
        float num_acts_pickdrop = 0;
        float num_acts_other = 0;

        float total_ttime = 0;
        float total_ttime_work = 0;
        float total_ttime_school = 0;
        float total_dur = 0;
        float total_dur_work = 0;
        float total_dur_school = 0;
        float total_dur_other = 0;
        float total_dur_pickdrop = 0;
        float total_joint = 0;
        float total_partial_joint = 0;
        float total_auto_tours = 0;
        float total_auto_work_tours = 0;
        float total_auto_school_tours = 0;
        float percent_auto_tours = 0;

		for (list<Activity*>::iterator aitr = Activities.begin(); aitr != Activities.end(); ++aitr)
		{
			Activity* A = *aitr;
            if (A->Purpose == "School")
            {
                total_dur_school += A->Act_Dur;
                num_acts_school++;
            }
            else if (A->Purpose == "Work")
            {
                total_dur_work += A->Act_Dur;
                num_acts_work++;
            }
            else if (A->Purpose == "Pick_Drop")
            {
                total_dur_pickdrop += A->Act_Dur;
                num_acts_pickdrop++;
            }
            else if (A->Purpose == "Other")
            {
                total_dur_other += A->Act_Dur;
                num_acts_other++;
            }
            num_acts++;
            total_dur += A->Act_Dur;
        }

		for (list<Tour*>::iterator titr = Tours.begin(); titr != Tours.end(); ++titr)
		{
			Tour* t = *titr;
            num_stops += t->num_stops;
            total_ttime += t->Total_Travel_Time;
            //total_dur += t.Total_Activity_Time;
            //if (t->Joint_Tour) total_joint++;
            //if (t->Partial_Joint_Tour) total_partial_joint++;
            if (t->Main_Mode == "SOV" || t->Main_Mode == "HOV") total_auto_tours++;

            if (t->Main_Stop_Type == "Work")
            {
                num_stops_work+= t->num_stops;
                work_tours++;
                total_ttime_work += t->Total_Travel_Time;
                if (t->Main_Mode == "SOV" || t->Main_Mode == "HOV") total_auto_work_tours++;
            }
            else if (t->Main_Stop_Type == "School")
            {
                num_stops_school += t->num_stops;
                school_tours++;
                total_ttime_school += t->Total_Travel_Time;
                if (t->Main_Mode == "SOV" || t->Main_Mode == "HOV") total_auto_school_tours++;
            }
            else
            {
                num_stops_other += t->num_stops;
                other_tours++;
            }
        }
        for (list<Tour*>::iterator titr = Sub_Tours.begin(); titr != Sub_Tours.end(); ++titr)
		{
			Tour* t = *titr;
            num_stops += t->num_stops;
            total_ttime += t->Total_Travel_Time;
            total_dur += t->Total_Activity_Time;
            //if (t->Joint_Tour) total_joint++;
            //if (t->Partial_Joint_Tour) total_partial_joint++;
            if (t->Main_Mode == "SOV" || t->Main_Mode == "HOV") total_auto_tours++;

            //if (t.Main_Stop_Type == "Discretionary") disc_subtours++;
            //if (t.Main_Stop_Type == "Maintenance") maint_subtours++;
            if (t->Main_Stop_Type == "Work")
            {
                num_stops_work += t->num_stops;
                work_tours++;
                work_subtours++;
                total_ttime_work += t->Total_Travel_Time;
                if (t->Main_Mode == "SOV" || t->Main_Mode == "HOV") total_auto_work_tours++;
            }
            else if (t->Main_Stop_Type == "School")
            {
                num_stops_school += t->num_stops;
                school_tours++;
                school_subtours++;
                total_ttime_school += t->Total_Travel_Time;
                if (t->Main_Mode == "SOV" || t->Main_Mode == "HOV") total_auto_school_tours++;
            }
            else
            {
                num_stops_other += t->num_stops;
                other_tours++;
                other_subtours++;
            }
        }

        num_tours = num_tours + num_subtours;

        // write output
        person_out.Write(HHID);
        person_out.Write(PERID);

        // Number of total tours
        person_out.Write(num_tours * SURVEY_DAY_CORRECTION);
        person_out.Write(num_subtours * SURVEY_DAY_CORRECTION); 
        person_out.Write( (num_tours - num_subtours) * SURVEY_DAY_CORRECTION);
        // Number of work tours
        person_out.Write(work_tours * SURVEY_DAY_CORRECTION); 
        person_out.Write(work_subtours * SURVEY_DAY_CORRECTION); 
        // Number of school tours
        person_out.Write(school_tours * SURVEY_DAY_CORRECTION); 
        person_out.Write(school_subtours * SURVEY_DAY_CORRECTION); 
        // Number of other tours
        person_out.Write(other_tours * SURVEY_DAY_CORRECTION); 
        person_out.Write(other_subtours * SURVEY_DAY_CORRECTION); 

        // Avg number of stops
        if (num_tours > 0) person_out.Write(num_stops / (num_tours));
        else person_out.Write(0);
        // Avg stops on work tour
        if (work_tours > 0 ) person_out.Write(num_stops_work / work_tours);
		else person_out.Write(0);
        // Avg stops on school tour
        if (school_tours > 0 ) {person_out.Write(num_stops_school / school_tours); }
        else person_out.Write(0);
        // Avg stops on other tour
        if (other_tours > 0 ) {person_out.Write(num_stops_other / other_tours); }
        else person_out.Write(0);
        // avg tour travel time
        if (num_tours > 0 ) { person_out.Write((total_ttime) / (num_tours)); }
        else person_out.Write(0);
        // avg travel-time work tour
        if (work_tours > 0 ) {person_out.Write((total_ttime_work) / (work_tours)); }
        else person_out.Write(0);
        // avg travel time school
        if (school_tours > 0 ) {person_out.Write((total_ttime_school) / (school_tours)); }
        else person_out.Write(0);
        // avg travel time non-work
        if (other_tours > 0 ) {person_out.Write((total_ttime - total_ttime_school - total_ttime_work) / (other_tours)); }
        else person_out.Write(0);

        // time spent at home
        person_out.Write( (total_dur - total_dur_school - total_dur_work - total_dur_other - total_dur_pickdrop) * SURVEY_DAY_CORRECTION);

        // number of work activities
        person_out.Write(num_acts_work * SURVEY_DAY_CORRECTION);
        // total duration work
        person_out.Write(total_dur_work * SURVEY_DAY_CORRECTION);
        // avg duration work
        if (num_acts_work > 0) person_out.Write((total_dur_work) / num_acts_work);
        else person_out.Write(0);

        // number of school activities
        person_out.Write(num_acts_school * SURVEY_DAY_CORRECTION); 
        // total duration school
        person_out.Write(total_dur_school * SURVEY_DAY_CORRECTION); 
        // avg duration school
        if (num_acts_school > 0){ person_out.Write((total_dur_school) / num_acts_school);}
        else person_out.Write(0);

        // number of pick_drop activities
        person_out.Write(num_acts_pickdrop * SURVEY_DAY_CORRECTION); 
        // total duration pick_drop
        person_out.Write(total_dur_pickdrop * SURVEY_DAY_CORRECTION);
        // avg duration pick_drop
        if (num_acts_pickdrop > 0){ person_out.Write((total_dur_pickdrop) / num_acts_pickdrop); }
        else person_out.Write(0);

        // number of other activities
        person_out.Write(num_acts_other * SURVEY_DAY_CORRECTION);
        // total duration other
        person_out.Write(total_dur_other * SURVEY_DAY_CORRECTION);
        // avg duration other
        if (num_acts_other > 0){ person_out.Write((total_dur_other) / num_acts_other);}
		else person_out.Write(0);

		// percent auto tours total
        if (num_tours > 0) person_out.Write(total_auto_tours / num_tours);
        else person_out.Write(0);
		// percent auto tours to work
        if (work_tours > 0) person_out.Write(total_auto_work_tours / work_tours);
        else person_out.Write(0);
		// percent auto tours to school
        if (school_tours > 0) person_out.Write(total_auto_school_tours / school_tours);
        else person_out.Write(0);

        //// Number of joint tours
        //person_out.Write(total_joint); person_out.Write("\t");
        //// Number of partial joint tours
        //person_out.Write(total_partial_joint); person_out.Write("\t");
        person_out.Write_Line();
    }

	void Person::Process_Tours()
    {
		if (this->household->ID == 4029855 && this->PERID == 3)
		{
			int test;
			test = 1;
		}
		for (list<Activity*>::iterator aitr = Activities.begin(); aitr != Activities.end(); ++aitr)
		{
			if ((*aitr)->Purpose == "Home") Time_At_Home += (*aitr)->Act_Dur;
		}

		// add a dmmy home activity if the person does not start at home
        if ((*(Activities.begin()))->Purpose != "Home")
        {
            Activity* a = new Activity(0, "Home",0,0,0,0);
            Activities.push_front(a);
        }
		if ((*(Activities.rbegin()))->Purpose != "Home")
        {
            Activity* a = new Activity(0, "Home",0,0,0,0);
            Activities.push_back(a);
        }

		Update_Activity_Purposes();
        Process_Tours_Initial();
        Process_Tours_Characteristics();
    }
	void Person::Update_Activity_Purposes()
	{
		//---------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------
		// Update the activity purposes with the estimates for work and pick-drop activities
		set<int>::iterator litr;
		for (list<Activity*>::iterator a = Activities.begin(); a != Activities.end(); ++a)
        {
			Activity* aitr = *a;

			// check for all non-home and non-school activities
			if (aitr->Purpose == "School" || aitr->Purpose == "Home" || aitr->Purpose == "Work") continue;

			// if activity location is a work location, set type to work
			//if ((litr = this->work_locations.find(aitr->Loc_ID)) != this->work_locations.end()) aitr->Purpose = "Work";
				
			// next, check if activity location is another household members work or school location for pick-drop purpose; only if duration <= 20
			if (aitr->Act_Dur > 20) continue;

			map<int,Person*>::iterator p_itr = household->Persons.begin();
			for (;p_itr != household->Persons.end(); ++p_itr)
			{
				// don't compare to current person
				if (p_itr->second->PERID == this->PERID) continue;
				// search other persons school/work lists
				if (p_itr->second->school_locations.find(aitr->Loc_ID) != p_itr->second->school_locations.end()) {aitr->Purpose = "Pick_Drop"; break;}
				if (p_itr->second->work_locations.find(aitr->Loc_ID) != p_itr->second->work_locations.end()) {aitr->Purpose = "Pick_Drop"; break;}
			}
				
		}
	}
	void Person::Process_Tours_Initial()
    {
        bool Tour_Started = false;
        int Tour_id = 0;
        Tour* t = new Tour(0, false);

        // Group into main tours
		int i = 0;
		for (list<Activity*>::iterator aitr = Activities.begin(); aitr != Activities.end(); ++aitr, ++i)
        {
            Activity* a = *aitr;

			//---------------------------------
			// start new tour
            if (a->Purpose == "Home" && Tour_Started==false)
            {
                Tour_Started = true;
                t = new Tour(Tour_id, false);
                t->Add_Activity(a);
            }
			//---------------------------------
			// tour ends at home
            else if (a->Purpose == "Home")
            {
                t->Add_Activity(a);
                   
                // don't add a home-home tour, gps misidentification
                if (t->Activities.size() > 2 || (*(Activities.begin()))->Purpose != "Home")
                {
					// also, don't add if two home activities are next to each other at the end (GPS misidentification)
					list<Activity*>::iterator next_act = aitr;
					++next_act;
                    if (next_act != Activities.end())
                    {		
						//-------------------
						// ends tour
                        if ((*next_act)->Purpose != "Home")
                        {
                            Tour_Started = false;
                            Tours.push_back(t);
                            Tour_id++;
                            --aitr;
                        }
                    }
					//-------------------
					// ends tour
                    else
                    {
                        Tour_Started = false;
                        Tours.push_back(t);
                        Tour_id++;
                        --aitr;
                    }                    
                }       
            }

			//---------------------------------
			// add activity to current tour
            else if (Tour_Started == true)
            {
                t->Add_Activity(a);
            }
        }

		//---------------------------------
        // remove degenerate tours
		for (list<Tour*>::iterator itr = Tours.begin(); itr != Tours.end(); ++itr)
		{
			if ((*itr)->Activities.size() <= 1)
            {
                itr = Tours.erase(itr);
				--itr;
            }
		}

		//---------------------------------
        // check for subtours in main tours
        bool Sub_Tour_Started = false;
        int Sub_Tour_id = 0;
        Tour* s = new Tour(0,false);

        for (list<Tour*>::iterator itr = Tours.begin(); itr != Tours.end(); ++itr)
		{
            Sub_Tour_Started = false;

			for (list<Activity*>::iterator aitr = (*itr)->Activities.begin(); aitr != (*itr)->Activities.end(); ++aitr)
            {
                if ((*aitr)->Purpose == "Work" && Sub_Tour_Started == false)
                {
                    Sub_Tour_Started = true;
                    s = new Tour(Sub_Tour_id, true);
                    s->Add_Activity(*aitr);
                }
                else if ((*aitr)->Purpose == "Work")
                {
                    Sub_Tour_Started = false;
                    s->Add_Activity(*aitr);
                    --aitr;

                    // add completed subtour to subtour list, if more than two activities (otherwise it is just part of main tour)
                    if (s->Activities.size() > 2)
                    {
                        s->Primary_Tour_ID = (*itr)->ID;
                        Sub_Tours.push_back(s);
                        Sub_Tour_id++;
                    }
                }
                else if (Sub_Tour_Started == true)
                {
                    s->Add_Activity(*aitr);
                }
            }

			//---------------------------------
			// remove degenerate subtours and remvoe acts in sub_tours from main tour
			for (list<Tour*>::iterator sitr = Sub_Tours.begin(); sitr != Sub_Tours.end(); ++sitr)
			{
				if ((*sitr)->Activities.size() <= 1)
				{
					sitr = Sub_Tours.erase(sitr);
					--sitr;
				}
				else
				{
					for (list<Activity*>::iterator s_act_itr = ++((*sitr)->Activities.begin()); s_act_itr != (*sitr)->Activities.end(); ++s_act_itr) (*itr)->Activities.remove(*s_act_itr);
				}
			}    
		}
    }
    void Person::Process_Tours_Characteristics()
    {
        // foreach (Tour t in Tours)
		for (list<Tour*>::iterator t = Tours.begin(); t != Tours.end(); ++t)
        {
            (*t)->Process();
        }
        for (list<Tour*>::iterator s = Sub_Tours.begin(); s != Sub_Tours.end(); ++s)
        {
            (*s)->Process();
        }
    }
}