package kruskalmst;

import java.util.LinkedList;

import graph.Edge;
import graph.Graph;
import graph.GraphException;
import disjointset.DisjointSet;
import disjointset.DisjointSetException;

public class KruskalMST<V> {
    LinkedList<Edge<V, Double>> edges;
    DisjointSet<V> trees;
    LinkedList<Edge<V, Double>> mstEdges;
    Graph<V, Double> mst;
    double totalDistance;

    //controllo directed eccezione, controllo tipo etichetta
    public KruskalMST(Graph<V, Double> graph) throws GraphException, DisjointSetException{
        if (graph.isDirected()){ throw new GraphException("Cannot pass a directed graph to Kruskal algorithm"); }
        edges = new LinkedList<Edge<V, Double>>();
        edges = graph.getAllEdges();
        trees = new DisjointSet<>(graph.getAllVertexes());
        mstEdges = new LinkedList<Edge<V, Double>>();
    }

    public void MST() throws DisjointSetException, GraphException{
        edges.sort(null);
        for (Edge<V, Double> tmp: edges){
            if(trees.union(tmp.getSource(), tmp.getDestination())) {
                mstEdges.add(tmp);
            }
        }
        mst = new Graph<V, Double>(false, mstEdges);
        setTotalDistance();
    }

    private void setTotalDistance(){
        for(Edge<V, Double> edge: mstEdges){
            this.totalDistance += edge.getLabel();
        }
    }

    public double getTotalDistance(){
        return this.totalDistance;
    }

    public Graph<V, Double> getMst(){
        return this.mst;
    }
}