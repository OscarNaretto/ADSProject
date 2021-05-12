package dsnode;

public class DSNode{

    private DSNode parent;
    private int elem;
    private int rank;


    DSNode(int elem){ 
        this.elem = elem;
        this.parent = null;
        this.rank = 0;
    }

    void setElem(int elem){
        this.elem = elem;
    }

    void setRank(int rank){
        this.rank = rank;
    }

    void setParent(DSNode parent){
        this.parent = parent;
    }
    
    DSNode getParent(){
        return parent;
    }

    int getRank(){
        return rank;
    }

    int getElem(){
        return elem;
    }
    
}