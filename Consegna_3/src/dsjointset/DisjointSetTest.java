package disjointset;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;


public class DisjointSetTest {
 
    private Node<Integer> t1;
    private Node<Integer> t2;
    private Node<Integer> t3;
    private Node<Integer> t4;
    private Node<Integer> t5;
    DisjointSet<Integer> test;

    @Before
    public void NodesGenerator(){
        test = new DisjointSet<Integer>();
        t1 = new Node<Integer>(3);
        t2 = new Node<Integer>(9);
        t3 = new Node<Integer>(12);
        t4 = new Node<Integer>(32);
        t5 = new Node<Integer>(21);
    }

    @Test
    public void makeSetTest() throws Exception{
        t1.setParent(t2);
        t1.setRank(1);
        Node<Integer> node1 = test.makeSet(t1);

        assertTrue(t1.getRank() == 1);
        assertTrue(node1.getRank() == 0);
        assertTrue(t1.getParent() == t2);
        assertTrue(node1.getParent() == node1);
        assertFalse(t1.getParent() == node1.getParent());
    }

    @Test
    public void testRankTwoElem() throws Exception{
        Node<Integer> node1 = test.makeSet(t1);
        Node<Integer> node2 = test.makeSet(t2);

        assertTrue(node1.getRank() == 0);
        assertTrue(node2.getRank() == 0);

        test.union(node1, node2);
        assertTrue(node1.getRank() == 0);
        assertTrue(node2.getRank() == 1);
    }

    @Test
    public void testUnionOneElem() throws Exception{
        Node<Integer> node1 = test.makeSet(t1);
        assertEquals(test.findSet(node1), test.findSet(node1));
    }

    @Test
    public void testUnionSetTwoElem() throws Exception{
        Node<Integer> node1 = test.makeSet(t1);
        Node<Integer> node2 = test.makeSet(t2);
        Node<Integer> node3 = test.makeSet(t3);

        test.union(node1, node2);
        test.union(node3, test.findSet(node1));

        assertEquals(test.findSet(node3), test.findSet(node2));
    }

    @Test
    public void testUnionSetThreeElem() throws Exception{
        Node<Integer> node1 = test.makeSet(t1);
        Node<Integer> node2 = test.makeSet(t2);
        Node<Integer> node3 = test.makeSet(t3); 
        Node<Integer> node4 = test.makeSet(t4); 
        Node<Integer> node5 = test.makeSet(t5); 

        test.union(node1, node2);
        test.union(node3, node2);
        test.union(node5, node4);
        test.union(node5, node2);

        assertEquals(test.findSet(node3), test.findSet(node2));
        assertEquals(test.findSet(node4), test.findSet(node1));

    }
}
