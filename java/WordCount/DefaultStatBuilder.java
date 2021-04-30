package ru.nsu.fit.g19202.Ermilov.task1;

import java.io.IOException;
import java.io.Reader;
import java.util.Map;

public class DefaultStatBuilder implements StatBuilder{

    @Override
    public int buildStat(Reader reader, Map<String, Integer> words) throws IOException{
        StringBuilder sb = new StringBuilder();
        int total = 0;
        int c;
        while ((c = reader.read()) != -1) {
            char cc = (char) c;
            if (Character.isLetterOrDigit(cc)) {
                sb.append(Character.toLowerCase(cc));
            } else if (sb.length() > 0) {
                words.merge(sb.toString(), 1, Integer::sum);
                sb.setLength(0);
                total++;
            }
        }
        if (sb.length() > 0) {
            words.merge(sb.toString(), 1, Integer::sum);
            total++;
        }
        return total;
    }
}
