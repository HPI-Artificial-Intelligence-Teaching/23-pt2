TARGETS = stack eval_exp queue list_tests bag_test
CXX = g++
CPPFLAGS = -std=c++17
LDLIBS=-lm

all: $(TARGETS)

bag_test: bag_test.cpp bag.h
	$(CXX) $(CPPFLAGS) $< -o $@

stack: stack.cpp stack.h 
	$(CXX) $(CPPFLAGS) -o $@ $<

list_tests: list_tests.cpp list_stack.h list_queue.h 
	$(CXX) $(CPPFLAGS) -o $@ $<

queue: queue.cpp queue.h 
	$(CXX) $(CPPFLAGS) -o $@ $<

eval_exp: eval_exp.cpp stack.h
	$(CXX) $(CPPFLAGS) -o $@ $<

clean:
	$(RM) $(TARGETS)

.PHONY: all clean