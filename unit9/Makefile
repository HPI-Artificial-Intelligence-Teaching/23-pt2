TARGETS = min_pq_test index_min_pq_test bag_test \
		  graph_test dfs_test bfs_test symbol_graph_test degree_of_separation cc_test \
  		  digraph_test symbol_digraph_test directed_cycle_test dfo_test topological_test scc_test \
		  weighted_graph_test weighted_digraph_test prim_test dijkstra_test bellman_ford_test

CXX = g++
CPPFLAGS = -std=c++17 -O3
LDLIBS=-lm

all: $(TARGETS)

min_pq_test: min_pq_test.cpp min_pq.h
	$(CXX) $(CPPFLAGS) $< -o $@

index_min_pq_test: index_min_pq_test.cpp index_min_pq.h
	$(CXX) $(CPPFLAGS) $< -o $@

bag_test: bag_test.cpp bag.h
	$(CXX) $(CPPFLAGS) $< -o $@

graph_test: graph_test.cpp graph.cpp graph.h stack.h bag.h
	$(CXX) $(CPPFLAGS) $< graph.cpp -o $@ 

dfs_test: dfs_test.cpp graph.cpp graph.h stack.h bag.h dfs.h
	$(CXX) $(CPPFLAGS) $< graph.cpp -o $@ 

bfs_test: bfs_test.cpp graph.cpp bfs.cpp graph.h stack.h queue.h bag.h bfs.h
	$(CXX) $(CPPFLAGS) $< graph.cpp bfs.cpp -o $@ 

symbol_graph_test: symbol_graph_test.cpp symbol_graph.cpp graph.cpp graph.h stack.h bag.h symbol_graph.h
	$(CXX) $(CPPFLAGS) $< symbol_graph.cpp graph.cpp -o $@ 

degree_of_separation: degree_of_separation.cpp symbol_graph.cpp symbol_graph.h graph.cpp graph.h stack.h bag.h bfs.cpp bfs.h queue.h  
	$(CXX) $(CPPFLAGS) $< symbol_graph.cpp graph.cpp bfs.cpp -o $@ 

cc_test: cc_test.cpp graph.cpp graph.h stack.h bag.h queue.h cc.h
	$(CXX) $(CPPFLAGS) $< graph.cpp -o $@ 

digraph_test: digraph_test.cpp digraph.cpp digraph.h stack.h bag.h
	$(CXX) $(CPPFLAGS) $< digraph.cpp -o $@ 

symbol_digraph_test: symbol_digraph_test.cpp symbol_digraph.cpp digraph.cpp digraph.h stack.h bag.h symbol_digraph.h
	$(CXX) $(CPPFLAGS) $< symbol_digraph.cpp digraph.cpp -o $@ 

directed_cycle_test: directed_cycle_test.cpp digraph.cpp digraph.h stack.h bag.h directed_cycle.h
	$(CXX) $(CPPFLAGS) $< digraph.cpp -o $@ 

dfo_test: dfo_test.cpp digraph.cpp digraph.h stack.h queue.h bag.h dfo.h
	$(CXX) $(CPPFLAGS) $< digraph.cpp -o $@ 

topological_test: topological_test.cpp symbol_digraph.cpp digraph.cpp digraph.h stack.h bag.h symbol_digraph.h topological.h directed_cycle.h
	$(CXX) $(CPPFLAGS) $< symbol_digraph.cpp digraph.cpp -o $@ 

scc_test: scc_test.cpp digraph.cpp digraph.h stack.h stack.h queue.h bag.h dfo.h scc.h
	$(CXX) $(CPPFLAGS) $< digraph.cpp -o $@ 

weighted_graph_test: weighted_graph_test.cpp weighted_graph.cpp weighted_graph.h stack.h bag.h edge.h
	$(CXX) $(CPPFLAGS) $< weighted_graph.cpp -o $@ 

weighted_digraph_test: weighted_digraph_test.cpp weighted_digraph.cpp weighted_digraph.h stack.h bag.h edge.h
	$(CXX) $(CPPFLAGS) $< weighted_digraph.cpp -o $@ 

prim_test: prim_test.cpp weighted_graph.cpp weighted_graph.h stack.h queue.h min_pq.h bag.h edge.h prim.h
	$(CXX) $(CPPFLAGS) $< weighted_graph.cpp -o $@ 

dijkstra_test: dijkstra_test.cpp weighted_digraph.cpp weighted_digraph.h stack.h queue.h index_min_pq.h bag.h edge.h dijkstra.h
	$(CXX) $(CPPFLAGS) $< weighted_digraph.cpp -o $@ 

bellman_ford_test: bellman_ford_test.cpp weighted_digraph.cpp weighted_digraph.h stack.h queue.h bag.h edge.h bellman_ford.h
	$(CXX) $(CPPFLAGS) $< weighted_digraph.cpp -o $@ 

clean:
	$(RM) $(TARGETS)

.PHONY: all clean