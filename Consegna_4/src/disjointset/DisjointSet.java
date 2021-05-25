package disjointset;

import java.util.HashMap;
import java.util.Set;

/**
 * @param <T>
 */
public class DisjointSet<T> {
    public HashMap <T,Node<T>> map;
    
    //Overload
    public DisjointSet(){
        this.map = new HashMap<>();
    }

    public DisjointSet(Set<T> vertexesSet) throws DisjointSetException{
        this();
        for (T vertex: vertexesSet){
            makeSet(vertex);
        }
    }

    //
    public void makeSet(T element) throws DisjointSetException{
        if (element == null){ 
            throw new DisjointSetException("DisjointSet makeSet: cannot accept null as element"); 
        } 
        if(!isPresent(element)){
            Node<T> newNode = new Node<>(element);
            newNode.setParent(newNode);
            map.put(element, newNode);
        }
    } 

    //changed from void to bool to check in KruskalMST if the operation succedeed correctly
    public boolean union(T elemx, T elemy) throws DisjointSetException{
        if (elemx == null || elemy == null ){ 
            throw new DisjointSetException("DisjointSet union: cannot accept null as element");
        }
        if (isPresent(elemx) && isPresent(elemy)){
            Node<T> nodex = (Node<T>) map.get(elemx);
            Node<T> nodey = (Node<T>) map.get(elemy);
            return link(findSet(nodex), findSet(nodey));
        }else{
            System.out.println("Element not present"); //lancia eccezione
            return false;
        }
    }

    //changed from void to bool to check in KruskalMST if the operation succedeed correctly
    private boolean link(Node<T> nodex, Node<T> nodey){
        if (nodex == nodey){
            return false;
        }else{
            if (nodex.getRank() > nodey.getRank()){
                nodey.setParent(nodex);
                map.put(nodey.getElem(), nodex);
            } else {
                nodex.setParent(nodey);
                if (nodex.getRank() == nodey.getRank()){
                    nodey.setRank(nodey.getRank() + 1);
                }
                map.put(nodex.getElem(), nodey);
            }
            return true;
        }  
    }

    private Node<T> findSet(Node<T> node){
        if (node != node.getParent()){
            node.setParent(findSet(node.getParent()));
        }
        return node.getParent();
    }

    public int mapSize(){
        return this.map.size();
    }
    
    public boolean isPresent(T elem) throws DisjointSetException{
        if (elem == null){ 
            throw new DisjointSetException("DisjointSet isPresent: cannot accept null as element");
        }
        if (map.get(elem) != null) {
            return findSet(map.get(elem)).getElem() != null;
        }
        return false;
    }
}
