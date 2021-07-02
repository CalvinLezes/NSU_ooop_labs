package ru.nsu.fit.g19202.dani.calc.commands;

import ru.nsu.fit.g19202.dani.calc.CalcContext;
import ru.nsu.fit.g19202.dani.calc.Command;

import java.util.Deque;

public class Sub implements Command {
    @Override
    @StackSize(2)
    public void execute(String[] args, CalcContext ctx) throws CalcException {
        Deque<Double> stack = ctx.getStack();
        Double v1  = stack.pop();
        Double v2 = stack.pop();
        stack.push(v2 - v1);
    }
}
