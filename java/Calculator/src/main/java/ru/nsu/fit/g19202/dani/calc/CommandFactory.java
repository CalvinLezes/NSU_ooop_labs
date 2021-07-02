package ru.nsu.fit.g19202.dani.calc;

import ru.nsu.fit.g19202.dani.calc.commands.CalcException;
import ru.nsu.fit.g19202.dani.calc.commands.NumOfArgs;
import ru.nsu.fit.g19202.dani.calc.commands.StackSize;

import java.io.InputStream;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

public class CommandFactory {

   private static class Helper {
        private static final CommandFactory factory = new CommandFactory();
    }

    public static CommandFactory getInstance() {
        return Helper.factory;
    }

 private final Map<String,Command> commands = new HashMap<>();

    public CommandFactory(){
        try(InputStream in = Main.class.getResourceAsStream("/ru/nsu/fit/g19202/dani/calc/commands.properties")){
            Properties properties = new Properties();
            properties.load(in);
            for(var name : properties.stringPropertyNames()){
                String className = properties.getProperty(name);
                Class<?> aClass = Class.forName(className);
                var cmd = (Command)aClass.newInstance();
                StackSize stackSize = aClass.getMethod("execute", String[].class, CalcContext.class)
                        .getAnnotation(StackSize.class);
                NumOfArgs numOfArgs = aClass.getMethod("execute", String[].class, CalcContext.class)
                        .getAnnotation(NumOfArgs.class);
                Command proxyCommand = (args, ctx) -> {
                    if(stackSize != null && stackSize.value() > ctx.getStack().size()){
                        throw new CalcException(name + " expects at least " + stackSize.value() + " in stack.");
                    }
                    if(numOfArgs != null && numOfArgs.value() > args.length){
                        throw new CalcException(name + " requires "+ numOfArgs.value()+" args.");
                    }

                    cmd.execute(args, ctx);
                };
                commands.put(name,proxyCommand);

            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public Command findCommandByName(String name) {
        return commands.get(name);
    }
}
