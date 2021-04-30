package ru.nsu.fit.g19202.Ermilov.task1;

import java.io.IOException;
import java.io.Reader;
import java.util.Map;

public interface StatBuilder {
    int buildStat(Reader reader, Map<String, Integer> words) throws IOException;
}