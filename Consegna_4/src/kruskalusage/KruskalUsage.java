package kruskalusage;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.DecimalFormat;
import java.util.HashSet;
import java.util.Set;

import disjointset.DisjointSetException;

import java.nio.file.Files;

import graph.Edge;
import graph.Graph;
import graph.GraphException;
import kruskalmst.KruskalMST;

public class KruskalUsage{
    private static final Charset ENCODING = StandardCharsets.UTF_8;
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_RED = "\u001B[31m";

    /**
     * @param filepath file to be read consisting of an unspecified number of strings
     * @return a list of edges
     * @throws NumberFormatException thrown to indicate that the application has attempted to convert a string to one of the numeric types, but that the string does not have the appropriate format
     * @throws IOException signals that an I/O exception of some kind has occurred
     * @throws IllegalArgumentException if we pass null values to Edge constructor
     */
    private static Set<Edge<String, Double>> loadGraph(String filepath) throws NumberFormatException, IOException, IllegalArgumentException{
        Set<Edge<String, Double>> edgesList = new HashSet<>();
        
        Path inputFilePath = Paths.get(filepath);
        try(BufferedReader fileInputReader = Files.newBufferedReader(inputFilePath, ENCODING)){
            String line = null;
            while((line = fileInputReader.readLine()) != null){      
                String[] lineElements = line.split(",");  
                Edge<String, Double> edge = new Edge<String, Double>(lineElements[0], lineElements[1], Double.parseDouble(lineElements[2])); 
                Edge<String, Double> reverseedge = new Edge<String, Double>(lineElements[1], lineElements[0], Double.parseDouble(lineElements[2])); 
                if (!edgesList.contains(edge) && !edgesList.contains(reverseedge)) {
                    edgesList.add(edge);
                }
            }
        }
        return edgesList;
    }

    /**
     * @param filepath file to be read consisting of an unspecified number of strings
     * @see Edge(); Graph(); DisjointSet(); loadGraph()
     * @throws IOException signals that an I/O exception of some kind has occurred
     * @throws NumberFormatException thrown to indicate that the application has attempted to convert a string to one of the numeric types, but that the string does not have the appropriate format
     * @throws IllegalArgumentException generally if a null value is passed; go to 'see'
     * @throws GraphException generally thrown by Graph constructor; go to 'see'
     * @throws DisjointSetException generally thrown by DisjointSet constructor; go to 'see'
     */
    private static void kruskalExecution(String filepath) throws IOException, NumberFormatException, IllegalArgumentException, GraphException, DisjointSetException{
        long start, initial; 
        float elapsed; 

        System.out.println(ANSI_RED + "Loading data:" + ANSI_RESET);
        start = initial = System.currentTimeMillis();
        Graph<String, Double> graph = new Graph<String, Double>(false, loadGraph(filepath));
        elapsed = (System.currentTimeMillis() - start)/1000F;
        System.out.println("Data loaded, took: " + elapsed + "sec\n");

        KruskalMST<String> mst = new KruskalMST<>(graph); 
        System.out.println(ANSI_RED + "Calculating MST:" + ANSI_RESET);
        start = System.currentTimeMillis();
        mst.MST();
        elapsed = (System.currentTimeMillis() - start)/1000F;
        System.out.println("MST calculated, took: " + elapsed + "sec\n");

        System.out.println(ANSI_RED + "Stats:" + ANSI_RESET);
        System.out.println("Minimum spanning tree vertexes count: " + mst.getMst().vertexesNumber());
        System.out.println("Minimum spanning tree edges count: " + mst.getMst().edgesNumber());
        System.out.println("Minimum spanning tree weight: " + new DecimalFormat("#0.000").format(mst.getTotalDistance()/1000)  + " km\n");

        elapsed = (System.currentTimeMillis() - initial)/1000F;
        System.out.println("Whole execution took: " + elapsed + "sec\n");
    }
    
    /**
     * 
     * @param args the command line arguments. It should contain only one argument specifying the filepath of the data file
     * @throws IOException signals that an I/O exception of some kind has occurred
     * @throws NumberFormatException thrown to indicate that the application has attempted to convert a string to one of the numeric types, but that the string does not have the appropriate format
     * @throws IllegalArgumentException generally if a null value is passed; go to 'see'
     * @throws GraphException generally thrown by Graph constructor; go to 'see'
     * @throws DisjointSetException generally thrown by DisjointSet constructor; go to 'see'
     * @throws Exception generic execption
     */
    public static void main(String[] args) throws IOException, NumberFormatException, IllegalArgumentException, GraphException, DisjointSetException, Exception {
        if(args.length < 1) {
            throw new Exception("Usage: KruskalUsage <file_name>");
        }
        kruskalExecution(args[0]);
    } 
}
