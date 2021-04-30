package ru.nsu.fit.g19202.Ermilov.task1;

import java.io.IOException;
import java.io.Writer;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class DefaultStatWriter implements StatWriter{

    @Override
    public void writeStat(Writer writer, WordComparator comparator, int total, Map<String, Integer> words) throws IOException {
        List<Map.Entry<String, Integer>> toSort = new ArrayList<>(words.entrySet());
        toSort.sort(comparator);
        for (Map.Entry<String, Integer> e : toSort) {
            String per = Float.toString((100.0f * e.getValue() / total));
            writer.append(e.getKey()).append('\t').append(e.getValue().toString()).append('\t').append(per).append('\n');
        }
    }
}
