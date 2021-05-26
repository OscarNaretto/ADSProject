package disjointset;

/**
 * @param <T> //Generic Type
 */
public class Node<T>{
    private Node<T> parent;
    private T elem;
    private int rank;

/**
 * @param elem element of the node
 */
    Node(T elem){ 
        this.elem = elem;
        this.parent = null;
        this.rank = 0;
    }

/**
 * @param elem element to be set
 */
    void setElem(T elem){
        this.elem = elem;
    }

/**
 * @param rank rank to be set
 */
    void setRank(int rank){
        this.rank = rank;
    }

/**
 * @param parent parent to be set
 */
    void setParent(Node<T> parent){
        this.parent = parent;
    }
    
/**
 * @return it returns the parent
 */
    Node<T> getParent(){
        return parent;
    }

/**
 * @return it returns the rank
 */    
    int getRank(){
        return rank;
    }

/**
 * @return it returns the element
 */
    T getElem(){
        return elem;
    } 
}