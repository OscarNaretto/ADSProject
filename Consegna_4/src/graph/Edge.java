package graph;

public class Edge<V> implements Comparable<Edge<V>>{
    private V start;
    private V end;
    private double label;

    Edge(V start, V end, double label) {
        this.start = start;
        this.end = end;
        this.label = label;
    }
    
    public V getStart() {
        return this.start;
    }

    public void setStart(V start) {
        this.start = start;
    }

    public V getEnd() {
        return this.end;
    }

    public void setEnd(V end) {
        this.end = end;
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
            return this.start == e.getStart() && this.end == e.getEnd() && this.label == e.getLabel();
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
