package disjointset;

import java.util.HashMap;
import java.util.Set;

/**
 * @param <T>
 */
public class DisjointSet<T> {
    public HashMap <T,Node<T>> map;
    
    public DisjointSet(){
        this.map = new HashMap<>();
    }

    public DisjointSet(Set<T> vertexesSet){
        this();
        for (T vertex: vertexesSet){
            makeSet(vertex);
        }
    }


    public void makeSet(T element){
        if (element != null && !isPresent(element)){
            Node<T> newNode = new Node<>(element);
            newNode.setParent(newNode);
            map.put(element, newNode);
        } else {
            System.out.println("Element already present or null");
        }
    } 

    //changed from void to bool to check in KruskalMST if the operation succedeed correctly
    public boolean union(T elemx, T elemy){
        if (isPresent(elemx) && isPresent(elemy) && elemx != null && elemy != null){
            Node<T> nodex = (Node<T>) map.get(elemx);
            Node<T> nodey = (Node<T>) map.get(elemy);

            
            return true && link(findSet(nodex), findSet(nodey));
        } else {
            System.out.println("Element not present");
            return false;
        }
    }

    //changed from void to bool to check in KruskalMST if the operation succedeed correctly
    private boolean link(Node<T> nodex, Node<T> nodey){
        if (nodex == nodey){
            return false;
        } else {
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
    
    public boolean isPresent(T elem){
        if (map.get(elem) != null) {
            Node<T> node = (Node<T>) map.get(elem);
            if (node != null) {
                return findSet(node).getElem() != null;
            }
        }
        return false;
    }
}
