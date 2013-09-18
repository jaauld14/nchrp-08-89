#pragma once
#include "Includes.h"
#include "Activity.h"

namespace Data_reduction
{
	struct Tour
    {
        string Tour_Type()
        {
			stringstream t;
            if (Activities.size() <= 1) return "";
            t << (*(Activities.begin()))->Purpose[0];
			for (list<Activity*>::iterator itr = Activities.begin(); itr != Activities.end(); ++itr)
            {
                t << (*itr)->Purpose[0];
            }
            return t.str();
        }
		int ID;
		int Primary_Tour_ID;
		string Main_Stop_Type;
		float Main_Stop_Duration;
		string Main_Mode;
		//bool Joint_Tour;
		//bool Partial_Joint_Tour;
		float Main_Mode_Duration;
		float Total_Travel_Time;
		float Total_Activity_Time;
		int count;
		int num_stops;
		bool Is_Subtour;
		list<Activity*> Activities;
		void Add_Activity(Activity* a)
        {
            string s = a->Purpose;
            Activities.push_back(a);
            count++;
        }

        Tour(int id, bool subtour)
        {
            count = 0;
            ID = id;
            Primary_Tour_ID = 0;
            Is_Subtour = subtour;
        }

        void Process()
        {
            // tour characteristics
            float sum_travel = 0;
            float sum_act_dur = 0;
            float max_act_dur = -1;
            int main_act_id = 1;
			num_stops=0;

            //Joint_Tour = true;
            //Partial_Joint_Tour = false;

			Activity* main_act = *(Activities.begin());

			for (list<Activity*>::iterator aitr = ++Activities.begin(); aitr != --Activities.end(); ++aitr)
			{	
				Activity* A = *aitr;
                // Joint activities not assumed to be identifiable - only available if data from HH survey tracking
                //if (A->Others_Involved > 0) Partial_Joint_Tour = false;
                //if (A->Others_Involved == 0) Joint_Tour = false;

                // see if current act is the primary act.
                if (A->Act_Dur > max_act_dur && A->Purpose != "Home")
                {
                    main_act = A;
                    max_act_dur = A->Act_Dur;
                }

                // count the tour stops
                num_stops++;
                
                // update the tour sums
                sum_travel += A->Trip_Dur;
                sum_act_dur += A->Act_Dur;
            }
            // update the tour with primary activity attributes
            Activity Main_Act = *main_act;
            Total_Activity_Time = sum_act_dur;
            Total_Travel_Time = sum_travel;
            Main_Stop_Type = Main_Act.Purpose;
            Main_Mode = Main_Act.Get_Mode();
            Main_Mode_Duration = Main_Act.Trip_Dur;
            Main_Stop_Duration = Main_Act.Act_Dur;
        }
        void Print(int HHID, int PERID, File_Writer& out_file)
        {
			out_file.Write(HHID);
			out_file.Write(PERID);

            if (!Is_Subtour)
            {
                out_file.Write(ID+1);    
            }
            else
            {
				stringstream s("");
				s << Primary_Tour_ID+1;
				s<<"."<<ID+1;
				out_file.Write(s.str());
            }
            out_file.Write(Tour_Type());
			if(Is_Subtour) out_file.Write("TRUE");
			else out_file.Write("FALSE");
			out_file.Write(Total_Activity_Time);
			out_file.Write(Total_Travel_Time);
			out_file.Write(Main_Mode);
            out_file.Write(Main_Stop_Type);
			out_file.Write(Main_Stop_Duration);
			out_file.Write(Main_Mode_Duration);
            out_file.Write(Activities.size() - 2);
			/*if (Joint_Tour) out_file.Write("TRUE");
			else out_file.Write("FALSE");
			if(Partial_Joint_Tour) out_file.Write_Line("TRUE");
			else out_file.Write_Line("FALSE");*/
        }
        void Print_Activities(int HHID, int PERID, File_Writer& out_file)
        {
            stringstream tour_id("");
            if (!Is_Subtour) tour_id << (ID + 1);
            else tour_id << (Primary_Tour_ID + 1) << "." << (ID + 1);

			for (list<Activity*>::iterator itr = Activities.begin(); itr != Activities.end(); ++itr)
            {
                out_file.Write(HHID);
				out_file.Write(PERID);
				out_file.Write(tour_id.str());
				out_file.Write((*itr)->ID);
				out_file.Write_Line((*itr)->Purpose);
            }
        }

    };

}