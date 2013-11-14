#pragma once

#include <cstdlib>
#include <cstdio>
#include <map>
#include <list>
#include <vector>
#include <set>
#include "File_Reader.h"
#include "File_Writer.h"

using namespace std;
using namespace File_IO;

extern int SURVEY_DAYS;
extern float SURVEY_DAY_CORRECTION;

namespace Data_reduction
{
	struct Household;
	struct Person;
	struct Activity;
	struct Tour;
	struct Household_List;
}