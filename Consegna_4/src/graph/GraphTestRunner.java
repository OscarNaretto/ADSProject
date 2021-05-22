package graph;

import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

public class GraphTestRunner {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_BLUE = "\u001B[34m";

    /**
     * @param args command line arguments
     */
    public static void main(String[] args){
        
        Result result = JUnitCore.runClasses(GraphTest.class);
        for (Failure failure : result.getFailures()) {
            System.out.println(failure.toString());
        }
        
        System.out.println(ANSI_BLUE + "GraphTest completed, result: " + result.wasSuccessful() + ANSI_RESET);
    }
}
