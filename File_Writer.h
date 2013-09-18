#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;


namespace File_IO
{

	//---------------------------------------------------------
	//	FILE READER (i.e. PUMA, SF3, etc.)
	//---------------------------------------------------------

	class File_Writer
	{
	public:
		File_Writer(){_open=false; }
		bool Open(string filepath)		
		{
			// Attempt to open file
			_file.open(filepath, ios::out);
			if (!_file.is_open())
			{
				cout<<"Error, file '" + filepath + "' could not be opened";
				_open=false;
			}
			else _open=true;

			return _open;

		}
		void Close()
		{
			_file.close();
			_open=false;
		}

		template<typename T> void Write(T value)
		{
			_file<<value<<DELIM;
		}
		template<typename T> void Write_Line(T value)
		{
			_file<<value<<endl;
		}
		void Write(stringstream &S)
		{
			_file<<S.str()<<DELIM;
			S.str("");
		}
		void Write_Line(stringstream &S)
		{
			_file<<S.str()<<endl;
			S.str("");
		}
		void Write_Line(const char* s)
		{
			_file<<s<<endl;
		}
		void Write_Line(void){_file<<endl;}
		static const char DELIM = '\t';

	protected:
		ofstream _file;
		bool _open;
	
	};

}