package ru.nsu.fit.g19202.dani.calc;

import org.junit.jupiter.api.Test;
import ru.nsu.fit.g19202.dani.calc.CalcContext;
import ru.nsu.fit.g19202.dani.calc.CommandFactory;
import ru.nsu.fit.g19202.dani.calc.commands.CalcException;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class MulTest {

    @Test
    public void testMul() throws CalcException {
        CalcContext ctx = new CalcContext();
        CommandFactory factory = CommandFactory.getInstance();
        var mul = factory.findCommandByName("mul");
        ctx.getStack().push(12.0);
        ctx.getStack().push(36.0);
        mul.execute(null, ctx);
        assertEquals(12.0 * 36.0, ctx.getStack().pop());
    }

    @Test
    public void testMulOneNumber() {
        CalcContext ctx = new CalcContext();
        CommandFactory factory = CommandFactory.getInstance();
        var mul = factory.findCommandByName("mul");
        ctx.getStack().push(12.0);
        assertThrows(CalcException.class, () -> mul.execute(null,ctx));
    }

    @Test
    public void testMulNoNumbers() {
        CalcContext ctx = new CalcContext();
        CommandFactory factory = CommandFactory.getInstance();
        var mul = factory.findCommandByName("mul");
        assertThrows(CalcException.class, () -> mul.execute(null,ctx));
    }
}
