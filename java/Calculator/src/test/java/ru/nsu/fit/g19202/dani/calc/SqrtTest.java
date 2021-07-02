package ru.nsu.fit.g19202.dani.calc;

import org.junit.jupiter.api.Test;
import ru.nsu.fit.g19202.dani.calc.CalcContext;
import ru.nsu.fit.g19202.dani.calc.CommandFactory;
import ru.nsu.fit.g19202.dani.calc.commands.CalcException;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class SqrtTest {

    @Test
    public void testSqrt() throws CalcException {
        CalcContext ctx = new CalcContext();
        CommandFactory factory = CommandFactory.getInstance();
        var sqrt = factory.findCommandByName("sqrt");
        ctx.getStack().push(16.0);
        sqrt.execute(null, ctx);
        assertEquals(4.0, ctx.getStack().pop());
    }

    @Test
    public void testSqrtNoNumbers() {
        CalcContext ctx = new CalcContext();
        CommandFactory factory = CommandFactory.getInstance();
        var sqrt = factory.findCommandByName("sqrt");
        assertThrows(CalcException.class, () -> sqrt.execute(null,ctx));
    }
}
