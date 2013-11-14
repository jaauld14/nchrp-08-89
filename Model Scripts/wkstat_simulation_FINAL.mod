[ModelDescription]


[Choice]
PERSON_CLUSTER  

[Beta]
// Name Value  LowerBound UpperBound  status (0=variable, 1=fixed)
ASC1	-0.848	-10	10	1
ASC2	-1.28	-10	10	1
ASC3	1.31	-10	10	1
ASC4	0.92	-10	10	1
ASC5	0	-10	10	1
ASC6	0.6	-10	10	1
B1_num_acts_other	0.0868	-10	10	1
B1_num_acts_work	3.02	-10	10	1
B2_Employment_Density	0.176	-10	10	1
B2_Housing_Density	-0.199	-10	10	1
B2_avg_stops_per_tour	0.161	-10	10	1
B2_avg_tour_ttime	0.00433	-10	10	1
B2_num_acts_school	-1.62	-10	10	1
B2_num_acts_work	2.76	-10	10	1
B2_total_dur_other	0.000517	-10	10	1
B2_total_dur_work	0.00234	-10	10	1
B3_num_acts_other	-0.0513	-10	10	1
B3_num_acts_school	-3.15	-10	10	1
B3_total_dur_pickdrop	-0.0752	-10	10	1
B4_Employment_Density	0.238	-10	10	1
B4_Housing_Density	-0.217	-10	10	1
B4_avg_tour_ttime	-0.0131	-10	10	1
B4_num_acts_other	-0.149	-10	10	1
B4_total_dur_pickdrop	0.0172	-10	10	1
B5_Employment_Density	0.158	-10	10	1
B5_Housing_Density	-0.172	-10	10	1
B5_num_acts_other	-0.152	-10	10	1
B5_total_dur_other	0.000425	-10	10	1
B5_total_dur_pickdrop	-0.0963	-10	10	1
B5_total_dur_school	0.00264	-10	10	1
IV_FULL_EDUC	0.217	-10	10	1
IV_OTHER_EDUC	0.125	-10	10	1
IV_PART_EDUC	0.116	-10	10	1
IV_RET_EDUC	0.0522	-10	10	1

					
					
[Utilities]					
// ID	Name	Avail	linear-in-parameter	expression	
1	PART	one	ASC1 * one + //B1_avg_stops_per_tour * avg_stops_per_tour + 		
			//B1_avg_stops_per_work_tour * avg_stops_per_work_tour + 		
			////B1_avg_stops_per_school_tour * avg_stops_per_school_tour + 		
			////B1_avg_stops_per_other_tour * avg_stops_per_other_tour + 		
			//B1_avg_tour_ttime * avg_tour_ttime + 		
			//B1_avg_work_tour_ttime * avg_work_tour_ttime + 		
			//B1_avg_school_tour_ttime * avg_school_tour_ttime + 		
			//B1_avg_other_tour_ttime * avg_other_tour_ttime + 		
			//B1_at_home_duration * at_home_duration + 		
			B1_num_acts_work * num_acts_work + 		
			//B1_total_dur_work * total_dur_work + 		
			//B1_num_acts_school * num_acts_school + 		
			//B1_total_dur_school * total_dur_school + 		
			//B1_num_acts_pickdrop * num_acts_pickdrop + 		
			//B1_total_dur_pickdrop * total_dur_pickdrop + 		
			B1_num_acts_other * num_acts_other + 		
			//B1_total_dur_other * total_dur_other + 		
			//B1_road_density * road_density + 		
			//B1_intersection_density * intersection_density + 		
			//B1_block_size * block_size + 		
			//B1_Employment_Density * Employment_Density + 		
			//B1_Pop_Denssity * Pop_Denssity + 		
			//B1_Housing_Density * Housing_Density +		
			IV_PART_EDUC * IV_PART		
2	FULL	one	ASC2 * one + B2_avg_stops_per_tour * avg_stops_per_tour + 		
			//B2_avg_stops_per_work_tour * avg_stops_per_work_tour + 		
			////B2_avg_stops_per_school_tour * avg_stops_per_school_tour + 		
			////B2_avg_stops_per_other_tour * avg_stops_per_other_tour + 		
			B2_avg_tour_ttime * avg_tour_ttime + 		
			//B2_avg_work_tour_ttime * avg_work_tour_ttime + 		
			//B2_avg_school_tour_ttime * avg_school_tour_ttime + 		
			//B2_avg_other_tour_ttime * avg_other_tour_ttime + 		
			//B2_at_home_duration * at_home_duration + 		
			B2_num_acts_work * num_acts_work + 		
			B2_total_dur_work * total_dur_work + 		
			B2_num_acts_school * num_acts_school + 		
			//B2_total_dur_school * total_dur_school + 		
			//B2_num_acts_pickdrop * num_acts_pickdrop + 		
			//B2_total_dur_pickdrop * total_dur_pickdrop + 		
			//B2_num_acts_other * num_acts_other + 		
			B2_total_dur_other * total_dur_other + 		
			//B2_road_density * road_density + 		
			//B2_intersection_density * intersection_density + 		
			//B2_block_size * block_size + 		
			B2_Employment_Density * Employment_Density + 		
			//B2_Pop_Denssity * Pop_Denssity + 		
			B2_Housing_Density * Housing_Density +		
			IV_FULL_EDUC * IV_FULL		
3	RETIRE	one	ASC3 * one + //B3_avg_stops_per_tour * avg_stops_per_tour + 		
			////B3_avg_stops_per_work_tour * avg_stops_per_work_tour + 		
			////B3_avg_stops_per_school_tour * avg_stops_per_school_tour + 		
			////B3_avg_stops_per_other_tour * avg_stops_per_other_tour + 		
			//B3_avg_tour_ttime * avg_tour_ttime + 		
			//B3_avg_work_tour_ttime * avg_work_tour_ttime + 		
			//B3_avg_school_tour_ttime * avg_school_tour_ttime + 		
			//B3_avg_other_tour_ttime * avg_other_tour_ttime + 		
			//B3_at_home_duration * at_home_duration + 		
			//B3_num_acts_work * num_acts_work + 		
			//B3_total_dur_work * total_dur_work + 		
			B3_num_acts_school * num_acts_school + 		
			//B3_total_dur_school * total_dur_school + 		
			//B3_num_acts_pickdrop * num_acts_pickdrop + 		
			B3_total_dur_pickdrop * total_dur_pickdrop + 		
			B3_num_acts_other * num_acts_other + 		
			//B3_total_dur_other * total_dur_other + 		
			//B3_road_density * road_density + 		
			//B3_intersection_density * intersection_density + 		
			//B3_block_size * block_size + 		
			//B3_Employment_Density * Employment_Density + 		
			//B3_Pop_Denssity * Pop_Denssity + 		
			//B3_Housing_Density * Housing_Density +		
			IV_RET_EDUC * IV_RET		
4	CHILD	one	ASC4 * one + //B4_avg_stops_per_tour * avg_stops_per_tour + 		
			////B4_avg_stops_per_work_tour * avg_stops_per_work_tour + 		
			//B4_avg_stops_per_school_tour * avg_stops_per_school_tour + 		
			//B4_avg_stops_per_other_tour * avg_stops_per_other_tour + 		
			B4_avg_tour_ttime * avg_tour_ttime + 		
			//B4_avg_work_tour_ttime * avg_work_tour_ttime + 		
			//B4_avg_school_tour_ttime * avg_school_tour_ttime + 		
			//B4_avg_other_tour_ttime * avg_other_tour_ttime + 		
			//B4_at_home_duration * at_home_duration + 		
			//B4_num_acts_work * num_acts_work + 		
			//B4_total_dur_work * total_dur_work + 		
			//B4_num_acts_school * num_acts_school + 		
			//B4_total_dur_school * total_dur_school + 		
			//B4_num_acts_pickdrop * num_acts_pickdrop + 		
			B4_total_dur_pickdrop * total_dur_pickdrop + 		
			B4_num_acts_other * num_acts_other + 		
			//B4_total_dur_other * total_dur_other + 		
			//B4_road_density * road_density + 		
			//B4_intersection_density * intersection_density + 		
			//B4_block_size * block_size + 		
			B4_Employment_Density * Employment_Density + 		
			//B4_Pop_Denssity * Pop_Denssity + 		
			B4_Housing_Density * Housing_Density		
5	STUDENT	one	ASC5 * one + //B5_avg_stops_per_tour * avg_stops_per_tour + 		
			////B5_avg_stops_per_work_tour * avg_stops_per_work_tour + 		
			//B5_avg_stops_per_school_tour * avg_stops_per_school_tour + 		
			//B5_avg_stops_per_other_tour * avg_stops_per_other_tour + 		
			//B5_avg_tour_ttime * avg_tour_ttime + 		
			//B5_avg_work_tour_ttime * avg_work_tour_ttime + 		
			//B5_avg_school_tour_ttime * avg_school_tour_ttime + 		
			//B5_avg_other_tour_ttime * avg_other_tour_ttime + 		
			//B5_at_home_duration * at_home_duration + 		
			//B5_num_acts_work * num_acts_work + 		
			//B5_total_dur_work * total_dur_work + 		
			//B5_num_acts_school * num_acts_school + 		
			B5_total_dur_school * total_dur_school + 		
			//B5_num_acts_pickdrop * num_acts_pickdrop + 		
			B5_total_dur_pickdrop * total_dur_pickdrop + 		
			B5_num_acts_other * num_acts_other + 		
			B5_total_dur_other * total_dur_other + 		
			//B5_road_density * road_density + 		
			//B5_intersection_density * intersection_density + 		
			//B5_block_size * block_size + 		
			B5_Employment_Density * Employment_Density + 		
			//B5_Pop_Denssity * Pop_Denssity + 		
			B5_Housing_Density * Housing_Density		
6	OTHER	one	ASC6 * one +		
			IV_OTHER_EDUC * IV_OTHER		






[Expressions] 
one = 1

[Model]
$MNL

