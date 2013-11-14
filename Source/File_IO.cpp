#include "File_Reader.h"
#include "File_Writer.h"

namespace File_IO
{
	//================================================================================
	// FILE WRITER METHODS
	bool File_Writer::Open(string filepath)
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

	void File_Writer::Close(void)
	{
		_file.close();
		_open=false;
	}

	void File_Writer::Write(stringstream &S)
	{
		_file<<S.str()<<DELIM;
		S.str("");
	}
	template <typename T>
	void File_Writer::Write(T value)
	{
		_file<<value<<DELIM;
	}

	void File_Writer::Write_Line(stringstream &S)
	{
		_file<<S.str()<<endl;
		S.str("");
	}
	void File_Writer::Write_Line(const char* s)
	{
		_file<<s<<endl;
	}
	template<typename T> void File_Writer::Write_Line(T value)
	{
		_file<<value<<endl;
	}



	//================================================================================
	// FILE READER METHODS
	template<class T>
	bool File_Reader::Get_Data(T& t, int column)
	{
		if (column >= _string_data.size()) 
		{
			return false;
		}
		istringstream iss(_string_data[column]);
		iss>>t;
		return true;
	}

	template<class T>
	bool File_Reader::Get_Data(vector<T> &data, vector<int> columns)
	{
		T t;
		for (vector<int>::iterator itr = columns.begin(); itr != columns.end(); itr++)
		{
			if (Get_Data<T>(t,*itr)) data.push_back(t);
			else {cout<<"ERROR: could not get data from column"; return false;}
		}
		return true;

	}

	bool File_Reader::Open(string filepath, bool header)
	{
		// Attempt to open file
		_file.open(filepath);
		if (!_file.is_open())
		{
			cout<<"Error, file '" + filepath + "' could not be opened";
			_open=false;
		}
		else _open=true;

		// get header row
		if (header)
		{
			string line;
			getline(_file,line);
			tokenize(line,_header);
		}
		return _open;

	}

	void File_Reader::Close(void)
	{
		_file.close();
		_open=false;
	}

	bool File_Reader::Read(void)
	{
		bool ret_val = true;
		if (!_open || _file.eof()) 
		{
			ret_val = false;
			return ret_val;
		}
		string line;
		getline(_file,line);
		_string_data.clear();
		tokenize(line, _string_data, _delims);
		if (_string_data.size() < _header.size())
		{
			return Read();
		}
		return ret_val;
	}

	const string& File_Reader::Get_String(int column)
	{
		return _string_data[column];
	}

	void File_Reader::tokenize(const std::string& str, vector<string>& tokens,
				  const std::string& delimiters, const bool trimEmpty)
	{
	   std::string::size_type pos, lastPos = 0;
	   while(true)
	   {
		  pos = str.find_first_of(delimiters, lastPos);
		  if(pos == std::string::npos)
		  {
			 pos = str.length();

			 if(pos != lastPos || !trimEmpty)
				tokens.push_back(vector<string>::value_type(str.data()+lastPos,
					  (vector<string>::value_type::size_type)pos-lastPos ));

			 break;
		  }
		  else
		  {
			 if(pos != lastPos || !trimEmpty)
				tokens.push_back(vector<string>::value_type(str.data()+lastPos,
					  (vector<string>::value_type::size_type)pos-lastPos ));
		  }

		  lastPos = pos + 1;
	   }
	};
}