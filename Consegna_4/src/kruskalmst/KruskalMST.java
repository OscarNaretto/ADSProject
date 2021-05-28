package kruskalmst;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.Set;

import graph.Edge;
import graph.Graph;
import graph.GraphException;
import disjointset.DisjointSet;
import disjointset.DisjointSetException;

public class KruskalMST<V> {
    LinkedList<Edge<V, Double>> edges;
    DisjointSet<V> trees;
    Set<Edge<V, Double>> mstEdges;
    Graph<V, Double> mst;
    double totalDistance;
    
    /**
     * @param graph composed of a type V which indicates the vertex of the graph and a type Double which indicates the label of the graph vertex
     * @throws IllegalArgumentException if one of the elements passed to the DisjointSet constructor is null
     * @throws GraphException if i pass a direct graph to the algorithm i generate this exception or if the passed graph has no edges
     * @throws DisjointSetException if we try to add an element already present
     */
    public KruskalMST(Graph<V, Double> graph) throws IllegalArgumentException, GraphException, DisjointSetException{
        if (graph.isDirected()){ throw new GraphException("Cannot pass a directed graph to Kruskal algorithm"); }
        edges = new LinkedList<Edge<V, Double>>();
        edges = graph.getAllEdges();
        trees = new DisjointSet<>(graph.getAllVertexes());
        mstEdges = new HashSet<>();
    }

    /**  
     * @throws DisjointSetException if one element or both elements passed to union() are not present in the DisjointSet structure
     */
    public void MST() throws DisjointSetException{
        edges.sort(null);
        for (Edge<V, Double> tmp: edges){
            if(trees.union(tmp.getSource(), tmp.getDestination())) {
                mstEdges.add(tmp);
            }
        }
        setTotalDistance();
    }

    private void setTotalDistance(){
        for(Edge<V, Double> edge: mstEdges){
            this.totalDistance += edge.getLabel();
        }
    }
    
    /**
     * @return returns the total distance of the edges in the graph
     */
    public double getTotalDistance(){
        return this.totalDistance;
    }

    /**
     * @return the minimum spanning tree
     * @throws GraphException if the user tries to add and already existing Vertex or Edge
     * @throws IllegalArgumentException if one of the elements passed to the union method is null or if we try to add a null Edge or Vertex to the graph
     */
    public Graph<V, Double> getMst() throws IllegalArgumentException, GraphException{
        mst = new Graph<V, Double>(false, mstEdges);
        return this.mst;
    }
}