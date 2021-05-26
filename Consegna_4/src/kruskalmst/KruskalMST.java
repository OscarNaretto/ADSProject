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

    
    /**
     * 
     * @param graph composed of a type <V> which indicates the vertex of the graph and a type <Double> which indicates the label of the graph vertex
     * @throws GraphException if i pass a direct graph to the algorithm i generate this exception
     * @throws DisjointSetException generic exception
     */
    public KruskalMST(Graph<V, Double> graph) throws GraphException, DisjointSetException{
        if (graph.isDirected()){ throw new GraphException("Cannot pass a directed graph to Kruskal algorithm"); }
        edges = new LinkedList<Edge<V, Double>>();
        edges = graph.getAllEdges();
        trees = new DisjointSet<>(graph.getAllVertexes());
        mstEdges = new LinkedList<Edge<V, Double>>();
    }

   /**  
     * @throws GraphException if i pass a direct graph to the algorithm i generate this exception
     * @throws DisjointSetException generic exception
     */
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
    
    /**
     * 
     * @return returns the total distance of the arcs in the graph
     */
    public double getTotalDistance(){
        return this.totalDistance;
    }

    /**
     * 
     * @return the Minimum spanning tree
     */
    public Graph<V, Double> getMst(){
        return this.mst;
    }
}