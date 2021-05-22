package kruskalmst;

import java.util.LinkedList;

import graph.Edge;
import graph.Graph;
import graph.GraphException;
import disjointset.DisjointSet;
import disjointset.DisjointSetException;

public class KruskalMST<V> {
    LinkedList<Edge<V>> edges;
    DisjointSet<V> trees;
    LinkedList<Edge<V>> mstEdges;
    Graph<V> mst;
    double totalDistance;
    boolean directed;

    public KruskalMST(Graph<V> graph) throws GraphException, DisjointSetException{
        edges = new LinkedList<Edge<V>>();
        edges = graph.getAllEdges();
        trees = new DisjointSet<>(graph.getAllVertexes());
        mstEdges = new LinkedList<Edge<V>>();
        directed = graph.isDirected();
    }

    public void MST() throws DisjointSetException{
        edges.sort(null);
        for (Edge<V> tmp: edges){
            if(trees.union(tmp.getSource(), tmp.getDestination())) {
                mstEdges.add(tmp);
            }
        }
        mst = new Graph<V>(mstEdges);
        setTotalDistance();
    }

    private void setTotalDistance(){
        for(Edge<V> edge: mstEdges){
            this.totalDistance += edge.getLabel();
        }
        if (!mst.isDirected()){
            this.totalDistance = this.totalDistance/2;
        }
    }

    public double getTotalDistance(){
        return this.totalDistance;
    }

    public Graph<V> getMst(){
        return this.mst;
    }
}