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
    Graph<String, Double> testDirected;
    Graph<String, Double> testNDirected;
    Graph<String, Double> testEmpty;

    /**
     * @throws GraphException when trying to add Vertexes or Edges already present
     */
    @Before
    public void GraphsGenerator() throws GraphException{
        testDirected = new Graph<String, Double>(true);
        testEmpty = new Graph<String, Double>(false);
        testNDirected = new Graph<String, Double>(false);

        testDirected.addVertex("vertice_a");
        testDirected.addVertex("vertice_b");
        testDirected.addVertex("vertice_c");
        testDirected.addVertex("vertice_d");
        testDirected.addEdge("vertice_a", "vertice_b", (double)10);
        testDirected.addEdge("vertice_c", "vertice_b", (double)2);
        testDirected.addEdge("vertice_c", "vertice_d", (double)4);

        testNDirected.addVertex("vertice_a");
        testNDirected.addVertex("vertice_b");
        testNDirected.addVertex("vertice_c");
        testNDirected.addVertex("vertice_d");
        testNDirected.addEdge("vertice_a", "vertice_b", (double)10);
        testNDirected.addEdge("vertice_c", "vertice_b", (double)2);
        testNDirected.addEdge("vertice_c", "vertice_d", (double)4);
    }

    /**
     * @throws Exception generic test exception
     */
    @Test
    public void emptyGraphSizesTest() throws Exception{
        assertEquals(0, testEmpty.vertexesNumber());
        assertEquals(0, testEmpty.edgesNumber());
    }

    /**
     * @throws Exception generic test exception
     */
    @Test
    public void notEmptyGraphSizesTest() throws Exception{
        assertEquals(4, testDirected.vertexesNumber());
        assertEquals(3, testDirected.edgesNumber());
    }

    /**
     * @throws Exception generic test exception
     */
    @Test
    public void isDirectedTrueTest() throws Exception{
        assertTrue(testDirected.isDirected());
    }

    /**
     * @throws Exception generic test exception
     */
    @Test
    public void isDirectedFalseTest() throws Exception{
        assertFalse(testEmpty.isDirected());
    }

    /**
     * @throws IllegalArgumentException if source or destination are null
     * @throws GraphException if Edge is not present
     * @throws Exception generic test exception
     */
    @Test
    public void distanceTest() throws IllegalArgumentException, GraphException, Exception{
        assertEquals(10, testDirected.getEdgeLabel("vertice_a", "vertice_b"), 0.0002);
        assertEquals(2, testDirected.getEdgeLabel("vertice_c", "vertice_b"), 0.0002);
        assertEquals(4, testDirected.getEdgeLabel("vertice_c", "vertice_d"), 0.0002);
    }

    /**
     * @throws IllegalArgumentException if source or destination are null
     * @throws GraphException if Edge is not present
     * @throws Exception generic test exception
     */
    @Test(expected = GraphException.class)
    public void distanceEmptyTest() throws IllegalArgumentException, GraphException, Exception{
        testEmpty.getEdgeLabel("vertice_c", "vertice_b");
    }

    /**
     * @throws IllegalArgumentException if source or destination are null
     * @throws Exception generic test exception
     */
    @Test
    public void isVertexPresentTrueTest() throws IllegalArgumentException, Exception{
        assertTrue(testDirected.isVertexPresent("vertice_a"));
        assertTrue(testDirected.isVertexPresent("vertice_b"));
        assertTrue(testDirected.isVertexPresent("vertice_c"));
        assertTrue(testDirected.isVertexPresent("vertice_d"));
    }

    /**
     * @throws IllegalArgumentException if parameters passed to isVertexPresent are null
     * @throws Exception generic test exception
     */
    @Test
    public void isVertexPresentFalseTest() throws IllegalArgumentException, Exception{
        assertFalse(testDirected.isVertexPresent("vertice"));
        assertFalse(testDirected.isVertexPresent("verticale"));
        assertFalse(testEmpty.isVertexPresent("vertice"));
        assertFalse(testEmpty.isVertexPresent("verticale"));
    }

    /**
     * @throws IllegalArgumentException if parameters passed to isEdgePresent are null
     * @throws Exception generic test exception
     */
    @Test
    public void isEdgePresentTrueTest() throws IllegalArgumentException, Exception{
        assertTrue(testDirected.isEdgePresent("vertice_a", "vertice_b"));
        assertTrue(testDirected.isEdgePresent("vertice_c", "vertice_b"));
        assertTrue(testDirected.isEdgePresent("vertice_c", "vertice_d"));
    }

    /**
     * @throws IllegalArgumentException if parameters passed to isEdgePresent are null
     * @throws Exception generic test exception
     */
    @Test
    public void isEdgePresentFalseTest() throws IllegalArgumentException, Exception{
        assertFalse(testDirected.isEdgePresent("vertice_a", "vertice_d"));
        assertFalse(testDirected.isEdgePresent("vertice_c", "vertice_a"));
        assertFalse(testDirected.isEdgePresent("vertice_b", "vertice_d"));

        assertFalse(testEmpty.isEdgePresent("vertice_a", "vertice_d"));
        assertFalse(testEmpty.isEdgePresent("vertice_c", "vertice_a"));
        assertFalse(testEmpty.isEdgePresent("vertice_b", "vertice_d"));
    }

    /**
     * @throws IllegalArgumentException if parameters passed to removeVertex or isVertexPresent are null
     * @throws GraphException if Vertex element is null
     * @throws Exception generic test exception
     */
    @Test
    public void removeVertexTest() throws IllegalArgumentException, GraphException, Exception{
        testDirected.removeVertex("vertice_a");
        testEmpty.removeVertex("vertice_a");

        assertFalse(testDirected.isVertexPresent("vertice_a"));
        assertFalse(testEmpty.isVertexPresent("vertice_a"));

        assertFalse(testDirected.isEdgePresent("vertice_a", "vertice_b"));
    }

    /**
     * @throws IllegalArgumentException if parameters passed to removeEdge are null
     * @throws GraphException if the Edge we want to remove is not present 
     * @throws Exception generic test exception
     */
    @Test
    public void removeEdgeTest() throws GraphException, Exception{
        testDirected.removeEdge("vertice_a", "vertice_b");
        assertFalse(testDirected.isEdgePresent("vertice_a", "vertice_b"));
    }

    /**
     * @throws IllegalArgumentException if parameters passed to removeEdge are null
     * @throws GraphException if the Edge we want to remove is not present 
     * @throws Exception generic test exception
     */
    @Test(expected = GraphException.class)
    public void removeEdgeEmptyTest() throws IllegalArgumentException, GraphException, Exception{
        testEmpty.removeEdge("vertice_c", "vertice_b");
    }
    
    /**
     * @throws IllegalArgumentException if null values are passed to the methods isEdgePresent or removeEdge
     * @throws GraphException if the Edge we want to remove is not present 
     * @throws Exception generic test exception
     */
    @Test
    public void directedGraphEdgeTest() throws IllegalArgumentException, GraphException, Exception{
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

    /**
     * @throws GraphException if the Graph has no Vertexes
     * @throws Exception generic test exception
     */
    @Test
    public void getAllVertexesTest() throws GraphException, Exception{
        Set<String> keys = new HashSet<>();

        keys.add("vertice_a");
        keys.add("vertice_b");
        keys.add("vertice_c");
        keys.add("vertice_d");

        assertEquals(keys, testDirected.getAllVertexes());
    }

    /**
     * @throws GraphException if the Graph has no Vertexes
     * @throws Exception generic test exception
     */
    @Test(expected = GraphException.class)
    public void getAllVertexesTestEmpty() throws GraphException, Exception{
        Set<String> keys = new HashSet<>();

        assertEquals(keys, testEmpty.getAllVertexes());
    }

    /**
     * @throws IllegalArgumentException if null values are passed to Edge constructor
     * @throws GraphException if the Graph has no Edges
     * @throws Exception generic test exception
     */
    @Test
    public void getAllEdgesEqualsTest() throws IllegalArgumentException, GraphException, Exception{
        LinkedList<Edge<String, Double>> edges = new LinkedList<>();
        LinkedList<Edge<String, Double>> edgesTaken = new LinkedList<>();

        Edge<String, Double> e1 = new Edge <>("vertice_a", "vertice_b", (double)10);
        Edge<String, Double> e2 = new Edge <>("vertice_c", "vertice_b", (double)2);
        Edge<String, Double> e3 = new Edge <>("vertice_c", "vertice_d", (double)4);
        Edge<String, Double> e4 = new Edge <>("vertice_c", "vertice_d", (double)4);
        
        edges.add(e1);
        edges.add(e2);
        edges.add(e3);
        
        assertEquals(e3, e4);
        
        edgesTaken = testDirected.getAllEdges();
        edges.sort(null);
        edgesTaken.sort(null);
        assertEquals(edges, edgesTaken);
    }

    /**
     * @throws GraphException if the Graph has no Vertexes
     * @throws Exception generic test exception
     */
    @Test
    public void getAllAdjVertexes() throws GraphException, Exception{
        Set<String> adjVertexes = new HashSet<>();

        adjVertexes.add("vertice_b");
        adjVertexes.add("vertice_d");

        assertEquals(adjVertexes, testDirected.getAllAdjVertexes("vertice_c"));
    }
    
    /**
     * @throws IllegalArgumentException if null values are passed to Edge constructor
     * @throws GraphException if Edge.label is not an instance of Double
     * @throws Exception generic test exception
     */
    @Test
    public void compareToTest() throws IllegalArgumentException, GraphException, Exception{
        Edge<String, Double> e1 = new Edge <>("vertice_a", "vertice_b", (double)10);
        Edge<String, Double> e2 = new Edge <>("vertice_c", "vertice_b", (double)2);
        Edge<String, Double> e3 = new Edge <>("vertice_c", "vertice_b", (double)2);

        assertEquals(1, e1.compareTo(e2));
        assertEquals(-1, e2.compareTo(e1));
        assertEquals(0, e2.compareTo(e3));
    }
}
