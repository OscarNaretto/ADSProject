package graph;

import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Map;
import java.util.Set;


/**
 * @param <V>   //Vertex and Distance
 */
public class Graph<V>{
    private boolean directed;
    private HashMap<V,HashMap<V, Double>> adjacencyLists;
    //HashMap<V,HashMap<V,D>> contains Vertexes of the Graph as keys and adjacencyLists as values (HashMap<V,D>)
    //HashMap<V,D> contains adjacency vertexes as keys and distances between Vertexes as values

    public Graph(){
        this(true);
    }

    //standard behaviour: directed graph
    public Graph(boolean directed){
        this.directed = directed;
        this.adjacencyLists = new HashMap<>();
    }

    public Graph(LinkedList<Edge<V>> edgesList){
        this(true, edgesList);
    }

    public Graph(boolean directed, LinkedList<Edge<V>> edgesList){
        this.directed = directed;
        this.adjacencyLists = new HashMap<>();

        for (Edge<V> edge : edgesList) {
            V source = edge.getSource();
            V destination = edge.getDestination();
            this.addVertex(source);
            this.addVertex(destination);
            this.addEdge(source, destination, edge.getLabel());
        }
    }

    public boolean isDirected(){
        return directed; 
    }

    public int vertexesNumber(){ 
        return this.adjacencyLists.size(); 
    }

    public int edgesNumber(){
        int tot = 0;

        for (V key : adjacencyLists.keySet()){
            tot = tot + adjacencyLists.get(key).size();
        }
        if (!isDirected()){ tot = tot / 2; }

        return tot;
    }

    public boolean isVertexPresent(V vertex){ 
        return this.adjacencyLists.containsKey(vertex); 
    }

    public void addVertex(V vertex){
        if(!isVertexPresent(vertex)){
            adjacencyLists.put(vertex,new HashMap<>());
        }   
    }

    public void removeVertex(V vertex){
        this.adjacencyLists.remove(vertex);           //removes vertex

        for (V key : this.adjacencyLists.keySet()) {  //removes "edges"; actually removes end vertex from HashMap<V,D>
            this.adjacencyLists.get(key).remove(vertex);
        } 
    }

    public boolean isEdgePresent(V source, V destination) {
        return adjacencyLists.containsKey(source) && adjacencyLists.get(source).containsKey(destination);
    }

    public void addEdge(V source, V destination, double distance){
        if(isVertexPresent(source) && isVertexPresent(destination) && !isEdgePresent(source, destination)){
            this.adjacencyLists.get(source).put(destination, distance);
            if (!isDirected()){
                this.adjacencyLists.get(destination).put(source, distance);
            }

            //Se aggiungo l'arco anche alla List, usata come attributo di Graph, getAllEdges è in O(1) e addEdge rimane costante
            //Edge<V> e = new Edge<>(source, destination, distance);    
            //edgesList = new LinkedList<>();
            //edgesList.add(e);
        }   
    }

    public void removeEdge(V source, V destination) throws GraphException{
        if(isVertexPresent(source) && isVertexPresent(destination) && isEdgePresent(source, destination)){
            this.adjacencyLists.get(source).remove(destination);
            if (!isDirected()) {
                this.adjacencyLists.get(destination).remove(source);
            }
            //nel caso, implementare rimozione dalla List
        } else {
            throw new GraphException("Graph removeEdge: cannot remove inexistent edge");
        }
    }

    public double getEdgeLabel(V source, V destination) throws GraphException{
        if (!isEdgePresent(source, destination)){ throw new GraphException("Graph getEdgeLabel: cannot get label if the edge is not present"); } //segnala errore con Exception
        return adjacencyLists.get(source).get(destination);
    }

    public Set<V> getAllVertexes(){
        Set<V> keys = new HashSet<>();
        keys = adjacencyLists.keySet();
        return keys;
    }

    //Recupero degli archi del grafo – O(n) DA CONFERMARE: O(n) CON n NUMERO DI ARCHI. 
    //Si può ottenere O(1) salvando ogni nuovo arco in un Set, ma si rallenta il resto anche quando non richiesto
    public LinkedList<Edge<V>> getAllEdges() throws GraphException {
        if(edgesNumber() == 0) { throw new GraphException("Graph getAllEdges: no edges present"); }
        LinkedList<Edge<V>> edgesList = new LinkedList<>();

        for (Map.Entry<V,HashMap<V, Double>> vert : adjacencyLists.entrySet()){
            for (Map.Entry<V,Double> edge : vert.getValue().entrySet()) {
                edgesList.add(new Edge<>(vert.getKey(), edge.getKey(), edge.getValue()));
            }
        }
        return edgesList;
    }

    public Set<V> getAllAdjVertexes(V vertex){
        Set<V> keys = this.adjacencyLists.get(vertex).keySet();
        return keys;
    }
}