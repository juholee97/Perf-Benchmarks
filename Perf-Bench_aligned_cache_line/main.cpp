#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>
#include <fstream>
#include <new> // for std::hardware_destructive_interference_size

std::ofstream outputFile( "compare_performance.csv" );

const int NUM_THREADS = 4;
const int NUM_INCREMENTS = 1000000;

struct PaddedAtomic {
	alignas( std::hardware_destructive_interference_size ) std::atomic<int> value;
};

struct NonPaddedAtomic {
	std::atomic<int> value;
};

PaddedAtomic paddedCounters[ NUM_THREADS ];
NonPaddedAtomic nonPaddedCounters[ NUM_THREADS ];

void incrementPadded( int index ) {
	for ( int i = 0; i < NUM_INCREMENTS; ++i ) {
		paddedCounters[ index ].value.fetch_add( 1, std::memory_order_relaxed );
	}
}

void incrementNonPadded( int index ) {
	for ( int i = 0; i < NUM_INCREMENTS; ++i ) {
		nonPaddedCounters[ index ].value.fetch_add( 1, std::memory_order_relaxed );
	}
}

void measureAndOutputPerformance() {

	// Measure performance with padding
	{
		std::vector<std::thread> threads;
		auto start = std::chrono::high_resolution_clock::now();

		for ( int i = 0; i < NUM_THREADS; ++i ) {
			threads.emplace_back( incrementPadded, i );
		}

		for ( auto& t : threads ) {
			t.join();
		}

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;

		int total = 0;
		for ( int i = 0; i < NUM_THREADS; ++i ) {
			total += paddedCounters[ i ].value.load();
		}

		outputFile << duration.count() << ",";
	}

	// Measure performance without padding
	{
		std::vector<std::thread> threads;
		auto start = std::chrono::high_resolution_clock::now();

		for ( int i = 0; i < NUM_THREADS; ++i ) {
			threads.emplace_back( incrementNonPadded, i );
		}

		for ( auto& t : threads ) {
			t.join();
		}

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;

		int total = 0;
		for ( int i = 0; i < NUM_THREADS; ++i ) {
			total += nonPaddedCounters[ i ].value.load();
		}

		outputFile << duration.count() << "\n";
	}

}

int main() {
	for ( int i = 0; i < 1000; i++ )
	{
		measureAndOutputPerformance();
	}
	outputFile.close();
	return 0;
}