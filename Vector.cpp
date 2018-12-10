#include<iostream>
using namespace std;
#include<vector>
#include<string>


#if 0
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
	{}

	friend ostream& operator<<(ostream& _cout, const Date& d)
	{
		_cout << d._year << "-" << d._month << "-" << d._day;
		return _cout;
	}
private:
	int _year;
	int _month;
	int _day;
};

template<class T>
void PrintVector(const vector<T>& v)
{
	for (auto e : v)
	{
		cout << e << " ";
	}

	//for (auto e = v.begin(); e != v.end(); ++it)
	//{
	//	cout << *e << "";
	//}

	cout << endl;
}
void TestVector()
{
	std::vector<int> v1;
	std::vector<int> v2(10, 5);
	std::vector<int> v3(10);//int()内置类型，缺省值：0
	std::vector<int> v4(10);//Date（)自定义类型：调用T()缺省的构造函数

	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	vector<int> v5(array, array + sizeof(array) / sizeof(array[0]));

	string str("hello");
	vector<char> v6(str.begin(), str.end());
	vector<char> v7(v6);

	PrintVector(v2);
	PrintVector(v3);
	PrintVector(v4);
	PrintVector(v5);
	PrintVector(v6);
	PrintVector(v7);
}

int main()
{
	TestVector();
	return 0;
}
#endif

#if 0
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
	{}

	friend ostream& operator<<(ostream& _cout, const Date& d)
	{
		_cout << d._year << "-" << d._month << "-" << d._day;
		return _cout;
	}
private:
	int _year;
	int _month;
	int _day;
};

void TestVector()
{
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	vector<int> v1(array, array + 5);
	cout << typeid(vector<int>::iterator).name() << endl;

	vector<int>::iterator it1 = v1.begin();
	*it1 = 10;

	// 列表的初始化
	const vector<int> v2{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	cout << typeid(const vector<int>::iterator).name() << endl;

	const vector<int>::const_iterator it2 = v2.cbegin();
	//*it2 = 10;
}

int main()
{
	Date d1(2018, 11, 24);
	Date d2(2018, 11, 24);
	TestVector();
	return 0;
}
#endif

#if 0
#include<algorithm>

int main()
{
	vector<int> v{ 2, 1, 8, 4, 0, 9, 3, 6, 7, 5 };
	sort(v.begin(), v.end());
	return 0;
}
#endif

#if 0
int main()
{
	vector<int> v{ 1, 2, 3, 4 };
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(6);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(20, 5);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(10);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.reserve(15);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.reserve(100);
	cout << v.size() << endl;
	cout << v.capacity() << endl;
	return 0;
}
#endif


#if 0
int main()
{
	size_t sz;
	std::vector<int>foo;
	//foo.reserve(100);
	sz = foo.capacity();
	std::cout << "making foo grow:\n";

	for (int i = 0; i < 100; ++i)
	{
		foo.push_back(i);
		if (sz != foo.capacity())
		{
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
	return 0;
}
#endif

#if 0
//迭代器失效
//1.什么是迭代器失效？
//2.vector什么情况下会发生迭代器失效？怎么解决？
//       >>push_back, inster, resize, reserve, assign
//       >>删除

int main()
{
	vector<int> v{ 1, 2, 3, 4 };
	vector<int>::iterator it = v.begin();
	*it *= 2;

	for (int i = 0; i < 5; ++i)
	{
		v.push_back(i);
	}
	it = v.begin();//it 迭代器失效
	*it *= 2;

	it = v.begin() + 8;
	cout << *it << endl;

	it = v.begin() + 2;
	it = v.erase(it);
	cout << *it << endl;

	v.pop_back();
	cout << *it << endl;

	return 0;

}
#endif


#if 0
int main()
{
	vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	auto it = v.begin();

	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			it = v.erase(it);
		}
		else
		{
			++it;
		}
	}
	return 0;
}
#endif


namespace bit
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef T* reserve_iterator;
	public:
		vector()
			:_start(nullptr)
			, _last(nullptr)
			, _endofStorage(nullptr)
		{}

		vector(size_t n, const T& data = T())
			:_start(new T[n])
			, _last(_start + n)
			, _endofStorage(_last)
		{
			for (size_t i = o; i < n; ++i)
			{
				-start[i] = data;
			}

			//有问题
			//memeset(_start, data, sizeof(T)*n);
		}

		//[first, last)代表一段连续的空间
		vector(T* first, T* last)
		{
			size_t size = last - first;
			_start = new T[size];

			for ()
		}
	private:
		iterator _start;
		iterator _last;//_size
		iterator _endofStorage;//_capacity
	};

}