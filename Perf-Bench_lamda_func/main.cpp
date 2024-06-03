// lamda, std::function performance test
#include <iostream>
#include <functional>
#include <chrono>
#include <fstream>

template<typename Func>
auto GetPerformance( Func f, size_t sampling_call ) 
{
	const auto startTime = std::chrono::high_resolution_clock::now();

	for ( size_t i = 0; i < sampling_call; ++i ) 
	{
		const auto result = f( i, i );
	}

	const auto endTime = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> timeOfDuration_ms = endTime - startTime;

	return timeOfDuration_ms.count();
}

int f_func( int a, int b )
{
	return a + b;
}

int main()
{
	std::ofstream ofs( "compare_performance.csv" );

	auto f_lamda = []( int a, int b ) { return a + b; };
	std::function<int( int, int )> f_stdFunc = f_func;

	// 함수 호출 회수에 따른 성능 비교.
	for ( size_t callcnt = 1; callcnt < 100000; ++callcnt )
	{
		ofs << GetPerformance( f_lamda, callcnt ) << ",";
		ofs << GetPerformance( f_stdFunc, callcnt ) << ",";
		ofs << std::endl;
	}

	return 0;
}