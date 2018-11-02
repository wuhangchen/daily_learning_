
using namespace self{
	class string{
		public:
			string(const char* str);
			string(const string &rhs);
			~string();
			string& operator=(const string &rhs);
			char& operator[](int n)const;
			size_t size()const ;
			const char* c_str()const;
		private:
			char* data;
			size_t length;
	};

	string::string(const char *str){
		if(str==nullptr){
			length=0;
			data=new char[1];
			*data='\0';
		}else{
			length=strlen(str);
			data=new char[length+1];
			strcpy(data,str);
		}
	}

	string::string(const string &rhs){
		length=str.size();
		data=new char[length+1];
		strcpy(data,str.c_str());
	}

	string& string::operator=(const string &rhs){
		if(this == &rhs)
			return *this;
		delete []data;
		length=rhs.length;
		data=new char[length+1];
		strcpy(data,str.c_str());
		return *this;
	}
	inline size_t string::size()const{
		return length;
	}
	inline const char* string::c_str()const{
		return data;
	}

	inline char& string::operator[](int n)const{
		if(n>=length)
			return data[length-1];
		else
			return data[n];
	}

	inline bool string::operator==(const string &rhs)const
	{
		if(length!=rhs.length)return false;
		else 
			return strcmp(data,str.data)?false:true;
	}
}
