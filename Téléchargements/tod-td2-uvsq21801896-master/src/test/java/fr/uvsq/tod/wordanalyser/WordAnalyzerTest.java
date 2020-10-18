package fr.uvsq.tod.wordanalyser;

import org.junit.Test;
import static org.junit.Assert.*;
public class WordAnalyzerTest {
  @Test
  public void expectAForAardvark() {
    WordAnalyzer w = new WordAnalyzer("aardvark");
    char res = w.firstRepeatedCharacter();
    assertEquals('a', res);
  }
  @Test
  public void expectAForRoommate() {
    WordAnalyzer w = new WordAnalyzer("roomate");
    char res = w.firstRepeatedCharacter();
    assertEquals('o', res );
  }
  @Test
  public void expectAForMate() {
    WordAnalyzer w = new WordAnalyzer("mate");
    char res = w.firstRepeatedCharacter();
    assertEquals(0, res);
  }
  @Test
  public void expectAForTest() {
    WordAnalyzer w = new WordAnalyzer("test");
    char res = w.firstRepeatedCharacter();
    assertEquals(0, res);
  }
  @Test
  public void expectIForMissisippi() {
    WordAnalyzer w = new WordAnalyzer("missisippi");
    char res = w.firstMultipleCharacter();
    assertEquals('i', res);
  }

  @Test
  public void expectZEROForMate() {
    WordAnalyzer w = new WordAnalyzer("mate");
    char res = w.firstMultipleCharacter();
    assertEquals(0, res);
  }
  @Test
  public void expectTForTest() {
    WordAnalyzer w = new WordAnalyzer("test");
    char res = w.firstMultipleCharacter();
    assertEquals('t', res);
  }


}
