set +e
scons -u || true
g++ -o cpp/baseline/helib/server/debug/helib-server-main.o -c -Wall -Icpp -std=c++0x -Wno-deprecated-declarations -g cpp/baseline/helib/server/helib-server-main.cc
g++ -o cpp/baseline/helib/server/debug/helib-server-main.out cpp/baseline/helib/server/debug/helib-server-main.o -L/home/cian/Libraries/HElib/lib64 cpp/baseline/helib/server/debug/libhelib-server.a cpp/baseline/helib/server/debug/libhelib-circuit-parser.a cpp/baseline/helib/server/debug/libhelib-circuit.a cpp/baseline/helib/server/debug/libhelib-scanner.a cpp/baseline/helib/server/debug/libhelib-gates.a -lpthread cpp/common/debug/liblogging.a cpp/common/debug/libstatics.a cpp/common/statics/debug/libordered-function-registry.a cpp/common/debug/liboutput-handler.a -lboost_thread -lhelib -lntl -lgmp cpp/baseline/common/debug/libbaseline.a
echo "Finished building"