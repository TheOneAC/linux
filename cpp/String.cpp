class String{
	String(const char*str = NULL);
	String(const String &another);
	~String();
	String& operator = (const String &rhs);
	size_t size();
	char & operator [] (size_t i){
		return m_data[i];
	}
private:
	char * m_data;
}
String::String(const char* str = NULL){
	if(str == NULL){
		m_data = new char[1];
		*m_data = '\0';
	}else {
		int length = strlen(str);
		m_data = new char[length+1];
		strcpy(m_data,str);
	}
}
String::String(const String &another){
	int length = strlen(another.m_data);
	m_data = new char[length];
	strcpy(m_data,another.m_data);
}
String& String::operator = (String &rhs){
	if(this == rhs)return *this;
	delete [] m_data;
	int length = strlen(rhs.m_data);
	m_data = new char[length];
	strcpy(m_data,rhs.m_data);
	return *this;
}
String:: ~String(){
	delete[] m_data;
}
size_t String::size(){
	return strlen(this.m_data);
}