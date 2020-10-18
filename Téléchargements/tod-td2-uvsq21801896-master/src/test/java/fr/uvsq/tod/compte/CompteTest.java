package fr.uvsq.tod.compte;

import org.junit.Test;

import static org.junit.Assert.*;

public class CompteTest {
  @Test
  public void CreerUnCompteAvecUnSoldeInitial() {
    Compte compte = new Compte(2000);
    assertEquals(2000, compte.getBalance());
  }
  @Test(expected=IllegalArgumentException.class)
  public void EchoueSiLeSoldeDansLeCompteEstNegatif()
  {
    Compte compte=new Compte(-2000);
  }
  @Test
  public void DebiteUnCompteAvecUneSommePositif()
  {
    Compte compte=new Compte(11);

    compte.debit(10);

    assertEquals(11-10, compte.getBalance());
  }
  @Test(expected=IllegalArgumentException.class)
  public void EchoueSiOnDebiteUnCompteAvecUnSoldeNegatif()
  {
    Compte compte=new Compte(1000);

    compte.debit(-100);
  }
  @Test(expected=IllegalArgumentException.class)
  public void EchoueSiOnDebiteUnCompteQuiAUnSoldeInferieurAuMontantADebiter()
  {
    Compte compte=new Compte(2000);

    compte.debit(6000);
  }
  @Test
  public void TransfertUneSommeDUnCompteDontLeSoldeEstSuperieurAuMontantTransferéAUnAutreCompte()
  {
    Compte compteEnvoie=new Compte(2000);
    Compte compteRecu=new Compte(2000);

    compteEnvoie.transfer(150, compteRecu);

    assertEquals(2000-150, compteEnvoie.getBalance());
    assertEquals(2000+150, compteRecu.getBalance());
  }
  @Test(expected=IllegalArgumentException.class)
  public void EchoueSiOnTransfereUneSommeSuperieurANotreSolde()
  {
    Compte compteEnvoie=new Compte(1000);
    Compte compteRecu=new Compte(1500);

    compteEnvoie.transfer(1100, compteRecu);
  }
  @Test
  public void CréditeUnCompteAvecUnSoldePositif()
  {
    Compte compte=new Compte(2000);

    compte.credit(1000);

    assertEquals(2000+1000, compte.getBalance());
  }
  @Test(expected=IllegalArgumentException.class)
  public void EchoueSiLeMontantACrediterEstNegatif()
  {
    Compte compte=new Compte(2000);

    compte.credit(-1000);
  }




}
