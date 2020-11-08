package fr.uvsq.tod.kata;
import org.junit.jupiter.api.*;
import static org.junit.jupiter.api.Assertions.assertEquals;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;
import java.util.*;
import java.lang.*;
/**
 * La classe <code>RomanNumeralsConverter</code> regroupe des fonctions pour la manipulation de nombres en numération romaine.
 *
 * @author hal
 * @version 2020
 */
public class RomanNumeralsConverter {
  /**
   * Convertit un nombre en chiffres romains en décimal
   * @param i la chaîne de caractères contenant le nombre en chiffres romains
   * @return la valeur décimal de ce nombre
   */

    public static int toDecimal(String i) {
      String firstposition;
      String lastposition;
      String position;
      int res = 0;
      int length = i.length();
      if(length == 0) return -1;
      else if(length == 1)
      {
        return (romanMap.containsKey(i) ? romanMap.get(i) : -1);
      }
      else
      {
        int a = 0;
        while(a<length-1)
        {
          position = String.valueOf(i.charAt(a));
          firstposition = String.valueOf(i.charAt(a+1));
          a++;

          if( toDecimal(position) >= toDecimal(firstposition) )
          {
            res = romanMap.containsKey(position) ? res+romanMap.get(position):-1;

          }
          else
          {
            res = romanMap.containsKey(position) ? res-romanMap.get(position):-1;
          }
        }
      }

      lastposition = String.valueOf(i.charAt(length-1));

      if(toDecimal(lastposition) != -1) res += toDecimal(lastposition);

      return res;
    }

  public static Map<String, Integer> romanMap;
  static {
    romanMap = new HashMap<String,Integer>();

    romanMap.put("I", 1);

    romanMap.put("V", 5);

    romanMap.put("X", 10);

    romanMap.put("L", 50);

    romanMap.put("C", 100);

    romanMap.put("D", 500);

    romanMap.put("M", 1000);

  }
    }
