package disjointset;

/**
 * @param <T>
 */
public class Node<T>{
    private Node<T> parent;
    private T elem;
    private int rank;


    Node(T elem){ 
        this.elem = elem;
        this.parent = null;
        this.rank = 0;
    }

    void setElem(T elem){
        this.elem = elem;
    }

    void setRank(int rank){
        this.rank = rank;
    }

    void setParent(Node<T> parent){
        this.parent = parent;
    }
    
    Node<T> getParent(){
        return parent;
    }

    int getRank(){
        return rank;
    }

    T getElem(){
        return elem;
    } 
}