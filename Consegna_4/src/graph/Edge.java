package graph;

public class Edge<V> implements Comparable<Edge<V>>{
    private V source;
    private V destination;
    private double label;

    public Edge(V source, V destination, double label) {
        this.source = source;
        this.destination = destination;
        this.label = label;
    }
    
    public V getSource() {
        return this.source;
    }

    public void setSource(V start) {
        this.source = start;
    }

    public V getDestination() {
        return this.destination;
    }

    public void setDestination(V end) {
        this.destination = end;
    }

    public double getLabel() {
        return this.label;
    }

    public void setLabel(double label) {
        this.label = label;
    }

    @Override
    public boolean equals(Object o){
        if (!(o instanceof Edge)){ 
            return false; 
        } else {
            Edge<V> e = (Edge<V>) o;
            return this.source == e.getSource() && this.destination == e.getDestination() && this.label == e.getLabel();
        }   
    }

    @Override
    public int compareTo(Edge<V> edge){
        if (this.label > edge.getLabel()){
            return 1;
        } else if (this.label == edge.getLabel()){
            return 0;
        }else {
            return -1;
        }
    }
}
