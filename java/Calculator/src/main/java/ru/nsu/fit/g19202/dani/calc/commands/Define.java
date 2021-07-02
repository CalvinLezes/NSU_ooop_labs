package ru.nsu.fit.g19202.dani.calc.commands;

import ru.nsu.fit.g19202.dani.calc.CalcContext;
import ru.nsu.fit.g19202.dani.calc.Command;

import java.util.Map;

public class Define implements Command {

    @Override
    @NumOfArgs(2)
    public void execute(String[] args, CalcContext ctx) throws CalcException {
        Map<String, Double> params = ctx.getParams();
        params.put(args[1],Double.valueOf(args[2]));
    }
}
