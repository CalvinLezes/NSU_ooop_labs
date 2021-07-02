package ru.nsu.fit.g19202.dani.calc;

import org.junit.jupiter.api.Test;
import ru.nsu.fit.g19202.dani.calc.commands.CalcException;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class SubTest {

    @Test
    public void testSub() throws CalcException {
        CalcContext ctx = new CalcContext();
        CommandFactory factory = CommandFactory.getInstance();
        var sub = factory.findCommandByName("sub");
        ctx.getStack().push(12.0);
        ctx.getStack().push(36.0);
        sub.execute(null, ctx);
        assertEquals(12.0 - 36.0, ctx.getStack().pop());
    }

    @Test
    public void testSubOneNumber() {
        CalcContext ctx = new CalcContext();
        CommandFactory factory = CommandFactory.getInstance();
        var sub = factory.findCommandByName("sub");
        ctx.getStack().push(12.0);
        assertThrows(CalcException.class, () -> sub.execute(null,ctx));
    }

    @Test
    public void testSubNoNumbers() {
        CalcContext ctx = new CalcContext();
        CommandFactory factory = CommandFactory.getInstance();
        var sub = factory.findCommandByName("sub");
        assertThrows(CalcException.class, () -> sub.execute(null,ctx));
    }
}
