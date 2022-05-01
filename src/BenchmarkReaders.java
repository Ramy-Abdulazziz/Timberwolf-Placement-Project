import java.io.*;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.Iterator;

public class BenchmarkReaders {

    public static void readNodes(String filename) {

        try {

            BufferedReader reader = new BufferedReader(
                                    new InputStreamReader(
                                    new FileInputStream(filename), Charset.forName(StandardCharsets.UTF_8.name())));

            Iterator<String> lineReader = reader.lines().iterator();
            int lineCount = 0;

            while (lineReader.hasNext()) {
                lineCount++;

                if (lineCount == 6) {

                    String[] line = lineReader.next().split("\\s+");
                    int numNodes = Integer.parseInt(line[2]);

                    line = lineReader.next().split("\\s+");
                    int numTerminals = Integer.parseInt(line[2]);

                }
                if (lineCount > 7) {

                    reader.lines().forEach(line -> {

                        boolean terminal = false;
                        String[] nodeLine = line.split("\\s+");

                        if (line.length() > 4 && nodeLine[4].equals("terminal")) {
                             terminal = true;
                        }

                        String name = nodeLine[1];
                        int width = Integer.parseInt(nodeLine[2]);
                        int height = Integer.parseInt(nodeLine[3]);
                    });

                }


            }
        }catch(FileNotFoundException e){
            System.out.println("File location error");
            e.printStackTrace();

        }
    }

    public static void readWts(String fileName){




    }

    public static void readNets(String fileName){


    }

    public static void readScl(String filename){


    }

    public static void readPl(String filename){


    }

    public static void readAux(String filename){


    }


}
