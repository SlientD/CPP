#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;

//自定义类型不能拷贝构造时，不能用默认拷贝构造函数，因为是浅拷贝只是将地址给了对方指向了同一块空间
//深拷贝
namespace String1{
	class string{
	public:
		string(char *s =""){
			if (s == nullptr)
			{
				s = "";
			}
			_str = new char[strlen(s) + 1];
			strcpy(_str, s);
		}
		/*string(const string &s)
		{
			_str = new char[strlen(s._str) + 1];
			strcpy(_str, s._str);
		}*/
		//现代版写法String类
		string(const string &s)
			:_str(nullptr)               //为什么要初始化：要保证交换完后，stmp不会指向一段无效空间，stmp析构的时候不会报错
		{
		string stmp(s._str);            //stmp在这个函数调完之后会自己调用析构函数释放
		swap(_str,stmp._str);  
		}
		
		~string()
		{
			delete[] _str;
			_str = nullptr;
		}

		/*string& operator=(const string &s)
		{
			if (this == &s)
			{
				return *this;
			}
			delete[] _str;
			_str = new char[strlen(s._str) + 1];
			strcpy(_str, s._str);
			return *this;

		}*/
		string& operator=(string s)
		{
			swap(_str, s._str);
			return *this;

		}


		friend ostream& operator<<(ostream &_cout, const string &str);
		
	private:
		char *_str;
	};
	ostream& operator<<(ostream &_cout, const string &str)
	{
		_cout << str._str;                    //_cout就是cout
		return _cout;
	}
}
//浅拷贝:
//思考为什么之前浅拷贝会出现错误？因为浅拷贝只是将地址给了对方指向了同一块空间，在调用析构函数时，同一块空间会出现被多次释放的情况，因而会报错
//但是并不代表多个对象就无法共享一份资源空间，只要保证该资源空间只被释放一次即可。
//因而另一个问题又出现了：应由哪一个共享该资源空间的对象释放呢？   ----应由最后一个使用该资源空间的对象来释放该空间
//那么当一个对象要去释放该空间时，如何知道他自己是不是最后一个用该空间的对象呢？     --》因而引入了计数器
//计数器作用：记录使用该快空间的对象还有几个，当每次多创建一个对象时，计数器加一，释放一个计数器减一

//那么计数器应该是什么类型的呢？
// 1.在类中增加int类的成员变量
//不行 -----原因：普通的整形成员变量，每个对象中都有一份，一个对象在修改该计数时候，不会影响其他对象

//// 将计数给成静态类型的成员变量---->不行
// 原因：静态类型成员变量是所有对象共享,不管有没有共享资源，count都是共享的。就是尽管不共享资源，也用了同一个count空间来及数所以肯定说不通
//      因而：计数应该与资源个数保持一致，就是共享同一块空间的资源才共享同一个计数器
namespace String2
{
	class string
	{
	public:
		string(char* str = "")
		{
			if (nullptr == str)
				str = "";

			// 申请空间
			_str = new char[strlen(str) + 1];
			count = 1;
			// 存放str中的字符
			strcpy(_str, str);
		}

		string(const string& s)
			: _str(s._str)
		{
			++count;
		}

		// s2 = s1;
		string& operator=(const string& str)
		{ 
			if (this == &str)
			{
				return *this;
			}
			if (_str&&--count == 0)     //不是还未初始化的，然后是最后一个用该空间的对象
			{
				delete[] _str;
				_str = nullptr;
			}
			_str = str._str;
			
			++count;

			return *this;
		}
		friend	ostream& operator<<(ostream &_cout, const string &str);
		~string()
		{
			if (_str && 0 == --count)
			{
				delete[] _str;
				_str = nullptr;
			}
		}
	private:
		char* _str;
		static int count;
	};

	int string::count = 0;
	ostream& operator<<(ostream &_cout, const string &str)
	{
		_cout << str._str << ":" << str.count;                    //_cout就是cout
		return _cout;
	}
}




//通过以上所述，将count定义为和_str类型相同，就可以满足共享同一块空间的资源共享同一个计数器，因而使用int *，来存储计数器

namespace String3{
	class string{
	public:
		string(char *s = "")
			:count(new int(1))
		{
			if (s == nullptr)
			{
				s = "";
			}
			_str = new char[strlen(s) + 1];
			strcpy(_str, s);
		}
		string(const string &s){
			_str = s._str;
			count = s.count;
			(*count)++;
		}
		string& operator=(const string &str)
		{
			if (this == &str)
			{
				return *this;
			}
			if (_str&&--(*count) == 0)     // 让当前对象与其管理资源分离开,分开时要判断他是不是最后一个用这个空间的资源
			{
				delete[] _str;
				_str = nullptr;

				delete count;
				count = nullptr;
			}
			_str = str._str;
			count = str.count;          //换指向，改计数器
			++(*count);
			return *this;
			

		}
		
		~string()
		{
			if (_str&&--(*count) == 0)     //不是还未初始化的，然后是最后一个用该空间的对象
			{
				delete[] _str;
				_str = nullptr;

				delete count;
				count = nullptr;
			}
		}
		friend	ostream& operator<<(ostream &_cout, const string &str);
	private:
		char *_str;
		int *count;
	};
	ostream& operator<<(ostream &_cout, const string &str)
	{
		_cout << str._str<<":"<<*str.count;                    //_cout就是cout
		return _cout;
	}
}

void Test(const String3::string &str)
{
	cout << str << endl;            //-->2
	String3::string str1("hello");
	String3::string str2(str1);

}

int main()
{
	String3::string str1("hello");
	String3::string str2(str1);
	Test(str1);
	String3::string str3("heihei");
	String3::string str4(str3);
	str4 = str1;
	
	cout << str1 << endl;
	cout << str2 << endl;
	cout << str3 << endl;
	cout << str4 << endl;


	system("pause");
	return 0;;
}