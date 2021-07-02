package ru.nsu.fit.g19202.dani.calc;

import org.junit.jupiter.api.Test;
import ru.nsu.fit.g19202.dani.calc.CalcContext;
import ru.nsu.fit.g19202.dani.calc.CommandFactory;
import ru.nsu.fit.g19202.dani.calc.commands.CalcException;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class DefineTest {
    @Test
    public void testDefine() throws CalcException {
        CalcContext ctx = new CalcContext();
        CommandFactory factory = CommandFactory.getInstance();
        String[] args = {"define","a","4"};
        var def = factory.findCommandByName(args[0]);
        def.execute(args,ctx);

        assertEquals(4.0, ctx.getParams().get("a"),1e-10);
    }

    @Test
    public void testDefineNoArgs() throws CalcException {
        CalcContext ctx = new CalcContext();
        CommandFactory factory = CommandFactory.getInstance();
        String[] args = {"define"};
        var def = factory.findCommandByName(args[0]);

        assertThrows(CalcException.class, () -> def.execute(args, ctx));
    }
}
