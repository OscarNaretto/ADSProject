package graph;

import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Set;


/**
 * @param <V>   //Vertex and Distance
 */
public class Graph<V, D>{
    private boolean directed;
    private HashMap<V,HashMap<V, D>> adjacencyListsMap;
    //HashMap<V,HashMap<V,Double>> contains Vertexes of the Graph as keys and adjacencyLists as values (HashMap<V,D>)
    //HashMap<V,Double> contains adjacency vertexes as keys and distances between Vertexes as values
    private HashMap<Integer, Edge<V, D>> edgesMap;

    public Graph(boolean directed){
        this.directed = directed;
        this.adjacencyListsMap = new HashMap<>();
        this.edgesMap = new HashMap<>();
    }

    public Graph(boolean directed, LinkedList<Edge<V, D>> edgesList) throws GraphException{
        this.directed = directed;
        this.adjacencyListsMap = new HashMap<>();
        this.edgesMap = new HashMap<>();

        for (Edge<V, D> edge : edgesList) {
            V source = edge.getSource();
            V destination = edge.getDestination();
            this.addVertex(source);
            this.addVertex(destination);
            this.addEdge(source, destination, edge.getLabel());
        }
    }

    public boolean isDirected(){
        return this.directed; 
    }

    public int vertexesNumber(){ 
        return this.adjacencyListsMap.size(); 
    }

    public int edgesNumber(){
        int tot = 0;

        for (V key : adjacencyListsMap.keySet()){
            tot = tot + adjacencyListsMap.get(key).size();
        }
        if (!isDirected()){ tot = tot / 2; }
        return tot;
    }

    public boolean isVertexPresent(V vertex) throws GraphException{
        if (vertex == null){ throw new GraphException("Graph isVertexPresent: cannot accept null as vertex"); }
        return this.adjacencyListsMap.containsKey(vertex); 
    }

    public void addVertex(V vertex) throws GraphException{
        if(!isVertexPresent(vertex)){
            adjacencyListsMap.put(vertex,new HashMap<>());
        }   
    }

    public void removeVertex(V vertex){
        this.adjacencyListsMap.remove(vertex);           

        for (V key : this.adjacencyListsMap.keySet()) {  
            this.adjacencyListsMap.get(key).remove(vertex);
        } 
    }

    public boolean isEdgePresent(V source, V destination) throws GraphException {
        if (source == null || destination == null){ throw new GraphException("Graph isVertexPresent: cannot accept null as vertex"); }
        return adjacencyListsMap.containsKey(source) && adjacencyListsMap.get(source).containsKey(destination);
    }

    public void addEdge(V source, V destination, D distance) throws GraphException{
        if(isVertexPresent(source) && isVertexPresent(destination) && !isEdgePresent(source, destination)){
            this.adjacencyListsMap.get(source).put(destination, distance);
            if (!isDirected()){
                this.adjacencyListsMap.get(destination).put(source, distance);
            }

            Edge<V, D> tmp = new Edge<>(source, destination, distance);
            edgesMap.put(tmp.hashCode(), tmp);
        }   
    }

    public void removeEdge(V source, V destination) throws GraphException{
        if(isVertexPresent(source) && isVertexPresent(destination) && isEdgePresent(source, destination)){
            int code = this.adjacencyListsMap.get(source).get(destination).hashCode();
            this.adjacencyListsMap.get(source).remove(destination);
            edgesMap.remove(code);
            if (!isDirected()) {
                int codeBis = this.adjacencyListsMap.get(destination).get(source).hashCode();
                this.adjacencyListsMap.get(destination).remove(source);
                edgesMap.remove(codeBis);
            }
        } else {
            throw new GraphException("Graph removeEdge: cannot remove inexistent edge");
        }
    }

    public D getEdgeLabel(V source, V destination) throws GraphException{
        if (!isEdgePresent(source, destination)){ throw new GraphException("Graph getEdgeLabel: cannot get label if the edge is not present"); } //segnala errore con Exception
        return adjacencyListsMap.get(source).get(destination);
    }

    public Set<V> getAllVertexes(){
        Set<V> keys = new HashSet<>();
        keys = adjacencyListsMap.keySet();
        return keys;
    }

    public LinkedList<Edge<V, D>> getAllEdges() throws GraphException {
        if(edgesNumber() == 0) { throw new GraphException("Graph getAllEdges: no edges present"); }
        LinkedList<Edge<V, D>> edgesList = new LinkedList<>(edgesMap.values());
        return edgesList;
    }

    public Set<V> getAllAdjVertexes(V vertex){
        Set<V> keys = this.adjacencyListsMap.get(vertex).keySet();
        return keys;
    }
}