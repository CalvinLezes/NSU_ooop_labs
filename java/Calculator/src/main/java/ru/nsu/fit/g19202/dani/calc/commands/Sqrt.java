package ru.nsu.fit.g19202.dani.calc.commands;

import ru.nsu.fit.g19202.dani.calc.CalcContext;
import ru.nsu.fit.g19202.dani.calc.Command;

import java.util.Deque;

public class Sqrt implements Command {
    @Override
    @StackSize(1)
    public void execute(String[] args, CalcContext ctx) throws CalcException {
        Deque<Double> stack = ctx.getStack();
        Double v1  = stack.pop();
        stack.push(Math.sqrt(v1));
    }
}
