package kruskalusage;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.LinkedList;
import java.nio.file.Files;

import graph.Edge;
import graph.Graph;
import kruskalmst.KruskalMST;

public class KruskalUsage{
    private static final Charset ENCODING = StandardCharsets.UTF_8;

    private static Graph<String> loadGraph(String filepath) throws NumberFormatException, IOException{
        System.out.println("\nLoading data from file...\n");
        LinkedList<Edge<String>> edgesList = new LinkedList<>();
        
        Path inputFilePath = Paths.get(filepath);
        BufferedReader fileInputReader = Files.newBufferedReader(inputFilePath, ENCODING);
        String line = null;
        while((line = fileInputReader.readLine()) != null){      
            String[] lineElements = line.split(",");  
            Edge<String> edge = new Edge<String>(lineElements[0], lineElements[1], Double.parseDouble(lineElements[2])); 
            edgesList.add(edge);
        }
        Graph<String> graph = new Graph<String>(false, edgesList);
        System.out.println("\nData loaded\n");
        return graph;
    }

    private static void kruskalExecution(String filepath) throws IOException{
        Graph<String> graph;
        graph = loadGraph(filepath);
        KruskalMST<String> mst = new KruskalMST<>(graph); 
        mst.MST();
        System.out.println("Statistiche raccolte:");
        System.out.println("- Nodi della foresta minima: " + mst.getMst().vertexesNumber());
        System.out.println("- Archi della foresta minima: " + mst.getMst().edgesNumber());
        System.out.println("- Peso della foresta minima: " + mst.getTotalDistance()/1000);
    }
    
    /**
     * @param args the command line arguments. It should contain only one argument
     * specifying the filepath of the data file
     */
    public static void main(String[] args) throws IOException, Exception {
        if(args.length < 0)
        throw new Exception("Usage: OrderedArrayUsageJava <file_name>");
        
        kruskalExecution("italian_dist_graph.csv");
    } 
}