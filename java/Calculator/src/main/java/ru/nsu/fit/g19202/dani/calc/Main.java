package ru.nsu.fit.g19202.dani.calc;

import org.apache.logging.log4j.Logger;
import org.apache.logging.log4j.LogManager;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Main {

    private static final Logger logger = LogManager.getLogger();

    public static void main(String[] args) {
        CalcContext ctx = new CalcContext();
        try (BufferedReader reader = new BufferedReader(new FileReader(args[0]))) {
            CommandFactory factory = CommandFactory.getInstance();
            logger.trace("Start of calculation cycle");
            while (true) {
                logger.trace("New iteration");
                String arg = reader.readLine();
                logger.trace("Read line" + arg);
                if(arg == null || arg.isEmpty()){
                    logger.debug("Line is empty or no more lines");
                    break;
                }
                var cmdArgs = arg.split(" ");
                if(cmdArgs[0].equals("#")){
                    logger.trace("Commentary, skip line");
                    continue;
                }
                var cmd = factory.findCommandByName(cmdArgs[0]);
                if(cmd == null){
                    logger.debug("Command not found" + cmdArgs[0]);
                    System.out.println("Command not found");
                    continue;
                }
                try{
                    logger.trace("Executing command" + cmdArgs[0]);
                    cmd.execute(cmdArgs, ctx);
                    logger.trace("Command executed correctly");
                }catch (Exception e) {
                    logger.debug("Caught exception"+ e.getLocalizedMessage() + "while executing");
                    e.printStackTrace();
                }
            }

        } catch (IOException e) {
            logger.debug("Caught exception"+ e.getLocalizedMessage() + "while reading");
            e.printStackTrace();
        }
    }
}
