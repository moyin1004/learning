learn:learn.cc learn.foo.pb.cc
	protoc -I=./ --cpp_out=./ ./learn.foo.proto
	g++ learn.cc learn.foo.pb.cc -g -lprotobuf -std=c++11
