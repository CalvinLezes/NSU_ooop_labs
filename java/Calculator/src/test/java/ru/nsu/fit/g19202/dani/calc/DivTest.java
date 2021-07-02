package ru.nsu.fit.g19202.dani.calc;

import org.junit.jupiter.api.Test;
import ru.nsu.fit.g19202.dani.calc.CalcContext;
import ru.nsu.fit.g19202.dani.calc.CommandFactory;
import ru.nsu.fit.g19202.dani.calc.commands.CalcException;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class DivTest {

    @Test
    public void testDiv() throws CalcException {
        CalcContext ctx = new CalcContext();
        CommandFactory factory = CommandFactory.getInstance();
        var div = factory.findCommandByName("div");
        ctx.getStack().push(12.0);
        ctx.getStack().push(36.0);
        div.execute(null, ctx);
        assertEquals(12.0 / 36.0, ctx.getStack().pop());
    }

    @Test
    public void testDivOneNumber() {
        CalcContext ctx = new CalcContext();
        CommandFactory factory = CommandFactory.getInstance();
        var div = factory.findCommandByName("div");
        ctx.getStack().push(12.0);
        assertThrows(CalcException.class, () -> div.execute(null,ctx));
    }

    @Test
    public void testDivNoNumbers() {
        CalcContext ctx = new CalcContext();
        CommandFactory factory = CommandFactory.getInstance();
        var div = factory.findCommandByName("div");
        assertThrows(CalcException.class, () -> div.execute(null,ctx));
    }
}
