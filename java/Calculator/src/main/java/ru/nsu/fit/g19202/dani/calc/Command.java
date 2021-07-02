package ru.nsu.fit.g19202.dani.calc;

import ru.nsu.fit.g19202.dani.calc.commands.CalcException;

public interface Command {
    void execute(String[] args, CalcContext ctx) throws CalcException;
}
