package disjointset;

import java.util.HashMap;
import java.util.Set;

/**
 * @param <T> //Generic Type
 */
public class DisjointSet<T> {
    public HashMap <T,Node<T>> map;
    
    public DisjointSet(){
        this.map = new HashMap<>();
    }

    /**
     * @param vertexesSet collection of vertexes used to inizialize disjointset using makeSet
     * @throws IllegalArgumentException if the elements in the collection is null
     * @throws DisjointSetException if the element is already present and so cannot be add
     */
    public DisjointSet(Set<T> vertexesSet) throws IllegalArgumentException, DisjointSetException{
        this();
        for (T vertex: vertexesSet){
            makeSet(vertex);
        }
    }
    
    /**
    * @param element element to insert in the map
    * @throws IllegalArgumentException if the elements is null
    * @throws DisjointSetException if the element is already present and so cannot be add
    */
    public void makeSet(T element) throws IllegalArgumentException, DisjointSetException{
        if (element == null){ 
            throw new IllegalArgumentException("DisjointSet makeSet: cannot accept null as element"); 
        } 
        if (!isPresent(element)){
            Node<T> newNode = new Node<>(element);
            newNode.setParent(newNode);
            map.put(element, newNode);
        } else { 
            throw new DisjointSetException("DisjointSet makeSet: cannot add element already present"); 
        }
    } 

    /**
    * @param elemx element x to be link with another element 
    * @param elemy element y to be link with another element 
    * @return it returns true if the union was successful, otherwise it returns false
    * @throws IllegalArgumentException if one of the elements is null
    * @throws DisjointSetException if one element or both elements are not present
    */
    //changed from void to bool to check in KruskalMST if the operation succedeed correctly
    public boolean union(T elemx, T elemy) throws IllegalArgumentException, DisjointSetException{
        if (elemx == null || elemy == null ){ 
            throw new IllegalArgumentException("DisjointSet union: cannot accept null as element");
        }
        if (isPresent(elemx) && isPresent(elemy)){
            Node<T> nodex = (Node<T>) map.get(elemx);
            Node<T> nodey = (Node<T>) map.get(elemy);
            return link(findSet(nodex), findSet(nodey));
        }else{
            throw new DisjointSetException("DisjointSet union: one or both elements not present");
        }
    }

    /**
    * @param nodex node x to be link with another node 
    * @param nodey node y to be link with another node
    * @return it returns true if the link was successful, otherwise it returns false(example, the nodes are the same)
    */
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

    /**
    * @param node child of the identifier, that we are looking for
    * @return it returns the identifier of the collection
    */
    private Node<T> findSet(Node<T> node){
        if (node != node.getParent()){
            node.setParent(findSet(node.getParent()));
        }
        return node.getParent();
    }

    /**
     * @return it returns the size of the map
     */
    public int mapSize(){
        return this.map.size();
    }
   
    /**
    * @param elem element to understand if it is present in the map
    * @return it returns true if the element is present in the collection, otherwise it returns false
    * @throws IllegalArgumentException if the element is null it throws the exception
    */    
    public boolean isPresent(T elem) throws IllegalArgumentException{
        if (elem == null){ 
            throw new IllegalArgumentException("DisjointSet isPresent: cannot accept null as element");
        }
        if (map.get(elem) != null) {
            return findSet(map.get(elem)).getElem() != null;
        }
        return false;
    }
}
