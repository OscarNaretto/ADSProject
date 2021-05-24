package graph;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.Set;

import org.junit.Before;
import org.junit.Test;

public class GraphTest {
    Graph<String> testDirected;
    Graph<String> testNDirected;
    Graph<String> testEmpty;

    @Before
    public void GraphsGenerator() throws GraphException{
        testDirected = new Graph<String>(true);
        testEmpty = new Graph<String>(false);
        testNDirected = new Graph<String>(false);

        testDirected.addVertex("vertice_a");
        testDirected.addVertex("vertice_b");
        testDirected.addVertex("vertice_c");
        testDirected.addVertex("vertice_d");
        testDirected.addEdge("vertice_a", "vertice_b", 10);
        testDirected.addEdge("vertice_c", "vertice_b", 2);
        testDirected.addEdge("vertice_c", "vertice_d", 4);

        testNDirected.addVertex("vertice_a");
        testNDirected.addVertex("vertice_b");
        testNDirected.addVertex("vertice_c");
        testNDirected.addVertex("vertice_d");
        testNDirected.addEdge("vertice_a", "vertice_b", 10);
        testNDirected.addEdge("vertice_c", "vertice_b", 2);
        testNDirected.addEdge("vertice_c", "vertice_d", 4);
    }

    @Test
    public void emptyGraphSizesTest() throws Exception{
        assertEquals(0, testEmpty.vertexesNumber());
        assertEquals(0, testEmpty.edgesNumber());
    }

    @Test
    public void notEmptyGraphSizesTest() throws Exception{
        assertEquals(4, testDirected.vertexesNumber());
        assertEquals(3, testDirected.edgesNumber());
    }

    @Test
    public void isDirectedTrueTest() throws Exception{
        assertTrue(testDirected.isDirected());
    }

    @Test
    public void isDirectedFalseTest() throws Exception{
        assertFalse(testEmpty.isDirected());
    }

    @Test
    public void distanceTest() throws Exception{
        assertEquals(10, testDirected.getEdgeLabel("vertice_a", "vertice_b"), 0.0002);
        assertEquals(2, testDirected.getEdgeLabel("vertice_c", "vertice_b"), 0.0002);
        assertEquals(4, testDirected.getEdgeLabel("vertice_c", "vertice_d"), 0.0002);
    }

    @Test(expected = GraphException.class)
    public void distanceEmptyTest() throws Exception{
        testEmpty.getEdgeLabel("vertice_c", "vertice_b");
    }

    @Test
    public void isVertexPresentTrueTest() throws Exception{
        assertTrue(testDirected.isVertexPresent("vertice_a"));
        assertTrue(testDirected.isVertexPresent("vertice_b"));
        assertTrue(testDirected.isVertexPresent("vertice_c"));
        assertTrue(testDirected.isVertexPresent("vertice_d"));
    }
        
    @Test
    public void isVertexPresentFalseTest() throws Exception{
        assertFalse(testDirected.isVertexPresent("vertice"));
        assertFalse(testDirected.isVertexPresent("verticale"));
        assertFalse(testEmpty.isVertexPresent("vertice"));
        assertFalse(testEmpty.isVertexPresent("verticale"));
    }

    @Test
    public void isEdgePresentTrueTest() throws Exception{
        assertTrue(testDirected.isEdgePresent("vertice_a", "vertice_b"));
        assertTrue(testDirected.isEdgePresent("vertice_c", "vertice_b"));
        assertTrue(testDirected.isEdgePresent("vertice_c", "vertice_d"));
    }

    @Test
    public void isEdgePresentFalseTest() throws Exception{
        assertFalse(testDirected.isEdgePresent("vertice_a", "vertice_d"));
        assertFalse(testDirected.isEdgePresent("vertice_c", "vertice_a"));
        assertFalse(testDirected.isEdgePresent("vertice_b", "vertice_d"));

        assertFalse(testEmpty.isEdgePresent("vertice_a", "vertice_d"));
        assertFalse(testEmpty.isEdgePresent("vertice_c", "vertice_a"));
        assertFalse(testEmpty.isEdgePresent("vertice_b", "vertice_d"));
    }

    @Test
    public void removeVertexTest() throws GraphException{
        testDirected.removeVertex("vertice_a");
        testEmpty.removeVertex("vertice_a");

        assertFalse(testDirected.isVertexPresent("vertice_a"));
        assertFalse(testEmpty.isVertexPresent("vertice_a"));

        assertFalse(testDirected.isEdgePresent("vertice_a", "vertice_b"));
    }

    @Test
    public void removeEdgeTest() throws GraphException{
        testDirected.removeEdge("vertice_a", "vertice_b");
        assertFalse(testDirected.isEdgePresent("vertice_a", "vertice_b"));
    }
    
    @Test(expected = GraphException.class)
    public void removeEdgeEmptyTest() throws GraphException{
        testEmpty.removeEdge("vertice_c", "vertice_b");
    }
    

    @Test
    public void directedGraphEdgeTest() throws GraphException{
        assertTrue(testNDirected.isEdgePresent("vertice_a", "vertice_b"));
        assertTrue(testNDirected.isEdgePresent("vertice_b", "vertice_a"));

        assertTrue(testNDirected.isEdgePresent("vertice_c", "vertice_d"));
        assertTrue(testNDirected.isEdgePresent("vertice_d", "vertice_c"));

        testNDirected.removeEdge("vertice_a", "vertice_b");
        testNDirected.removeEdge("vertice_d", "vertice_c");


        assertFalse(testNDirected.isEdgePresent("vertice_a", "vertice_b"));
        assertFalse(testNDirected.isEdgePresent("vertice_b", "vertice_a"));

        assertFalse(testNDirected.isEdgePresent("vertice_c", "vertice_d"));
        assertFalse(testNDirected.isEdgePresent("vertice_d", "vertice_c"));
    }

    @Test
    public void getAllVertexesTest(){
        Set<String> keys = new HashSet<>();

        assertEquals(keys, testEmpty.getAllVertexes());

        keys.add("vertice_a");
        keys.add("vertice_b");
        keys.add("vertice_c");
        keys.add("vertice_d");

        assertEquals(keys, testDirected.getAllVertexes());
    }

    @Test
    public void getAllEdgesEqualsTest() throws GraphException{
        LinkedList<Edge<String>> edges = new LinkedList<>();
        LinkedList<Edge<String>> edgesTaken = new LinkedList<>();

        Edge<String> e1 = new Edge <>("vertice_a", "vertice_b", 10);
        Edge<String> e2 = new Edge <>("vertice_c", "vertice_b", 2);
        Edge<String> e3 = new Edge <>("vertice_c", "vertice_d", 4);
        Edge<String> e4 = new Edge <>("vertice_c", "vertice_d", 4);
        
        edges.add(e1);
        edges.add(e2);
        edges.add(e3);
        
        assertEquals(e3, e4);   //metodo edge.equals(Object o) testato
        
        edgesTaken = testDirected.getAllEdges();
        assertEquals(edges, edgesTaken);
    }

    @Test
    public void getAllAdjVertexes(){
        Set<String> adjVertexes = new HashSet<>();

        adjVertexes.add("vertice_b");
        adjVertexes.add("vertice_d");

        assertEquals(adjVertexes, testDirected.getAllAdjVertexes("vertice_c"));
    }

    @Test
    public void compareToTest() throws GraphException{
        Edge<String> e1 = new Edge <>("vertice_a", "vertice_b", 10);
        Edge<String> e2 = new Edge <>("vertice_c", "vertice_b", 2);
        Edge<String> e3 = new Edge <>("vertice_c", "vertice_b", 2);

        assertEquals(1, e1.compareTo(e2));
        assertEquals(-1, e2.compareTo(e1));
        assertEquals(0, e2.compareTo(e3));
    }
}
