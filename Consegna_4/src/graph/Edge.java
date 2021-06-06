package graph;

public class Edge<V, D> implements Comparable<Edge<V, D>>{
    private V source;
    private V destination;
    private D label;

    public Edge(V source, V destination, D label) throws IllegalArgumentException{
        if(source == null || destination == null || label == null) { throw new IllegalArgumentException("Edge constructor: parameters cannot be null"); }
        this.source = source;
        this.destination = destination;
        this.label = label;
    }
    
    public V getSource() {
        return this.source;
    }

    public void setSource(V source) throws IllegalArgumentException{
        if(source == null){ throw new IllegalArgumentException("Edge setSource: Vertex parameters cannot be null"); }
        this.source = source;
    }

    public V getDestination(){
        return this.destination;
    }

    public void setDestination(V destination) throws IllegalArgumentException{
        if(destination == null){ throw new IllegalArgumentException("Edge setDestination: Vertex parameters cannot be null"); }
        this.destination = destination;
    }

    public D getLabel() {
        return this.label;
    }

    public void setLabel(D label) {
        this.label = label;
    }

    @Override
    public int hashCode() {
        int result = 1;
        result = 31 * result + ((source == null) ? 0 : source.hashCode());
        result = 31 * result + ((destination == null) ? 0 : destination.hashCode());
        result = 31 * result + ((label == null) ? 0 : label.hashCode());
        return result;
    }

    @Override
    public boolean equals(Object o){
        if (this == o){ return true; }
        if (o == null) {return false; }
        if (this.getClass() != o.getClass()){ return false; }
        Edge<V, D> other = (Edge<V, D>) o;

        if (source == null) {
            if (other.source != null) {return false; }
        } else if (!source.equals(other.source)) { return false; }

        if (destination == null) {
            if (other.destination != null) { return false; }
        } else if (!destination.equals(other.destination)) { return false; }
        return true;
    }

    @Override
    public int compareTo(Edge<V, D> edge){
        if (!(edge.label instanceof Double)){ 
            try {
                throw new GraphException("Edge compareTo: label type D is not an instance of Double");
            } catch (GraphException e) {
                e.printStackTrace();
            } 
        }
        return Double.compare((double)this.label, (double)edge.label);
    }
}
