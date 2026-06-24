bench_queue:bench_queue.cc
	g++ -O2 -std=c++20 -Iinclude bench_queue.cc -lbenchmark -pthread -o queue_bench
run:
	./queue_bench --benchmark_repetitions=5 --benchmark_report_aggregates_only=tru