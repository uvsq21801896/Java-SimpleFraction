package fr.uvsq.tod.kata;
import org.junit.jupiter.api.*;
import static org.junit.jupiter.api.Assertions.assertEquals;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;




public class RomanNumeralsConverterTest {
  @Test
  public void shouldConvertTheDigitI() throws IllegalArgumentException {
    assertEquals(1, RomanNumeralsConverter.toDecimal("I"));
  }

  @Test
  public void shouldConvertTheDigitIX() throws IllegalArgumentException{
    assertEquals(9, RomanNumeralsConverter.toDecimal("IX"));
  }

  @Test
  void shouldConvertTheDigitMCMXCII() throws IllegalArgumentException{
    assertEquals(1992, RomanNumeralsConverter.toDecimal("MCMXCII"));
  }



}

