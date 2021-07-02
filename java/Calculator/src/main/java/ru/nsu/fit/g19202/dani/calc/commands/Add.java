package ru.nsu.fit.g19202.dani.calc.commands;

import ru.nsu.fit.g19202.dani.calc.CalcContext;
import ru.nsu.fit.g19202.dani.calc.Command;

import java.util.Deque;

public class Add implements Command {

    @Override
    @StackSize(2)
    public void execute(String[] args, CalcContext ctx) {
        Deque<Double> stack = ctx.getStack();
        Double v1  = stack.pop();
        Double v2 = stack.pop();
        stack.push(v1 + v2);

    }
}
