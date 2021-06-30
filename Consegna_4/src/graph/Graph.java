package graph;

import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Set;


public class Graph<V, D>{
    private boolean directed;
    private HashMap<V,HashMap<V, D>> adjacencyListsMap;

    /**
    * @param directed if true the graph will be directed; if false will be non-directed
    */
    public Graph(boolean directed){
        this.directed = directed;
        this.adjacencyListsMap = new HashMap<>();
    }

    /**
    * @param directed   if true the graph will be directed; if false will be non-directed
    * @param edgesList  represents the set containing all the edges of the graph that needs to be created.
    * Edges need to be unique
    * @throws IllegalArgumentException  if we try to add a null Edge or Vertex to the graph
    * @throws GraphException if the user tries to add and already existing Vertex or Edge  
    */
    public Graph(boolean directed, Set<Edge<V, D>> edgesList) throws IllegalArgumentException, GraphException{
        this.directed = directed;
        this.adjacencyListsMap = new HashMap<>();

        for (Edge<V, D> edge : edgesList) {
            V source = edge.getSource();
            V destination = edge.getDestination();
            if (!this.isVertexPresent(source)) { this.addVertex(source); }
            if (!this.isVertexPresent(destination)) { this.addVertex(destination); }
            this.addEdge(source, destination, edge.getLabel());
        }
    }

    /**
    * @return returns the boolean attribute "directed"; if true the graph will be directed; if false will be non-directed
    */
    public boolean isDirected(){
        return this.directed; 
    }

    /**
    * @return returns the number of vertexes of the graph 
    */
    public int vertexesNumber(){ 
        return this.adjacencyListsMap.size(); 
    }

    /**
    * @return returns the number of edges of the graph 
    */
    public int edgesNumber(){
        int tot = 0;
        for (V key : adjacencyListsMap.keySet()){
            tot = tot + adjacencyListsMap.get(key).size();
        }
        if (!isDirected()){ tot = tot / 2; }
        return tot;
    }

    /**
    * @param vertex is the element of type V we want to search in the graph 
    * @return true if vertex is present; false if it is not
    * @throws IllegalArgumentException if vertex is null
    */
    public boolean isVertexPresent(V vertex) throws IllegalArgumentException{
        if (vertex == null){ throw new IllegalArgumentException("Graph isVertexPresent: cannot accept null as vertex"); }
        return this.adjacencyListsMap.containsKey(vertex); 
    }

    /**
    * @param vertex is the element of type V we want to search in the graph 
    * @return true if vertex is present; false if it is not
    * @throws IllegalArgumentException if vertex is null
    * @throws GraphException if the user tries to add and already existing Vertex
    */
    public void addVertex(V vertex) throws IllegalArgumentException, GraphException{
        if(!isVertexPresent(vertex)){
            adjacencyListsMap.put(vertex,new HashMap<>());
        } else {
            throw new GraphException("Graph addEVertex: cannot add a Vertex already present");
        }
    }

    /**
    * @param vertex is the element of type V we want to remove in the graph 
    */
    public void removeVertex(V vertex){
        this.adjacencyListsMap.remove(vertex);           

        for (V key : this.adjacencyListsMap.keySet()) {  
            this.adjacencyListsMap.get(key).remove(vertex);
        } 
    }

    /**
    * @param source is the Vertex of type V where the edge starts
    * @param destination is the Vertex of type V where the edge ends
    * @return true if edge is present; false if it is not
    * @throws IllegalArgumentException if source or destination are null
    */
    public boolean isEdgePresent(V source, V destination) throws IllegalArgumentException {
        if (source == null || destination == null){ throw new IllegalArgumentException("Graph isEdgePresent: cannot accept null as vertex"); }
        return adjacencyListsMap.containsKey(source) && adjacencyListsMap.get(source).containsKey(destination);
    }

    /**
    * @param source is the Vertex of type V where the edge starts
    * @param destination is the Vertex of type V where the edge ends
    * @param distance is the label of type D of the edge
    * @throws IllegalArgumentException if source or destination or distance are null
    * @throws GraphException if the user tries to add and already existing Edge
    */
    public void addEdge(V source, V destination, D distance) throws IllegalArgumentException, GraphException{
        if (isEdgePresent(source, destination)){ throw new GraphException("Graph addEdge: cannot add and Edge already present" + source + destination); }
        if(isVertexPresent(source) && isVertexPresent(destination)){
            this.adjacencyListsMap.get(source).put(destination, distance);
            if (!isDirected()){
                this.adjacencyListsMap.get(destination).put(source, distance);
            }
        }   
    }

    /**
    * @param source is the Vertex of type V where the edge starts
    * @param destination is the Vertex of type V where the edge ends
    * @throws IllegalArgumentException if source or destination are null
    * @throws GraphException if the user tries to add and already existing Edge
    */
    public void removeEdge(V source, V destination) throws IllegalArgumentException, GraphException{
        if (!isEdgePresent(source, destination)){ throw new GraphException("Graph removeEdge: cannot remove a non-existing Edge"); }
        if(isVertexPresent(source) && isVertexPresent(destination)){
            this.adjacencyListsMap.get(source).remove(destination);
            if (!isDirected()) {
                this.adjacencyListsMap.get(destination).remove(source);
            }
        } else {
            throw new GraphException("Graph removeEdge: cannot remove inexistent edge");
        }
    }

    /**
    * @param source is the Vertex of type V where the edge starts
    * @param destination is the Vertex of type V where the edge ends
    * @return the desired Edge label of type D
    * @throws IllegalArgumentException if source or destination are null
    * @throws GraphException if Edge is not present
    */
    public D getEdgeLabel(V source, V destination) throws IllegalArgumentException, GraphException{
        if (!isEdgePresent(source, destination)){ throw new GraphException("Graph getEdgeLabel: cannot get label if the edge is not present"); } //segnala errore con Exception
        return adjacencyListsMap.get(source).get(destination);
    }

    /**
    * @return the Collection of all Vertexes
    * @throws GraphException if the Graph has no Vertexes
    */
    public Set<V> getAllVertexes() throws GraphException{
        if(vertexesNumber() == 0) { throw new GraphException("Graph getAllVertexes: no vertexes present"); }
        Set<V> keys = new HashSet<>();
        keys = adjacencyListsMap.keySet();
        return keys;
    }

    /**
    * @return the Collection of all Edges, loaded in a LinkedList in order to keep track of the order for KruskalMST
    * @throws GraphException if the Graph has no Edges
    */
    public LinkedList<Edge<V, D>> getAllEdges() throws GraphException {
        if(edgesNumber() == 0) { throw new GraphException("Graph getAllEdges: no edges present"); }
        LinkedList<Edge<V, D>> edgesList = new LinkedList<>();
        for (V source : this.adjacencyListsMap.keySet()) {  
            for (V destination : this.adjacencyListsMap.get(source).keySet()) {  
                edgesList.add(new Edge<>(source, destination, this.adjacencyListsMap.get(source).get(destination)));
            }
        }
        return edgesList;
    }

    /**
    * @param vertex
    * @return the Collection of all adiacent vertexes, loaded into a Set<V>
    * @throws GraphException if the Graph has no Edges
    */
    public Set<V> getAllAdjVertexes(V vertex) throws GraphException{
        if(!this.directed && this.adjacencyListsMap.get(vertex).size() == 0) { throw new GraphException("Graph getAllAdjVertexes: no edges present with vertex as source or destination"); }
        Set<V> keys = this.adjacencyListsMap.get(vertex).keySet();

        for (V key : this.adjacencyListsMap.keySet()) {  
            if (this.adjacencyListsMap.get(key).get(vertex) != null){
                keys.add(key);
            }
        }
        if(keys.size() == 0) { throw new GraphException("Graph getAllAdjVertexes: no edges present with vertex as source or destination"); }
        return keys;
    }
}