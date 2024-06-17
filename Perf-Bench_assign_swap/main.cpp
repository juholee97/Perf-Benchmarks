// lamda, std::function performance test
#include <iostream>
#include <functional>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <vector>


class CBigdata
{
public:
	CBigdata() = default;
	void Clear_assign()
	{
		ai = 0;
		bi = 0;
		ci = 0;
		ad = 0.0;
		bd = 0.0;
		cd = 0.0;
		ab = false;
		bb = false;
		cb = false;
		aull = 0;
		bull = 0;
		cull = 0;
	}

private : 
	int ai { 0 };
	int bi { 0 };
	int ci { 0 };
	double ad { 0.0 };
	double bd { 0.0 };
	double cd { 0.0 };
	bool ab { false };
	bool bb { false };
	bool cb { false };
	unsigned long long aull { 0 };
	unsigned long long bull { 0 };
	unsigned long long cull { 0 };
};



template<typename Func>
auto GetPerformance( Func f, int cnt  )
{
	CBigdata data;
	const auto startTime = std::chrono::high_resolution_clock::now();
	for ( int i = 0; i < cnt; i++ )
	{
		f( data );
	}

	const auto endTime = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> timeOfDuration_ms = endTime - startTime;

	return timeOfDuration_ms.count();
}

void f_func1( CBigdata & data )
{
	data.Clear_assign();	
}

void f_func2( CBigdata & data )
{
	CBigdata tmp;
	std::swap( data, tmp );
}

int main()
{
	std::ofstream ofs( "compare_performance.csv" );

	std::function<void( CBigdata& )> f_stdFunc1 = f_func1;
	std::function<void( CBigdata& )> f_stdFunc2 = f_func2;

	// std::swap 초기화 vs assign 초기화
	for ( size_t callcnt = 1; callcnt <= 10000; ++callcnt )
	{
		ofs << GetPerformance( f_stdFunc1, callcnt ) << ",";
		ofs << GetPerformance( f_stdFunc2, callcnt ) << ",";
		ofs << "\n";
	}

	return 0;
}