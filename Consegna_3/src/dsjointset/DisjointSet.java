package disjointset;

/**
 * @param <T>
 */
public class DisjointSet<T> {
    
    public Node<T> makeSet(Node<T> node){
        Node<T> newNode = new Node<>(node.getElem());
        newNode.setParent(newNode);
        return newNode;
    } 

    public void union(Node<T> nodex, Node<T> nodey){
        link(findSet(nodex), findSet(nodey));
    }

    public void link(Node<T> nodex, Node<T> nodey){
        if (nodex.getRank() > nodey.getRank()){
            nodey.setParent(nodex);
        } else {
            nodex.setParent(nodey);
            if (nodex.getRank() == nodey.getRank()){
                nodey.setRank(nodey.getRank() + 1);
            }
        }
    }

    public Node<T> findSet(Node<T> node){
        if (node != node.getParent()){
            node.setParent(findSet(node.getParent()));
        }
        return node.getParent();
    }
}
