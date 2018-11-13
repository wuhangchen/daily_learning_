namespace self{
	class string{
		public:
			string();
			string(char* rhs=nullptr);
			string(const string &rhs);
			~string();
			string& operator=(const string& rhs);
		private:
			char *str;
	};
	

	string& string::operator=(const self::string &rhs){
	#ifdef VERSION_ONE
		if(*this==rhs)
			return *this;
		delete[] str;
		str = nullptr;
		//拷贝赋值是深拷贝
		str = new char[strlen(rhs.str)+1];
		strcpy(str,rhs.str);
	}
	#else
		if(*this!=rhs){
			string other(rhs);
			char *pother = other.str;
			other.str = str;
			str = pother;
		}
		return *this;
	}
	#endif

