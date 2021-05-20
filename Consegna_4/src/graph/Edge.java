package graph;

public class Edge<V, D>{
    private V start;
    private V end;
    private D label;

    Edge(V start, V end, D label) {
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

    public D getLabel() {
        return this.label;
    }

    public void setLabel(D label) {
        this.label = label;
    }

    @Override
    public boolean equals(Object o){
        if (!(o instanceof Edge)){ 
            return false; 
        } else {
            Edge<V, D> e = (Edge<V, D>) o;
            return this.start == e.getStart() && this.end == e.getEnd() && this.label == e.getLabel();
        }   
    }
}
