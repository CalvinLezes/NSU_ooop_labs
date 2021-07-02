package ru.nsu.fit.g19202.dani.calc.commands;

import ru.nsu.fit.g19202.dani.calc.CalcContext;
import ru.nsu.fit.g19202.dani.calc.Command;

public class Push implements Command {

    @Override
    @NumOfArgs(1)
    public void execute(String[] args, CalcContext ctx) throws CalcException {
        if(args[1].chars().allMatch(Character::isDigit)){
            ctx.getStack().push(Double.valueOf(args[1]));
        }
        else{
            Double value = ctx.getParams().get(args[1]);
            if(value == null){
                throw new CalcException("Unknown parameter");
            }
            else {
                ctx.getStack().push(value);
            }
        }
    }

}
