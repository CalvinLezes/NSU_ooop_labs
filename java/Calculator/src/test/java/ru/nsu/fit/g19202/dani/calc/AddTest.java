package ru.nsu.fit.g19202.dani.calc;

import org.junit.jupiter.api.Test;
import ru.nsu.fit.g19202.dani.calc.CalcContext;
import ru.nsu.fit.g19202.dani.calc.CommandFactory;
import ru.nsu.fit.g19202.dani.calc.commands.CalcException;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class AddTest {

    @Test
    public void testAdd() throws CalcException {
        CalcContext ctx = new CalcContext();
        CommandFactory factory = CommandFactory.getInstance();
        var sum = factory.findCommandByName("add");
        ctx.getStack().push(12.0);
        ctx.getStack().push(36.0);
        sum.execute(null, ctx);
        assertEquals(12.0 + 36.0, ctx.getStack().pop());
    }

    @Test
    public void testAddOneNumber() {
        CalcContext ctx = new CalcContext();
        CommandFactory factory = CommandFactory.getInstance();
        var sum = factory.findCommandByName("add");
        ctx.getStack().push(12.0);
        assertThrows(CalcException.class, () -> sum.execute(null,ctx));
    }

    @Test
    public void testAddNoNumbers() {
        CalcContext ctx = new CalcContext();
        CommandFactory factory = CommandFactory.getInstance();
        var sum = factory.findCommandByName("add");
        assertThrows(CalcException.class, () -> sum.execute(null,ctx));
    }
}
