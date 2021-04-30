package ru.nsu.fit.g19202.Ermilov.task1;

import org.apache.commons.cli.*;

import java.io.*;
import java.util.HashMap;
import java.util.Map;

public class main {
    public static void main(String[] args) throws IOException {
        CommandLine line = parseArgs(args);
        if(line == null){
            return;
        }
        Map<String, Integer> words = new HashMap();
        int total;
        try(Reader reader = new InputStreamReader(getInputStream(line))){
            StatBuilder sb = new DefaultStatBuilder();
            total = sb.buildStat(reader, words);
        }
        WordComparator comparator = new WordComparator();
        try(Writer writer = new OutputStreamWriter(getOutputStream(line))){
            StatWriter sw = new DefaultStatWriter();
            sw.writeStat(writer, comparator, total, words);
        }

    }

    private static OutputStream getOutputStream(CommandLine line) throws FileNotFoundException {
        OutputStream out = System.out;
        if(line.hasOption("out")){
            String file = line.getOptionValue("out");
            System.out.println("Writing to:" + file);
            out = new FileOutputStream(file);
        }
        return out;
    }

    private static InputStream getInputStream(CommandLine line) throws FileNotFoundException {
        InputStream in = System.in;
        if(line.hasOption("file")){
            String file = line.getOptionValue("file");
            System.out.println("Reading from:" + file);
            in = new FileInputStream(file);
        }
        return in;
    }

    private static CommandLine parseArgs(String[] args) {
        Options options = new Options();
        options.addOption("f","file", true, "InputFile");
        options.addOption("o","out", true, "OutputFile");
        CommandLineParser parser = new DefaultParser();
        CommandLine line = null;
        try {
            line = parser.parse(options, args);
        } catch (ParseException e) {
            e.printStackTrace();
        }
        return line;
    }
}
