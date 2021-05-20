package disjointset;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;


public class DisjointSetTest {
    DisjointSet<Integer> test;
    DisjointSet<Integer> testEmpty;


    @Before
    public void NodesGenerator(){
        test = new DisjointSet<Integer>();
        testEmpty = new DisjointSet<Integer>();
        
        test.makeSet(1);
        test.makeSet(2);
        test.makeSet(3);
        test.makeSet(4);
    }

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

    @Test
    public void makeSetTestElem() throws Exception{
        test.union(1, 2);
        test.union(3, 2);

        assertTrue(test.map.get(1).getElem() == 2);
        assertTrue(test.map.get(3).getElem() == 2);
    }

    @Test
    public void testUnionSetZeroElem() throws Exception{
        assertEquals(0, testEmpty.mapSize());
    }

    @Test
    public void testUnionSetFourElem() throws Exception{
        assertEquals(4, test.mapSize());
    }

    @Test
    public void testUnionSetIsPresent() throws Exception{
        assertTrue(test.isPresent(1));
        assertTrue(test.isPresent(3));
        assertTrue(test.isPresent(2));
        assertTrue(test.isPresent(4));
    }

    @Test
    public void testUnionSetIsNotPresent() throws Exception{
        assertTrue(test.isPresent(1));
        assertTrue(test.isPresent(3));
        assertTrue(test.isPresent(2));
        assertFalse(test.isPresent(5));
    }
}
