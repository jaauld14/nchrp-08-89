#pragma once
#include "Includes.h"

namespace Data_reduction
{
	struct Activity
    {
		int ID;
        string Purpose;
        int Mode;
        float Trip_Dur;
        float Act_Dur;
        int Loc_ID;
        Activity(int id, string purpose, int locid, int mode, float act_dur, float trip_dur)
        {
            ID = id;
            Purpose = purpose;
            Mode = mode;
            Act_Dur = act_dur;
            Trip_Dur = trip_dur;
            Loc_ID = locid;
        }
		bool operator==(const Activity& obj)
		{
			return (ID == obj.ID && Purpose == obj.Purpose && Mode == obj.Mode && Trip_Dur == obj.Trip_Dur && Act_Dur == obj.Act_Dur && Loc_ID == obj.Loc_ID);
		}
		Activity(const Activity& obj)
		{
			ID = obj.ID;
			Purpose = obj.Purpose;
			Mode = obj.Mode;
			Trip_Dur = obj.Trip_Dur;
			Act_Dur = obj.Act_Dur;
			Loc_ID = obj.Loc_ID;
		}
		Activity()
		{
			ID = 0;
			Purpose = "";
			Mode =0;
			Trip_Dur =0;
			Act_Dur = 0;
			Loc_ID = 0;
		}
        string Get_Mode()
        {
            if (Mode == 1) return "NM";
            if (Mode == 2) return "NM";
            if (Mode == 3) return "SOV";
            if (Mode == 4) return "HOV";
            if (Mode == 5) return "PUBLIC";
            if (Mode == 6) return "PUBLIC";
            if (Mode == 7) return "SOV";
            if (Mode == 8) return "PUBLIC";
            if (Mode == 9) return "HOV";
            if (Mode == 10) return "Other";
            if (Mode == 11) return "Other";
            if (Mode == 97) return "Other";
            return "Other";

        }
    };

}
