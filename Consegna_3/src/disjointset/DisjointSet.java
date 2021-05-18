package disjointset;

import java.util.HashMap;

/**
 * @param <T>
 */
public class DisjointSet<T> {
    public HashMap <T,Node<T>> map;
    
    public DisjointSet(){
        this.map = new HashMap<T, Node<T>>();
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

    public void union(T elemx, T elemy){
        if (isPresent(elemx) && isPresent(elemy)){
            Node<T> nodex = (Node<T>) map.get(elemx);
            Node<T> nodey = (Node<T>) map.get(elemy);

            link(findSet(nodex), findSet(nodey));
        } else {
            System.out.println("Element not present");
        }
    }

    private void link(Node<T> nodex, Node<T> nodey){
        if (nodex == nodey){
            System.out.println("Elements already connected");
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
