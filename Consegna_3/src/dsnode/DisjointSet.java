package dsnode;

import java.util.ArrayList;


public class DisjointSet {

    private static ArrayList<DSNode> treesArray = null;

    public DisjointSet(){
        treesArray = new ArrayList<DSNode>();
    }
    
    public static void MakeSet(DSNode node){
        DSNode newNode = new DSNode(node.getElem());
        newNode.setParent(newNode);
        treesArray.add(newNode);
    } 

    public static void union(DSNode nodex, DSNode nodey){
        link(findSet(nodex), findSet(nodey));
    }

    public static void link(DSNode nodex, DSNode nodey){
        if (nodex.getRank() > nodey.getRank()){
            nodey.setParent(nodex);
        } else {
            nodex.setParent(nodey);
            if (nodex.getRank() > nodey.getRank()){
                nodey.setRank(nodey.getRank() + 1);
            }
        }
    }

    public static DSNode findSet(DSNode node){
        if (node != node.getParent()){
            node.setParent(findSet(node.getParent()));
        }
        return node.getParent();
    }
}
