package fr.uvsq.tod.compte;

/**
 * La classe <code>Compte</code> représente un compte bancaire.
 *
 * @author hal
 * @version 2020
 */
public class Compte {

  private int solde;
  public Compte(int initialBalance) {
if(initialBalance<0){
  throw new IllegalArgumentException("Initialisation d'un compte négatif impossible");
}
this.solde=initialBalance;

  }

  public int getBalance() {
    return this.solde;
  }

  public void debit(int somme)
  {
    if(somme<0)
    {
      throw new IllegalArgumentException("Une somme négative est impossible à débiter");
    }

    if((this.solde-somme)<0)
    {
      throw new IllegalArgumentException("Le solde est insuffiant, le débit est impossible");
    }

    this.solde=solde-somme;
  }

  public void transfer(int somme, Compte compte)
  {
    if((this.solde-somme)<0)
    {
      throw new IllegalArgumentException("Une somme négative ne peut être débitée.");
    }

    this.debit(somme);
    compte.credit(somme);
  }

  public void credit(int somme)
  {
    if(somme<0)
    {
      throw new IllegalArgumentException("Une somme négative ne peut être créditée");
    }

    this.solde=solde+somme;
  }


}

