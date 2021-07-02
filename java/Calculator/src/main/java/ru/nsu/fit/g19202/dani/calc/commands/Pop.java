package ru.nsu.fit.g19202.dani.calc.commands;

import ru.nsu.fit.g19202.dani.calc.CalcContext;
import ru.nsu.fit.g19202.dani.calc.Command;

public class Pop implements Command {
    @Override
    @StackSize(1)
    public void execute(String[] args, CalcContext ctx) throws CalcException {
        ctx.getStack().pop();
    }
}
