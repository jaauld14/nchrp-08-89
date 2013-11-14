[ModelDescription]


[Choice]
EDUCA   

[Beta]
// Name Value  LowerBound UpperBound  status (0=variable, 1=fixed)
ASC1	0	-10	10	1
ASC2	2.25	-10	10	1
ASC3	1.92	-10	10	1
B2_Employment_Density	0.752	-10	10	1
B2_Pop_Denssity	-0.158	-10	10	1
B2_num_acts_other	0.235	-10	10	1
B2_road_density	-0.102	-10	10	1
B2_total_dur_pickdrop	-0.0968	-10	10	1
B3_Employment_Density	0.973	-10	10	1
B3_Pop_Denssity	-0.257	-10	10	1
B3_intersection_density	-0.0111	-10	10	1
B3_num_acts_other	0.317	-10	10	1
B3_total_dur_pickdrop	-0.0688	-10	10	1

				
				
				
[Utilities]				
// ID	Name	Avail	linear-in-parameter	expression
1	NOHS	one	ASC1 * one	
2	HS	one	ASC2 * one + //B2_avg_stops_per_tour * avg_stops_per_tour + 	
			//B2_avg_stops_per_work_tour * avg_stops_per_work_tour + 	
			//B2_avg_stops_per_school_tour * avg_stops_per_school_tour + 	
			//B2_avg_stops_per_other_tour * avg_stops_per_other_tour + 	
			//B2_avg_tour_ttime * avg_tour_ttime + 	
			//B2_avg_work_tour_ttime * avg_work_tour_ttime + 	
			//B2_avg_school_tour_ttime * avg_school_tour_ttime + 	
			//B2_avg_other_tour_ttime * avg_other_tour_ttime + 	
			//B2_at_home_duration * at_home_duration + 	
			//B2_num_acts_work * num_acts_work + 	
			//B2_total_dur_work * total_dur_work + 	
			//B2_num_acts_school * num_acts_school + 	
			//B2_total_dur_school * total_dur_school + 	
			//B2_num_acts_pickdrop * num_acts_pickdrop + 	
			B2_total_dur_pickdrop * total_dur_pickdrop + 	
			B2_num_acts_other * num_acts_other + 	
			//B2_total_dur_other * total_dur_other + 	
			B2_road_density * road_density + 	
			//B2_intersection_density * intersection_density + 	
			//B2_block_size * block_size + 	
			B2_Employment_Density * Employment_Density + 	
			B2_Pop_Denssity * Pop_Denssity 	
			//B2_Housing_Density * Housing_Density	
3	COLL	one	ASC3 * one + //B3_avg_stops_per_tour * avg_stops_per_tour + 	
			//B3_avg_stops_per_work_tour * avg_stops_per_work_tour + 	
			//B3_avg_stops_per_school_tour * avg_stops_per_school_tour + 	
			//B3_avg_stops_per_other_tour * avg_stops_per_other_tour + 	
			//B3_avg_tour_ttime * avg_tour_ttime + 	
			//B3_avg_work_tour_ttime * avg_work_tour_ttime + 	
			//B3_avg_school_tour_ttime * avg_school_tour_ttime + 	
			//B3_avg_other_tour_ttime * avg_other_tour_ttime + 	
			//B3_at_home_duration * at_home_duration + 	
			//B3_num_acts_work * num_acts_work + 	
			//B3_total_dur_work * total_dur_work + 	
			//B3_num_acts_school * num_acts_school + 	
			//B3_total_dur_school * total_dur_school + 	
			//B3_num_acts_pickdrop * num_acts_pickdrop + 	
			B3_total_dur_pickdrop * total_dur_pickdrop + 	
			B3_num_acts_other * num_acts_other + 	
			//B3_total_dur_other * total_dur_other + 	
			//B3_road_density * road_density + 	
			B3_intersection_density * intersection_density + 	
			//B3_block_size * block_size + 	
			B3_Employment_Density * Employment_Density + 	
			B3_Pop_Denssity * Pop_Denssity 	
			//B3_Housing_Density * Housing_Density	




[Expressions] 
one = 1

[Model]
$MNL
