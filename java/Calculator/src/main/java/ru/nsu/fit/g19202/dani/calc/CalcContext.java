package ru.nsu.fit.g19202.dani.calc;

import java.util.ArrayDeque;
import java.util.Deque;
import java.util.HashMap;
import java.util.Map;

public class CalcContext {
    private Deque<Double> stack = new ArrayDeque<>();
    private Map<String,Double> params= new HashMap<>();

    public Deque<Double> getStack() {
        return stack;
    }

    public Map<String, Double> getParams() {
        return params;
    }
}
