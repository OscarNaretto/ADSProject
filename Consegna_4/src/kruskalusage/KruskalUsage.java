package kruskalusage;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.LinkedList;

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

    private static LinkedList<Edge<String, Double>> loadGraph(String filepath) throws NumberFormatException, IOException, GraphException{
        LinkedList<Edge<String, Double>> edgesList = new LinkedList<>();
        
        Path inputFilePath = Paths.get(filepath);
        try(BufferedReader fileInputReader = Files.newBufferedReader(inputFilePath, ENCODING)){
            String line = null;
            while((line = fileInputReader.readLine()) != null){      
                String[] lineElements = line.split(",");  
                Edge<String, Double> edge = new Edge<String, Double>(lineElements[0], lineElements[1], Double.parseDouble(lineElements[2])); 
                edgesList.add(edge);
            }
        }
        return edgesList;
    }

    private static void kruskalExecution(String filepath) throws IOException, NumberFormatException, GraphException, DisjointSetException{
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
        System.out.println("Minimum spanning tree weight: " + mst.getTotalDistance()/1000 + "km\n");

        elapsed = (System.currentTimeMillis() - initial)/1000F;
        System.out.println("Whole execution took: " + elapsed + "sec\n");
    }
    
    /**
     * @param args the command line arguments. It should contain only one argument
     * specifying the filepath of the data file
     */
    public static void main(String[] args) throws IOException, Exception {
        if(args.length < 1) {
            throw new Exception("Usage: OrderedArrayUsageJava <file_name>");
        }
        kruskalExecution(args[0]);
    } 
}