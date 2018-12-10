#define _CRT_SECURE_NO_WARNINGS
#include<assert.h>
//#include <algorithm>
//#include<string>
#include<iostream>
using namespace std;


#if 0
class String
{
public:
	String(const char* str = "")
	{
		//assert(str);
		if (nullptr == str)
		{
			str = "";
		}
		_str = new char[strlen(str) + 1];tai
		strcpy(_str, str);
	}

	//类似系统生成的默认拷贝构造函数的方式
	//值的拷贝方式---内存拷贝
	//后果：多个对象公用一份资源，在销毁时同一份资源被释放多次从而引起程序的崩溃
	String(const String& s)
		:_str(s._str)
	{}

	//类似系统生成的默认赋值运算符的方式
	//值的拷贝方式--内存拷贝
	//问题: 1.内存泄漏
	//      2.与拷贝构造函数类似
	//浅拷贝：两个对象共用一个空间的数据
	String& operator=(const String& s)
	{
		
		_str = s._str;
		return *this;
	}

	~String()
	{
		if (_str)          //如果_str不为空，释放空间并且将str指针置空
		{
			delete[] _str;
			_str = nullptr;
		}
	}
		
private:
	char* _str;
	
};

void TestString()
{
	String s1("hello");
	//String s2(s1);
	String s2;
	s2 = s1;
}

int main()
{
	TestString();
	return 0;
}

#endif

#if 0
//深拷贝
//传统的写法
class String
{
public:
	String(const char* str = "")
	{
		//assert(str)
		if (nullptr == str)
		{
			str = "";
		}
		
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}

	String(const String& s)
		:_str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			/*delete[] _str;
			_str = new char[strlen(s._str) + 1];
			strcpy(_str, s._str);*/

			char* pstr = new char[strlen(s._str) + 1];
			strcpy(pstr, s._str);
			delete[] _str;
			_str = pstr;
		}
		return *this;
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
		}
	}
private:
	char* _str;
};

void TestString()
{
	String s1("hello");
	//String s2(s1);
	String s2;
	s2 = s1;
}


int main()
{
	TestString();
	return 0;
}
#endif


#if 0
//现代版写法：代码比较简洁
class String
{
public:
	String(const char* str = "")
	{
		//assert(str);
		if (nullptr == str)
		{
			str = "";
		};

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}

	String(const String& s)
		:_str(nullptr)
	{
		String strTemp(s._str);
		swap(_str, strTemp._str);

		//_str = 0xCCCCCCCC
		//String strTemp(s._str);
		//swap(_str, strTemp._str)

		//strs使用的是strTemp的空间
		//strTemp._str = 0xCCCCCCCC;

	}

	/*String& operator=(String s)
	{
		if (this != &s)
		{
			String strTemp(s);
			swap(_str, strTemp._str);
		}
		return *this;
	}*/

	//s2 = s2
	String& operator=(String s)
	{
		swap(_str, s._str);
		return *this;
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
		}
	}
private:
	char* _str;
};

void TestString()
{
	String s1("hello");
	String s2(s1);
	String s3;
	s3 = s2;
}

int main()
{
	TestString();
	return 0;
}
#endif

#if 0
class String
{
public:
	String(const char* str = "")
	{
		if (nullptr == str)
		{
			str = "";
		}
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
		_count = 1;
	}

	String(String& s)
		:_str(s._str)
		, _count(++s._count)
	{}

	~String()
	{
		if (0 == --_count && _str)
		{
			delete[] _str;
			_str = nullptr;
		}
	}
private:
	char* _str;
	int _count;//不行：每个对象中都有一份，一个对象修改了，其他对象不知道
};
#endif

#if 0
class String
{
public:
	String(const char* str = "")
	{
		if (nullptr == str)
		{
			str = "";
		}

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
		_count = 1;
	}

	String(String& s)
		:_str(s._str)
	{
		++_count;
	}

	~String()
	{
		if (0 == --_count && _str)
		{
			delete[] _str;
			_str = nullptr;
		}
	}
private:
	char* _str;
	static int _count;//不行，所有对象共享的，但资源可能会有多份
};

int String::_count = 0;

void TestString()
{
	String s1("hello");
	String s2(s1);
	String s3;
}


int main()
{
	TestString();
	return 0;
}
#endif


#if 0
//写时拷贝（cow copy on wirte）:浅拷贝 + 引用计数 + 在向对象中写入内容时，是否需要给当前对象独立空间
class String
{
public:
	String(const char* str = "")
		:_pcount(new int(1))
	{
		if (nullptr == str)
		{
			str = "";
		}

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}

	String(String& s)
		:_str(s._str)
		, _pcount(s._pcount)
	{
		++(*_pcount);
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			if (0 == --(*_pcount) && _str)
			{
				delete[] _str;
				_str = nullptr;

				delete _pcount;
				_pcount = nullptr;
			}

			_str = s._str;
			_pcount = nullptr;

			++(*_pcount);
		}
		return *this;
	}

	~String()
	{
		if (0 == --(*_pcount) && _str)
		{
			delete[] _str;
			_str = nullptr;

			delete _pcount;
			_pcount = nullptr;
		}
	}
	char& operator[](size_t index)
	{
		if (*_pcount > 1)
		{
			String str(_str);
			this->Swap(str);
		}
		return _str[index];
	}

	const char& operator[](size_t index)const
	{
		return _str[index];
	}

	void Swap(String& s)
	{
		swap(_str, s._str);
		swap(_pcount, s._pcount);
	}
private:
	char* _str;
	int* _pcount;
};

void TestString()
{
	String s1("hello");
	String s2(s1);

	String s3("world");
	//s1 = s3;
	s3 = s1;
	s1[0] = 'H';
}
int main()
{
	TestString();
	return 0;
}

#endif

#if 0
#if 0
int main()
{
	string s1(100, "h");
	string s2(s1);
	cout << (int)s1.c_str() << endl;
	cout << (int)s2.c_str() << endl;
	return 0; 
}
#endif

class String
{
public:
	typedef char* Iterator;
public:
	String(const char* str)
	{
		if (nullptr == str)
		{
			str = "";
		}

		_size = strlen(str);
		_str = new char[_size + 1];
		_capacity = _size;

		strcpy(_str, str);
	}

	String(const char* str, size_t size)
	{

	}

	String(const String& s)
		:_str(new char[s._capacity + 1])
		, _capacity(s._capacity)
		, _size(s._size)
	{
		strcpy(_str, s._str);
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* pStr = new char[s._capacity + 1];
			strcpy(pStr, s._str);
			delete[] _str;
			_str = pStr;
			_capacity = s._capacity;
			_size = s._size;
		}
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
			_capacity = 0;
			_size = 0;
		}
	}

	Iterator Begin()
	{
		return _str;
	}


	Iterator End()
	{
		return _str + _size;
	}

	Iterator RBegin()
	{
		return End();
	}

	Iterator REnd()
	{
		return RBegin();
	}

	void Pushback(char c)
	{
		Reserve(_size + 1);
		_str[_size++] = c;
		_str[_size] = '\0';
	}

	void Append(const char* str)
	{
		int len = strlen(str);
		if (len > _capacity - _size)
		{
			Reserve(2 * _capacity + len);
		}

		strcat(_str, str);
		_size += len;
	}

	char& operator[](size_t index)
	{
		return _str[index];
	}

	const char& operator[](size_t index)const
	{
		return _str[index];
	}

	void ReSzie(size_t newSzie, char c);
	void Reserve(size_t newCapacity);
	int Size()const
	{
		return _size;
	}

	bool Empty()const
	{
		return 0 == _size;
	}
	
	void Clear()
	{
		_size = 0;
	}

	int Find(char c, size_t pos = 0)
	{
		for (size_t i = pos; i < _size; ++i)
		{
			if (c == _str[i]);
			return i;
		}
		return npos;
	}

	int rFind(char c)
	{
		for (int i = _size - 1; i >= 0; --i)
		{
			if (c == _str[i]);
			return i;
		}
		return npos;
	}

	const char* C_str()const
	{
		return _str;
	}

	void Swap(String& s)
	{
		swap(_str, s._str);
		swap(_size, s._size);
		swap(_capacity, s._capacity);
	}

	String StrSub(size_t pos, size_t size)
	{
		int len = strlen(_str + pos);

		if (size > len)
		{
			size = len;
		}
		return String(_str + pos, size);
	}

	bool operator<(const String& s);
	bool operator<=(const String& s);
	bool operator>(const String& s);
	bool operator>=(const String& s);
	bool operator==(const String& s);
	bool operator!=(const String& s);
	friend ostream& operator<<(ostream& _count, const String& s);
	friend istream& operator>>(istream& _count, String& s);
private:
	char* _str;
	size_t _capacity;
	size_t _size;

	const static int npos;

};

const int String::npos = -1;

int main()
{
	return 0;
}
#endif

int main()
{
	string str("1234567890");
	for (size_t i = 0; i < str.size(); ++i)
		cout << str[i] << " ";
	cout << endl;

	for (string::iterator it = str.begin(); it != str.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	for (auto e : str)
		cout << e << " ";
	cout << endl;

	for (auto it = str.rbegin(); it != str.rend(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	return 0;
}