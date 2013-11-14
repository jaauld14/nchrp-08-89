#include "Household.h"
#include <cassert>

using namespace Data_reduction;

int SURVEY_DAYS;
float SURVEY_DAY_CORRECTION;

int main(int argc, char* argv[])
{
	cout << "*******************************************************************"<<endl;
	cout << "* NCHRP 08-89: Applying GPS Data to Understand Travel Behavior"<<endl;
	cout << "* GPS data reduction program."<<endl;
	cout << "* Joshua Auld, 05-27-13"<<endl;
	cout << endl;
	cout << "---------------------------------------------------------"<<endl;
	cout << " Command Line Arguments: <filename> <length of survey in days>"<<endl<<endl;
	cout << "---------------------------------------------------------"<<endl;
	cout << "Program inputs: tour_input.txt - tab delimited text file with the following data items (in this order):"<<endl<<endl;
	cout << "Header format:"<<endl;
	cout << "Variable_Name:\t\tDescription:\t\t\tType:\tCategories:"<<endl;
	cout << "--------------\t\t------------\t\t\t-----\t-----------"<<endl;
	cout << "1. HH_ID\t\tUnique household identifier\tinteger\tNA"<<endl;
	cout << "2. PERSON_ID\t\tPerson number within household\tinteger\tNA"<<endl;
	cout << "3. ACT_ID\t\tActivity number for the person\tinteger\tNA"<<endl;
	cout << "4. ACTIVITY_LOC_TYPE\tBasic Location Type\t\tstring\t{\"Home\",\"School\",\"Other\"}"<<endl;
	cout << "5. LOCATION_ID\t\tUnique location identifier\tinteger\tNA"<<endl;
	cout << "6. MODE_ID\t\tMode Identifier\t\t\tinteger\t{1=non-motorized,3=SOV,4=HOV,5=Public,10=Other}"<<endl;
	cout << "7. TRIP_DURATION\tTravel time in minutes\t\tinteger\tNA"<<endl;
	cout << "8. ACT_DURATION\t\tActivity duration in minutes\tinteger\tNA"<<endl;
	cout << "---------------------------------------------------------"<<endl;
	cout << "Program outputs:"<<endl;
	cout << "trip_info.xls\t\ttrip level derived characteristics"<<endl;
	cout << "tour_info.xls\t\ttour level derived characteristics"<<endl;
	cout << "person_info.xls\t\taggregate person level travel pattern characteristics"<<endl;
	cout << "---------------------------------------------------------"<<endl<<endl;


	File_Writer tour_out;
	File_Writer trip_out;
	File_Writer person_out;

	//--------------------------------------------------
	// open input file - either from command line arg or request from user
	string filename;
	if (argc > 1)
	{
		filename = argv[1];
	}
	else
	{
		cout << "Enter input file name: ";
		getline(cin,filename);
	}
	if (argc > 2)
	{
		stringstream s;
		s << argv[2];
		s >> SURVEY_DAYS;
	}
	else
	{
		//--------------------------------------------------
		// Get survey length in days so daily averages can be calculated
		cout << endl << "Enter number of days data was collected for in input file: ";
		cin >> SURVEY_DAYS;
		assert(SURVEY_DAYS > 0);
	}

	// get output files ready
	string filename_extract = filename.substr(0,filename.size()-4);

	stringstream tour_name; tour_name << filename_extract << "_tour_info.txt";
	stringstream trip_name; trip_name << filename_extract << "_trip_info.txt";
	stringstream per_name; per_name << filename_extract << "_person_info.txt";

    //tour_out.Open("tour_info2.txt");
    //trip_out.Open("trip_info2.txt");
    //person_out.Open("person_info2.txt");
	tour_out.Open(tour_name.str());
    trip_out.Open(trip_name.str());
    person_out.Open(per_name.str());

	SURVEY_DAY_CORRECTION = 2.0f / (float) SURVEY_DAYS;

    File_Reader file;
	if (!file.Open(filename,true)) {cin >> filename; return 1;}


    Household_List households;
	string s;
	int i=0;

	//--------------------------------------------------
    // Read household data
    while (file.Read())
    {
		// Basic input variales
		int HHID, PERID, ACTID, LOCID, MODE;
		string PURPOSE;
		float ACTDUR, TRIPDUR;

		file.Get_Data<int>(HHID,0);
		file.Get_Data<int>(PERID,1);
		file.Get_Data<int>(ACTID,2);
		PURPOSE = file.Get_String(3);
		file.Get_Data<int>(LOCID,4);
		file.Get_Data<int>(MODE,5);
		file.Get_Data<float>(TRIPDUR,6);
		file.Get_Data<float>(ACTDUR,7);

		//--------------------------------------------------
		// create new household
        households.Add_Item(HHID, PERID, ACTID, PURPOSE, LOCID, MODE, ACTDUR, TRIPDUR);
		if (i % 100 == 0) cout << "Reading..."<<i<<"\r"; 
		i++;
    }
    tour_out.Write_Line("SAMPN\tPERNO\tTOURNO\tTOUR_TYPE\tIS_SUBTOUR\tACTDUR\tTRIPDUR\tMODE\tMAIN_STOP_TYPE\tMAIN_STOP_ACTDUR\tMAIN_STOP_TRIPDUR\tNUM_STOPS\tFULLY_JOINT\tPARTIAL_JOINT");
    trip_out.Write_Line("SAMPN\tPERNO\tTOURNO\tPLANNO\tPURP");
    person_out.Write_Line("HHID\tPERID\ttotal_tours\tnum_subtours\tnum_primary_tours\twork_tours\twork_subtours\tschool_tours\tschool_subtours\tother_tours\tother_subtours\tavg_stops_per_tour\tavg_stops_per_work_tour\tavg_stops_per_school_tour\tavg_stops_per_other_tour\tavg_tour_ttime\tavg_work_tour_ttime\tavg_school_tour_ttime\tavg_other_tour_ttime\tat_home_duration\tnum_acts_work\ttotal_dur_work\tavg_dur_work\tnum_acts_school\ttotal_dur_school\tavg_dur_school\tnum_acts_pickdrop\ttotal_dur_pickdrop\tavg_dur_pickdrop\tnum_acts_other\ttotal_dur_other\tavg_dur_other\tauto_total\tauto_work\tauto_school");
	cout << endl;

	i=0;
	for (map<int,Household*>::iterator itr = households.Households.begin(); itr != households.Households.end(); ++itr,++i)
	{
        // process household
        itr->second->Process();
        // then print it
        itr->second->Print(trip_out, tour_out, person_out);
		if (i % 100 == 0) cout << "Processing..."<<i<<"\r";
    }

	cout <<endl<<"Done."<<endl<<"Total Households Processed: "<< households.Households.size();
	cout <<endl<<endl<<"Writing output files...";
		

    tour_out.Close();
    trip_out.Close();
    person_out.Close();
        
	cout <<"done. Press any key to end"<<endl;

	char pause;
	cin >> pause;
	return 0;
}
