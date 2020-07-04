package util;

import java.util.UUID;

public class GenerateCode {
    public static String generate() {
        String code;
        UUID uuid = UUID.randomUUID();
        code = uuid.toString().substring(0, 6).toUpperCase();
        return code;
    }

    public static void main(String[] args) {
        for (int i = 0; i < 10; i++)
            System.out.println(GenerateCode.generate());
    }
}
