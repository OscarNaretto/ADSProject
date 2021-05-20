package graph;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;


/**
 * @param <V,D>   //Vertex and Distance
 */

public class Graph<V,D>{
    private boolean directed;
    private HashMap<V,HashMap<V,D>> adjacencyLists;
    //HashMap<V,HashMap<V,D>> contains Vertexes of the Graph as keys and adjacencyLists as values (HashMap<V,D>)
    //HashMap<V,D> contains adjacency vertexes as keys and distances between Vertexes as values

    public Graph(boolean directed){
        this.directed = directed;
        this.adjacencyLists = new HashMap<>();
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

    public boolean isEdgePresent(V start, V end) {
        return adjacencyLists.containsKey(start) && adjacencyLists.get(start).containsKey(end);
    }

    public void addEdge(V start, V end, D distance){
        if(isVertexPresent(start) && isVertexPresent(end) && !isEdgePresent(start, end)){
            this.adjacencyLists.get(start).put(end, distance);
            if (!isDirected()){
                this.adjacencyLists.get(end).put(start, distance);
            }
        }   
    }

    public void removeEdge(V start, V end){
        if(isVertexPresent(start) && isVertexPresent(end)){
            this.adjacencyLists.get(start).remove(end);
            if (!isDirected()) {
                this.adjacencyLists.get(end).remove(start);
            }
        }
    }

    public D getEdgeLabel(V start, V end){
        if (!isEdgePresent(start, end)){ return null; }
        return adjacencyLists.get(start).get(end);
    }

    //Recupero dei nodi del grafo – O(n)            
    public Set<V> getAllVertexes(){
        Set<V> keys = new HashSet<>();
        keys = adjacencyLists.keySet();
        return keys;
    }

    //Recupero degli archi del grafo – O(n) DA CONFERMARE: O(n) CON n NUMERO DI ARCHI. 
    //Si può ottenere O(1) salvando ogni nuovo arco in un Set, ma si rallenta il resto anche quando non richiesto
    public Set<Edge<V, D>> getAllEdges() {
        if(edgesNumber() == 0) { return null; }

        Set<Edge<V, D>> edgesSet = new HashSet<>();

        for (Map.Entry<V,HashMap<V,D>> node : adjacencyLists.entrySet()){
            for (Map.Entry<V,D> edge : node.getValue().entrySet()) {
                edgesSet.add(new Edge<>(node.getKey(), edge.getKey(), edge.getValue()));
            }
        }
        return edgesSet;
    }

    //Recupero nodi adiacenti di un dato nodo – O(1) 
    public Set<V> getAllAdjVertexes(V vertex){
        Set<V> keys = this.adjacencyLists.get(vertex).keySet();
        return keys;
    }
}