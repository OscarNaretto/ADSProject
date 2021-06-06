package disjointset;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;


public class DisjointSetTest {
    DisjointSet<Integer> test;
    DisjointSet<Integer> testEmpty;

    /**
     * @throws DisjointSetException element already present
     * @throws Exception generic test exception
     */
    @Before
    public void NodesGenerator() throws DisjointSetException, Exception{
        test = new DisjointSet<Integer>();
        testEmpty = new DisjointSet<Integer>();
        
        test.makeSet(1);
        test.makeSet(2);
        test.makeSet(3);
        test.makeSet(4);
    }

    /**
     * @throws Exception generic test exception
     */
    @Test
    public void makeSetTestRank() throws Exception{
        test.union(1, 2);
        test.union(3, 2);

        assertTrue(test.map.get(1).getRank() == 1);
        assertTrue(test.map.get(2).getRank() == 1);
        assertTrue(test.map.get(3).getRank() == 1);

        assertTrue(test.map.get(1).getElem() == 2);
        assertTrue(test.map.get(3).getElem() == 2);
    }

    /**
     * @throws Exception generic test exception
     */
    @Test
    public void makeSetTestElem() throws Exception{
        test.union(1, 2);
        test.union(3, 2);

        assertTrue(test.map.get(1).getElem() == 2);
        assertTrue(test.map.get(3).getElem() == 2);
    }

    /**
     * @throws Exception generic test exception
     */    
    @Test
    public void testUnionSetZeroElem() throws Exception{
        assertEquals(0, testEmpty.mapSize());
    }

    /**
     * @throws Exception generic test exception
     */    
    @Test
    public void testUnionSetFourElem() throws Exception{
        assertEquals(4, test.mapSize());
    }

    /**
     * @throws IllegalArgumentException element is null
     * @throws Exception generic test exception
     */    
    @Test
    public void testUnionSetIsPresent() throws IllegalArgumentException, Exception{
        assertTrue(test.isPresent(1));
        assertTrue(test.isPresent(3));
        assertTrue(test.isPresent(2));
        assertTrue(test.isPresent(4));
    }

    /**
     * @throws IllegalArgumentException if added element is null
     * @throws Exception generic test exception
     */
    @Test
    public void testUnionSetIsNotPresent() throws IllegalArgumentException, Exception{
        assertTrue(test.isPresent(1));
        assertTrue(test.isPresent(3));
        assertTrue(test.isPresent(2));
        assertFalse(test.isPresent(5));
    }

    /**
     * @throws IllegalArgumentException if added element is null
     * @throws Exception generic test exception
     */
    @Test(expected = IllegalArgumentException.class)
    public void testMakeSetArrgumentException() throws IllegalArgumentException, Exception{
        test.makeSet(null);
    }

    /**
     * @throws DisjointSetException if added element is already present
     * @throws Exception generic test exception
     */
    @Test(expected = DisjointSetException.class)
    public void testMakeSetDoubleAddException() throws DisjointSetException, Exception{
        test.makeSet(1);
    }
}
