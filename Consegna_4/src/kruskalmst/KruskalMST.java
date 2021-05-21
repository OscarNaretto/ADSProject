package kruskalmst;

import java.util.LinkedList;

import graph.Edge;
import graph.Graph;
import disjointset.DisjointSet;

public class KruskalMST<V> {
    LinkedList<Edge<V>> edges;
    DisjointSet<V> trees;
    LinkedList<Edge<V>> mstEdges;
    Graph<V> mst;

    public KruskalMST(Graph<V> graph){
        edges = new LinkedList<Edge<V>>();
        edges = graph.getAllEdges();
        trees = new DisjointSet<>(graph.getAllVertexes());
    }

    public Graph<V> MST(){
        edges.sort(null);
        for (Edge<V> tmp: edges){
            if(trees.union(tmp.getStart(), tmp.getEnd())) {
                mstEdges.add(tmp);
            }
        }
        mst = new Graph<V>(mstEdges);
        return mst;
    }
}