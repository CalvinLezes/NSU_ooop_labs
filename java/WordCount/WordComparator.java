package ru.nsu.fit.g19202.Ermilov.task1;

import java.util.Comparator;
import java.util.Map;

public class WordComparator implements Comparator<Map.Entry<String,Integer>> {

    @Override
    public int compare(Map.Entry<String, Integer> a, Map.Entry<String, Integer> b) {
        int rs = b.getValue().compareTo(a.getValue());
        if(rs == 0){
            rs = a.getKey().compareTo(b.getKey());
        }
        return rs;
    }
}
