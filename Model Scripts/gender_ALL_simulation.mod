[ModelDescription]


[Choice]
GEND   

[Beta]
// Name Value  LowerBound UpperBound  status (0=variable, 1=fixed)
ASC1	0	-10	10	1
ASC2	0.0261	-10	10	1
B1_Employment_Density	0.0532	-10	10	1
B1_Housing_Density	-0.0675	-10	10	1
B1_Pop_Denssity	0.0206	-10	10	1
B1_avg_other_tour_ttime	0.00309	-10	10	1
B1_avg_school_tour_ttime	0.00332	-10	10	1
B1_avg_stops_per_tour	-0.102	-10	10	1
B1_avg_stops_per_work_tour	-0.0697	-10	10	1
B1_avg_work_tour_ttime	0.00303	-10	10	1
B1_num_acts_pickdrop	-0.152	-10	10	1
B1_num_acts_school	0.144	-10	10	1
B1_num_acts_work	-0.218	-10	10	1
B1_road_density	-0.0213	-10	10	1
B1_total_dur_work	0.000939	-10	10	1

				
[Utilities]				
// ID	Name	Avail	linear-in-parameter	expression
1	MALE	one	B1_avg_stops_per_tour * avg_stops_per_tour + 	
			B1_avg_stops_per_work_tour * avg_stops_per_work_tour + 	
			//B1_avg_stops_per_school_tour * avg_stops_per_school_tour + 	
			//B1_avg_stops_per_other_tour * avg_stops_per_other_tour + 	
			//B1_avg_tour_ttime * avg_tour_ttime + 	
			B1_avg_work_tour_ttime * avg_work_tour_ttime + 	
			B1_avg_school_tour_ttime * avg_school_tour_ttime + 	
			B1_avg_other_tour_ttime * avg_other_tour_ttime + 	
			//B1_at_home_duration * at_home_duration + 	
			B1_num_acts_work * num_acts_work + 	
			B1_total_dur_work * total_dur_work + 	
			B1_num_acts_school * num_acts_school + 	
			//B1_total_dur_school * total_dur_school + 	
			B1_num_acts_pickdrop * num_acts_pickdrop + 	
			//B1_total_dur_pickdrop * total_dur_pickdrop + 	
			//B1_num_acts_other * num_acts_other + 	
			//B1_total_dur_other * total_dur_other + 	
			B1_road_density * road_density + 	
			//B1_intersection_density * intersection_density + 	
			//B1_block_size * block_size + 	
			B1_Employment_Density * Employment_Density + 	
			B1_Pop_Denssity * Pop_Denssity + 	
			B1_Housing_Density * Housing_Density 	
			//B1_auto_total * auto_total + 	
			//B1_auto_work * auto_work + 	
			//B1_auto_school * auto_school	
2	FEMALE	one	ASC2 * one	




[Expressions] 
one = 1

[Model]
$MNL
