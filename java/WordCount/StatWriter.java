package ru.nsu.fit.g19202.Ermilov.task1;

import java.io.IOException;
import java.io.Writer;
import java.util.Map;

public interface StatWriter {
    void writeStat(Writer writer, WordComparator comparator, int total, Map<String, Integer> words) throws IOException;
}
