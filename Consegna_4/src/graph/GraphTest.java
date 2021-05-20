package graph;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;

public class GraphTest {
    Graph<String, Integer> testDirected;
    Graph<String, Integer> testNDirected;
    Graph<String, Integer> testEmpty;

    @Before
    public void GraphsGenerator(){
        testDirected = new Graph<String, Integer>(true);
        testEmpty = new Graph<String, Integer>(false);
        testNDirected = new Graph<String, Integer>(false);


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
        assertEquals(Integer.valueOf(10), testDirected.getEdgeLabel("vertice_a", "vertice_b"));
        assertEquals(Integer.valueOf(2), testDirected.getEdgeLabel("vertice_c", "vertice_b"));
        assertEquals(Integer.valueOf(4), testDirected.getEdgeLabel("vertice_c", "vertice_d"));
    }

    @Test
    public void distanceEmptyTest() throws Exception{
        assertEquals(null, testEmpty.getEdgeLabel("vertice_c", "vertice_b"));
        assertEquals(null, testEmpty.getEdgeLabel("vertice_a", "vertice_b"));
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
    public void removeVertexTest(){
        testDirected.removeVertex("vertice_a");
        testEmpty.removeVertex("vertice_a");

        assertFalse(testDirected.isVertexPresent("vertice_a"));
        assertFalse(testEmpty.isVertexPresent("vertice_a"));

        assertFalse(testDirected.isEdgePresent("vertice_a", "vertice_b"));
    }

    @Test
    public void removeEdgeTest(){
        testDirected.removeEdge("vertice_a", "vertice_b");
        testEmpty.removeEdge("vertice_c", "vertice_b");

        assertFalse(testDirected.isEdgePresent("vertice_a", "vertice_b"));
        assertFalse(testEmpty.isEdgePresent("vertice_a", "vertice_b"));
    }

    @Test
    public void directedGraphEdgeTest(){
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
}
